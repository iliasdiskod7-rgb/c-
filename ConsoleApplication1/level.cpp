#include "level.h"
#include "cell.h"
#include "gamestate.h"
void Level::init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Cell* c = new Cell(i + 0.5f, j + 0.5f, 1.0f);
            bool is_start_zone = (i == 0 && j == 0);
            bool is_goal_zone = (i == 9 && j == 9);
            if (!is_start_zone && !is_goal_zone && rand() % 5 == 0) c->m_is_obstacle = true;
            m_goal = new Goal(9.5f, 9.5f);
            m_goal->init();
            m_cells.push_back(c);
        }
    }
}
void Level::checkCollisions() {
    Player* player = m_state->m_player;
    if (!player || !m_goal) return;
    if (player->intersect(*m_goal)) {
        m_state->nextLevel();
        return; 
    }
    for (auto cell : m_cells) {
        if (cell->m_is_obstacle) {
            if (player->intersect(*cell)) {
                graphics::playSound(m_state->getFullAssetPath("error.mp3"), 0.5f, false);
                player->m_pos_x = player->m_old_x;
                player->m_pos_y = player->m_old_y; 
                if (m_state->m_debugging) {
                    printf("Collision with obstacle %d!\n", cell->m_id);
                }
            }
        }
    }
}

void Level::draw() {
    for (auto cell : m_cells) {
        cell->draw();
    }
    if (m_goal) m_goal->draw();
}

void Level::update(float dt) {
    for (auto cell : m_cells) cell->update(dt);
    graphics::MouseState ms;
    graphics::getMouseState(ms);
    float mx = graphics::windowToCanvasX(ms.cur_pos_x);
    float my = graphics::windowToCanvasY(ms.cur_pos_y);
    Box mouse_box;
    mouse_box.m_pos_x = mx;
    mouse_box.m_pos_y = my;
    mouse_box.m_width = 0.00001f;
    mouse_box.m_height = 0.00001f;
    if (ms.button_left_pressed) {
        for (auto cell : m_cells) {
            if (cell->m_is_obstacle && cell->intersect(mouse_box)) {
				graphics::playSound(m_state->getFullAssetPath("destroy.mp3"), 0.5f, false);
                cell->m_is_fading = true; 
                cell->m_is_obstacle = false; 
                break; 
            }

        }

    }


    if (ms.button_right_pressed) {
        int gx = (int)floor(mx);
        int gy = (int)floor(my);

        for (auto cell : m_cells) {
            int cx = (int)floor(cell->m_pos_x);
            int cy = (int)floor(cell->m_pos_y);

            if (cx == gx && cy == gy) {
                cell->m_is_obstacle = false;
                break;
            }
        }
    }

    checkCollisions();
    if (m_goal) {
        for (auto cell : m_cells) {
            if (cell->intersect(*m_goal)) {
                cell->m_is_obstacle = false;
                break;
            }
        }
    }
    for (auto cell : m_cells) {
        if (cell->intersect(*m_goal)) {
            cell->m_is_obstacle = false;
            break;
        }
        static bool n_was_down = false;
        bool n_down = graphics::getKeyState(graphics::SCANCODE_N);

        if (n_down && !n_was_down) {
            GameState::getInstance()->m_status = GameState::STATUS_ROUND_END;
        }
        n_was_down = n_down;
    }
}

Level::~Level() {
    for (auto cell : m_cells) {
        delete cell;
    }
    if (m_goal) delete m_goal;
    m_cells.clear();
}