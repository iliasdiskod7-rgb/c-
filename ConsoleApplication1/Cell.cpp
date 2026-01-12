#include "cell.h"
#include "gamestate.h"

// Αρχικοποίηση του static generator
int Cell::m_id_generator = 0;

Cell::Cell(float x, float y, float size) : GameObject("Cell") {
    m_pos_x = x;
    m_pos_y = y;
    m_width = size;
    m_height = size;
    m_id = m_id_generator++;
}

void Cell::init() {
    // Αρχικές ρυθμίσεις αν χρειάζονται
    m_destruction_anim = 0.0f;
    m_is_fading = false;
}

void Cell::update(float dt) {
    // Αν το κελί βρίσκεται σε φάση "σβησίματος"
    if (m_is_fading) {
        // Αυξάνουμε την πρόοδο του animation με βάση το χρόνο (dt)
        m_destruction_anim += dt / 300.0f; // Το εφέ διαρκεί 300ms

        if (m_destruction_anim >= 1.0f) {
            m_destruction_anim = 1.0f;
            m_is_fading = false;
            m_is_obstacle = false; // Τελική αφαίρεση του εμποδίου
        }
    }
}

void Cell::draw() {
    graphics::Brush br;
    // Αν δεν είναι εμπόδιο και δεν σβήνει, δεν σχεδιάζουμε τίποτα
    if (!m_is_obstacle && !m_is_fading) {



    // Ρύθμιση Χρώματος (π.χ. Γκρι για εμπόδια)
    br.fill_color[0] = 0.8f;
    br.fill_color[1] = 0.8f;
    br.fill_color[2] = 0.8f;

    // Εφέ Διαφάνειας: Όσο αυξάνεται το animation, τόσο σβήνει το κουτάκι
    br.fill_opacity = 0.5f;
    br.outline_opacity = 0.2f;
    graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, br);
    return;
}
    // Εφέ Συρρίκνωσης (Scaling): Μικραίνουμε το πλάτος/ύψος
    float current_w = m_width * (1.0f - m_destruction_anim);
    float current_h = m_height * (1.0f - m_destruction_anim);

    // Σχεδίαση του κελιού
    graphics::drawRect(m_pos_x, m_pos_y, current_w, current_h, br);
}