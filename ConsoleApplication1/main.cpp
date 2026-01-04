#include <sgg/graphics.h>
#include "gamestate.h"

// Wrapper συναρτήσεις που καλούν τις μεθόδους του Singleton GameState

void draw()
{
    GameState::getInstance()->draw();
}

void update(float dt)
{
    GameState::getInstance()->update(dt);
}

void init()
{
    GameState::getInstance()->init();
}
  

int main(int argc, char** argv)
{
    // 1. Δημιουργία παραθύρου
    graphics::createWindow(800, 800, "Grid Pathfinding Project");

    // 2. Ορισμός των functions που θα τρέχουν σε κάθε frame
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // 3. Ρύθμιση του καμβά (Canvas)
    // Χρησιμοποιούμε 10x10 για να έχουμε εύκολο grid (κάθε κελί = 1.0f μονάδα)
    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(),
        GameState::getInstance()->getCanvasHeight());

    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    // 4. Αρχικοποίηση των δεδομένων μας
    init();

    // 5. Έναρξη του loop της εφαρμογής
    graphics::startMessageLoop();

    return 0;
}