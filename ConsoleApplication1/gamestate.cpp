#include "gamestate.h"
#include "level.h"
#include "player.h"

GameState* GameState::m_unique_instance = nullptr;
GameState::GameState() {}

GameState* GameState::getInstance() {
    if (!m_unique_instance)
        m_unique_instance = new GameState();
    return m_unique_instance;
}
static void mouseToCanvas(const graphics::MouseState& ms, float& mx, float& my) {
    mx = graphics::windowToCanvasX(ms.cur_pos_x);
    my = graphics::windowToCanvasY(ms.cur_pos_y);
}

void GameState::init() {
    m_status = STATUS_MENU;
    m_current_level_count = 1;
    m_current_round = 1;
    m_max_levels = 3;
    m_victory = false;
    m_current_level = new Level();
    m_current_level->init();

    m_player = new Player("Player1");
    m_player->init();

    std::string music_path = getFullAssetPath("Idea 22 (1).mp3");
    graphics::playMusic(music_path, 0.5f, true);
}

void GameState::draw() {
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx, my;
    mouseToCanvas(ms, mx, my);
    if (m_status == STATUS_PLAYING) {
        if (m_current_level) m_current_level->draw();
        if (m_player) m_player->draw();
    }
    if (m_status == STATUS_MENU) {
        graphics::Brush br, text_br;
        if (!m_victory) {
            graphics::Brush bg;
            bg.texture = getFullAssetPath("menu.png"); 
            bg.fill_opacity = 1.0f;
            bg.outline_opacity = 0.0f;
            graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, bg);
        }
        text_br.fill_color[0] = 1.0f; text_br.fill_color[1] = 1.0f; text_br.fill_color[2] = 1.0f;
        text_br.fill_opacity = 1.0f;
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.7f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);

        if (!m_victory) {
            graphics::drawText(3.6f, 2.2f, 0.60f, "MY GAME", text_br);
            bool play_hover = (mx >= 3.5f && mx <= 6.5f && my >= 4.5f && my <= 5.5f);
            float p_scale = play_hover ? 1.1f : 1.0f;
            br.fill_opacity = 1.0f;
            br.fill_color[0] = 1.0f; br.fill_color[1] = play_hover ? 0.9f : 0.7f; br.fill_color[2] = 0.0f;
            graphics::drawRect(5.0f, 5.0f, 3.0f * p_scale, 1.0f * p_scale, br);
            graphics::drawText(4.35f, 5.15f, 0.45f, "PLAY", text_br); 
            bool settings_hover = (mx >= 3.5f && mx <= 6.5f && my >= 6.0f && my <= 7.0f);
            float s_scale = settings_hover ? 1.1f : 1.0f;
            br.fill_color[0] = settings_hover ? 0.7f : 0.5f; br.fill_color[1] = br.fill_color[0]; br.fill_color[2] = br.fill_color[0];
            graphics::drawRect(5.0f, 6.5f, 3.0f * s_scale, 1.0f * s_scale, br);
            graphics::drawText(3.9f, 6.65f, 0.40f, "SETTINGS", text_br); 
            bool exit_hover = (mx >= 3.5f && mx <= 6.5f && my >= 7.5f && my <= 8.5f);
            br.fill_color[0] = exit_hover ? 0.9f : 0.6f; br.fill_color[1] = 0.1f; br.fill_color[2] = 0.1f;
            graphics::drawRect(5.0f, 8.0f, 3.0f, 1.0f, br);
            graphics::drawText(4.45f, 8.15f, 0.40f, "EXIT", text_br);
        }
        else {
            graphics::drawText(1.5f, 3.5f, 0.6f, "CONGRATULATIONS!", text_br);
            graphics::Brush bg;
            bg.texture = getFullAssetPath("congr.png"); 
            bg.fill_opacity = 1.0f;
            bg.outline_opacity = 0.0f;
            graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, bg);
            graphics::drawText(2.0f, 4.5f, 0.4f, "YOU FINISHED ALL LEVELS", text_br);
            bool re_hover = (mx >= 2.8f && mx <= 5.0f && my >= 6.0f && my <= 6.8f);
            br.fill_opacity = 1.0f;
            br.fill_color[0] = re_hover ? 0.4f : 0.2f; br.fill_color[1] = re_hover ? 1.0f : 0.8f; br.fill_color[2] = 0.4f;
            graphics::drawRect(3.9f, 6.4f, 2.2f, 0.8f, br);
            graphics::drawText(3.35f, 6.5f, 0.25f, "RESTART", text_br);
            bool back_hover = (mx >= 5.0f && mx <= 7.2f && my >= 6.0f && my <= 6.8f);
            br.fill_color[0] = back_hover ? 0.9f : 0.7f; br.fill_color[1] = back_hover ? 0.4f : 0.2f; br.fill_color[2] = back_hover ? 0.4f : 0.2f;
            graphics::drawRect(6.1f, 6.4f, 2.2f, 0.8f, br);
            graphics::drawText(5.75f, 6.5f, 0.25f, "MENU", text_br);
        }
    }

    if (m_status == STATUS_SETTINGS) {
        graphics::Brush br, txt;
        txt.fill_color[0] = 1.0f; txt.fill_color[1] = 1.0f; txt.fill_color[2] = 1.0f;
        br.fill_opacity = 0.9f;
        br.fill_color[0] = 0.1f; br.fill_color[1] = 0.1f; br.fill_color[2] = 0.2f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);
        graphics::drawText(3.0f, 3.0f, 0.6f, "SELECT LEVELS:", txt);

        for (int i = 0; i < 3; i++) {
            int val = (i == 0) ? 3 : (i == 1) ? 5 : 10;
            float x_pos = 3.5f + i * 1.5f;
            br.fill_opacity = 1.0f;
            br.fill_color[0] = (m_max_levels == val) ? 1.0f : 0.4f;
            br.fill_color[1] = (m_max_levels == val) ? 0.8f : 0.4f;
            graphics::drawRect(x_pos, 5.0f, 1.2f, 1.2f, br);
            graphics::drawText(x_pos - 0.2f, 5.1f, 0.4f, std::to_string(val), txt);
        }

        bool b_hover = (mx >= 4.0f && mx <= 6.0f && my >= 8.0f && my <= 8.8f);
        br.fill_color[0] = b_hover ? 1.0f : 0.8f; br.fill_color[1] = 0.2f; br.fill_color[2] = 0.2f;
        graphics::drawRect(5.0f, 8.4f, 2.0f, 0.8f, br);
        graphics::drawText(4.55f, 8.5f, 0.25f, "BACK", txt);
    }
    if (m_status == STATUS_EXIT_CONFIRM) {
        graphics::Brush br, txt;
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.8f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);
        txt.fill_color[0] = 1.0f; txt.fill_color[1] = 1.0f; txt.fill_color[2] = 1.0f;
        graphics::drawText(3.5f, 4.5f, 0.5f, "EXIT GAME?", txt); 
        graphics::drawText(4.2f, 5.5f, 0.3f, "Y : YES", txt);
        graphics::drawText(4.2f, 6.0f, 0.3f, "N : NO", txt);
    }
}

void GameState::update(float dt) {
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx, my;
    mouseToCanvas(ms, mx, my);
    if (m_status == STATUS_EXIT_CONFIRM) {
        if (graphics::getKeyState(graphics::SCANCODE_Y)) {
            graphics::stopMessageLoop(); 
            return;
        }
        if (graphics::getKeyState(graphics::SCANCODE_N)) {
            m_status = STATUS_MENU; 
            return;
        }
        return; 
    }
    if (m_status == STATUS_MENU) {
        if (ms.button_left_pressed) {
            if (!m_victory) {
                if (mx >= 3.5f && mx <= 6.5f && my >= 4.5f && my <= 5.5f) {
                    m_status = STATUS_PLAYING;
                    m_current_level_count = 1;
                    if (m_player) { m_player->m_pos_x = 0.5f; m_player->m_pos_y = 0.5f; }
                    graphics::playSound(getFullAssetPath("start.mp3"), 0.5f, false);
                }
                else if (mx >= 3.5f && mx <= 6.5f && my >= 6.0f && my <= 7.0f) {
                    m_status = STATUS_SETTINGS;
                }
                else if (mx >= 3.5f && mx <= 6.5f && my >= 7.5f && my <= 8.5f) {
                    m_status = STATUS_EXIT_CONFIRM;
                    graphics::playSound(getFullAssetPath("click.mp3"), 0.5f, false);
                }
            }
            else {
                if (mx >= 2.8f && mx <= 5.0f && my >= 6.0f && my <= 6.8f) {
                    m_victory = false;
                    m_current_level_count = 1;
                    m_status = STATUS_PLAYING;
                    if (m_current_level) { delete m_current_level; m_current_level = new Level(); m_current_level->init(); }
                    if (m_player) { m_player->m_pos_x = 0.5f; m_player->m_pos_y = 0.5f; }
                    graphics::playSound(getFullAssetPath("start.mp3"), 0.5f, false);
                }
                else if (mx >= 5.0f && mx <= 7.2f && my >= 6.0f && my <= 6.8f) {
                    m_victory = false;
                    m_current_level_count = 1;
                    graphics::playSound(getFullAssetPath("click.mp3"), 0.5f, false);
                }
            }
        }
        return;
    }

    if (m_status == STATUS_SETTINGS) {
        if (ms.button_left_pressed) {
            if (my >= 4.4f && my <= 5.6f) {
                if (mx >= 2.9f && mx <= 4.1f) m_max_levels = 3;
                else if (mx >= 4.4f && mx <= 5.6f) m_max_levels = 5;
                else if (mx >= 5.9f && mx <= 7.1f) m_max_levels = 10;
            }
            if (mx >= 4.0f && mx <= 6.0f && my >= 8.0f && my <= 8.8f) m_status = STATUS_MENU;
        }
        return;
    }

    if (m_status == STATUS_PLAYING) {
        if (m_player) m_player->update(dt);
        if (m_current_level) m_current_level->update(dt);
    }
}

void GameState::nextLevel() {
    if (m_current_level_count >= m_max_levels) {
        m_victory = true;
        m_status = STATUS_MENU; 
        graphics::playSound(getFullAssetPath("victory.mp3"), 1.0f, false);
        return;
    }
    m_current_level_count++;
    if (m_current_level) delete m_current_level;
    m_current_level = new Level();
    m_current_level->init();
    if (m_player) { m_player->m_pos_x = 0.5f; m_player->m_pos_y = 0.5f; }
}