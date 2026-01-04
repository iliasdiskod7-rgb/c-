#pragma once
#include "gameobject.h"
#include "util.h" // Για το struct Box
#include <sgg/graphics.h>

class Cell : public GameObject, public Box {
public:
    bool m_is_obstacle = false;
    graphics::Brush m_brush;

    Cell(float x, float y, float size) : GameObject("Cell") {
        m_pos_x = x;
        m_pos_y = y;
        m_width = size;
        m_height = size;
    }

    void draw() override {
        // Αν είναι εμπόδιο, το βάφουμε σκούρο, αλλιώς ανοιχτό
        m_brush.fill_color[0] = m_is_obstacle ? 0.2f : 0.8f;
        m_brush.fill_color[1] = m_is_obstacle ? 0.2f : 0.8f;
        m_brush.fill_color[2] = m_is_obstacle ? 0.2f : 0.8f;
        m_brush.fill_opacity = 1.0f;
        m_brush.outline_opacity = 0.5f; // Περίγραμμα για να φαίνεται το grid

        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush);
    }
};