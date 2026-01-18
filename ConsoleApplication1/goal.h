
#pragma once
#include "gameobject.h"
#include "util.h"
#include <sgg/graphics.h>
#include "player.h"

class Goal : public GameObject, public Box {
    graphics::Brush m_brush_goal;

public:
    Goal(float x, float y) : GameObject("Goal") {
        m_pos_x = x;
        m_pos_y = y;
        m_width = 0.7f;
        m_height = 0.7f;
    }

    void init() override {
        m_brush_goal.fill_color[0] = 0.2f; 
        m_brush_goal.fill_color[1] = 0.2f;
        m_brush_goal.fill_color[2] = 1.0f;
        m_brush_goal.fill_opacity = 1.0f;
    }

    void draw() override {
        graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_goal);
    }
};