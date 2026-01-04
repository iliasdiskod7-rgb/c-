#pragma once
#pragma once
#include "gameobject.h"
#include "goal.h"
#include <vector>

class Level : public GameObject {
    // STL Container για τα κελιά (Πολυμορφισμός με δείκτες)
    std::vector<class Cell*> m_cells;
    class Goal* m_goal = nullptr;

public:
    Level(const std::string& name = "GridLevel") : GameObject(name) {}
    ~Level(); // Destructor για καθαρισμό μνήμης

    void init() override;
    void update(float dt) override;
    void draw() override;
	void checkCollisions();
};