#pragma once
#include "gameobject.h"
#include "util.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box {
   graphics::Brush m_brush_player;
public: 
   float m_old_x;
   float m_old_y;
   float m_velocity = 5.0f; 
public:
   Player(std::string name) : GameObject(name) {}

   void init() override;
   void update(float dt) override;
   void draw() override;
};