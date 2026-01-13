#include "gamestate.h"
#include "level.h"
#include "player.h"

// Αρχικοποίηση του στατικού δείκτη
GameState* GameState::m_unique_instance = nullptr;

GameState::GameState() {}

GameState* GameState::getInstance() {
    if (!m_unique_instance)
        m_unique_instance = new GameState();
    return m_unique_instance;
}

void GameState::init() {
    m_current_level = new Level();
    m_current_level->init();

    m_player = new Player("Player1");
    m_player->init();

    std::string music_path = getFullAssetPath("Idea 22 (1).mp3");
    graphics::playMusic(music_path, 0.5f, true);
}

void GameState::draw() {
    // 1. Σχεδιάζουμε ΠΑΝΤΑ το παιχνίδι πρώτο (background)
    if (m_current_level) m_current_level->draw();
    if (m_player) m_player->draw();

    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = ms.cur_pos_x / 80.0f;
    float my = ms.cur_pos_y / 80.0f;

    // 2. ΟΘΟΝΗ ΜΕΝΟΥ
    if (m_status == STATUS_MENU) {
        graphics::Brush br, icon_br, icon1_br, icon2_br;

        // Overlay "θολώματος"
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.7f;
        br.outline_opacity = 0.0f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);

        // Hover Logic για Play
        bool play_hover = (mx >= 3.5f && mx <= 6.5f && my >= 4.5f && my <= 5.5f);
        float play_scale = play_hover ? 1.1f : 1.0f;

        br.fill_opacity = 1.0f;
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = play_hover ? 0.9f : 0.7f;
        br.fill_color[2] = 0.0f;
        graphics::drawRect(5.0f, 5.0f, 3.0f * play_scale, 1.0f * play_scale, br);

        icon_br.texture = getFullAssetPath("play.png");
        icon_br.fill_opacity = 1.0f;
        graphics::drawRect(5.0f, 5.0f, 1.0f * play_scale, 0.8f * play_scale, icon_br);

        // Τίτλος
        icon1_br.texture = getFullAssetPath("start.png");
        icon1_br.fill_opacity = 1.0f;
        graphics::drawRect(5.0f, 4.0f, 2.0f, 1.0f, icon1_br);

        // Hover Logic για Settings
        bool settings_hover = (mx >= 3.5f && mx <= 6.5f && my >= 6.0f && my <= 7.0f);
        float settings_scale = settings_hover ? 1.1f : 1.0f;

        br.fill_color[0] = settings_hover ? 0.7f : 0.5f;
        br.fill_color[1] = settings_hover ? 0.7f : 0.5f;
        br.fill_color[2] = settings_hover ? 0.7f : 0.5f;
        graphics::drawRect(5.0f, 6.5f, 3.0f * settings_scale, 1.0f * settings_scale, br);

        icon2_br.texture = getFullAssetPath("settings.png");
        icon2_br.fill_opacity = 1.0f;
        graphics::drawRect(5.0f, 6.5f, 1.0f * settings_scale, 1.0f * settings_scale, icon2_br);

        if (m_victory) {
            br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
            graphics::drawText(3.0f, 8.5f, 0.5f, "VICTORY! ALL LEVELS CLEAR!", br);
        }
        return;
    }

    // 3. ΟΘΟΝΗ ΡΥΘΜΙΣΕΩΝ
    if (m_status == STATUS_SETTINGS) {
        graphics::Brush br, icon_selector_br;
        br.fill_opacity = 0.9f;
        br.fill_color[0] = 0.1f; br.fill_color[1] = 0.1f; br.fill_color[2] = 0.2f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);

        br.fill_opacity = 1.0f;
        br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
        graphics::drawText(3.0f, 3.0f, 0.6f, "SELECT LEVELS:", br);

        for (int i = 0; i < 3; i++) {
            int val = (i == 0) ? 3 : (i == 1) ? 5 : 10;
            float x_pos = 3.5f + i * 1.5f;

            br.fill_color[0] = (m_max_levels == val) ? 1.0f : 0.4f;
            br.fill_color[1] = (m_max_levels == val) ? 0.8f : 0.4f;
            graphics::drawRect(x_pos, 5.0f, 1.2f, 1.2f, br);

            icon_selector_br.fill_opacity = 1.0f;
            std::string icon_name = "level" + std::to_string(val) + ".png";
            icon_selector_br.texture = getFullAssetPath(icon_name);
            graphics::drawRect(x_pos, 5.0f, 0.8f, 0.8f, icon_selector_br);
        }

        br.fill_color[0] = 0.8f; br.fill_color[1] = 0.2f; br.fill_color[2] = 0.2f;
        graphics::drawRect(5.0f, 8.0f, 2.0f, 0.8f, br);

        graphics::Brush back_br;
        back_br.texture = getFullAssetPath("back.png");
        back_br.fill_opacity = 1.0f;
        graphics::drawRect(5.0f, 8.0f, 0.6f, 0.6f, back_br);
        return;
    }
}

void GameState::update(float dt) {
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = ms.cur_pos_x / 80.0f;
    float my = ms.cur_pos_y / 80.0f;

    // LOGIC ΓΙΑ MENU
    if (m_status == STATUS_MENU) {
        if (ms.button_left_pressed) {
            if (mx >= 3.5f && mx <= 6.5f && my >= 4.5f && my <= 5.5f) {
                m_status = STATUS_PLAYING;
                m_victory = false;
                m_current_level_count = 1; // Reset προόδου
                graphics::playSound(getFullAssetPath("start.mp3"), 0.5f, false);
            }
            else if (mx >= 3.5f && mx <= 6.5f && my >= 6.0f && my <= 7.0f) {
                m_status = STATUS_SETTINGS;
                graphics::playSound(getFullAssetPath("click.mp3"), 0.5f, false);
            }
        }
        return;
    }

    // LOGIC ΓΙΑ SETTINGS
    if (m_status == STATUS_SETTINGS) {
        if (ms.button_left_pressed) {
            if (my >= 4.4f && my <= 5.6f) {
                if (mx >= 2.9f && mx <= 4.1f) m_max_levels = 3;
                else if (mx >= 4.4f && mx <= 5.6f) m_max_levels = 5;
                else if (mx >= 5.9f && mx <= 7.1f) m_max_levels = 10;
                graphics::playSound(getFullAssetPath("click.mp3"), 0.5f, false);
            }
            if (mx >= 4.0f && mx <= 6.0f && my >= 7.6f && my <= 8.4f) {
                m_status = STATUS_MENU;
                graphics::playSound(getFullAssetPath("click.mp3"), 0.5f, false);
            }
        }
        return;
    }

    // LOGIC ΓΙΑ PLAYING
    if (m_status == STATUS_PLAYING) {
        if (m_player) m_player->update(dt);
        if (m_current_level) m_current_level->update(dt);
    }
}

void GameState::nextLevel() {
    // Έλεγχος τερματισμού
    if (m_current_level_count >= m_max_levels) {
        m_victory = true;
        m_status = STATUS_MENU;
        printf("GAME COMPLETED! Victory!\n");
        return;
    }

    m_current_level_count++;

    if (m_current_level) {
        delete m_current_level;
        m_current_level = nullptr;
    }

    m_current_level = new Level();
    m_current_level->init();

    if (m_player) {
        m_player->m_pos_x = 0.5f;
        m_player->m_pos_y = 0.5f;
    }
    printf("Level %d started!\n", m_current_level_count);
}