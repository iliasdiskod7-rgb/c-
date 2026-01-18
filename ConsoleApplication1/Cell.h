#pragma once
#include "gameobject.h"
#include "util.h"
#include <sgg/graphics.h>

class Cell : public GameObject, public Box {
public:
    bool m_is_obstacle = false;
    int m_id;
    static int m_id_generator;
    float m_destruction_anim = 0.0f;
    bool m_is_fading = false;
    graphics::Brush m_brush;
    Cell(float x, float y, float size);
    void init() override;
    void update(float dt) override;
    void draw() override;
};