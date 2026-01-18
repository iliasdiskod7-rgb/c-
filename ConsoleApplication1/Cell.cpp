#include "cell.h"
#include "gamestate.h"
int Cell::m_id_generator = 0;

Cell::Cell(float x, float y, float size) : GameObject("Cell") {
    m_pos_x = x;
    m_pos_y = y;
    m_width = size;
    m_height = size;
    m_id = m_id_generator++;
}

void Cell::init() {
    m_destruction_anim = 0.0f;
    m_is_fading = false;
}

void Cell::update(float dt) {
    if (m_is_fading) {
        m_destruction_anim += dt / 300.0f; 

        if (m_destruction_anim >= 1.0f) {
            m_destruction_anim = 1.0f;
            m_is_fading = false;
            m_is_obstacle = false; 
        }
    }
}

void Cell::draw() {
    graphics::Brush br;
    if (!m_is_obstacle && !m_is_fading) {
    br.fill_color[0] = 0.8f;
    br.fill_color[1] = 0.8f;
    br.fill_color[2] = 0.8f;
    br.fill_opacity = 0.5f;
    br.outline_opacity = 0.2f;
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, br);
    return;
}
    float current_w = m_width * (1.0f - m_destruction_anim);
    float current_h = m_height * (1.0f - m_destruction_anim);
    graphics::drawRect(m_pos_x, m_pos_y, current_w, current_h, br);
}