#include "player.h"
#include "gamestate.h"

void Player::init() {
    // Αρχική θέση στο κέντρο ενός κελιού
    m_pos_x = 0.5f;
    m_pos_y = 0.5f;
    m_width = 0.6f;  // Λίγο μικρότερος από το κελί για να χωράει
    m_height = 0.6f;

    m_brush_player.fill_color[0] = 1.0f; // Κόκκινος παίκτης
    m_brush_player.fill_color[1] = 0.2f;
    m_brush_player.fill_color[2] = 0.2f;
    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
}

void Player::update(float dt) {
    // Μετατροπή των ms σε seconds
    float delta_time = dt / 1000.0f;
    m_old_x = m_pos_x;
    m_old_y = m_pos_y;

    // Έλεγχος πλήκτρων WASD
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        m_pos_x -= m_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        m_pos_x += m_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        m_pos_y -= m_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        m_pos_y += m_velocity * delta_time;
    }

    // Περιορισμός παίκτη μέσα στα όρια του καμβά (0-10)
    if (m_pos_x < 0) m_pos_x = 0;
    if (m_pos_x > 10) m_pos_x = 10;
    if (m_pos_y < 0) m_pos_y = 0;
    if (m_pos_y > 10) m_pos_y = 10;
}

void Player::draw() {
    // Σχεδίαση του παίκτη
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_player);
}