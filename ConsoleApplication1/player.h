#pragma once
#include "gameobject.h"
#include "util.h"
#include <sgg/graphics.h>

class Player : public GameObject, public Box {
   graphics::Brush m_brush_player;
public: // Change access modifier to allow access to derived classes or other classes like Level
   float m_old_x;
   float m_old_y;
   float m_velocity = 5.0f; // Ταχύτητα κίνησης
public:
   Player(std::string name) : GameObject(name) {}

   void init() override;
   void update(float dt) override;
   void draw() override;
};