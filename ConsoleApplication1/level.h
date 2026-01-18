#pragma once
#pragma once
#include "gameobject.h"
#include "goal.h"
#include <vector>

class Level : public GameObject {
    std::vector<class Cell*> m_cells;
    class Goal* m_goal = nullptr;

public:
    Level(const std::string& name = "GridLevel") : GameObject(name) {}
    ~Level(); 
    void init() override;
    void update(float dt) override;
    void draw() override;
	void checkCollisions();
};