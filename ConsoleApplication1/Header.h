#pragma once
#include <string>
#include <sgg/graphics.h>

class GameState
{
private:
    // Singleton: Στατικός δείκτης στο μοναδικό αντικείμενο
    static GameState* m_unique_instance;

    // Δεδομένα καμβά και assets
    std::string m_asset_path = "assets\\";
    float m_canvas_width = 10.0f;
    float m_canvas_height = 10.0f;

    // Private constructor
    GameState();

public:
    // Καθολικές μεταβλητές κίνησης και debugging
    float m_global_offset_x = 0.0f;
    float m_global_offset_y = 0.0f;
    bool m_debugging = false;

    // Δείκτες στα βασικά στοιχεία
    class Player* m_player = nullptr;
    class Level* m_current_level = nullptr;

    // Βασικές μέθοδοι
    void init();
    void draw();
    void update(float dt);

    // Στατική μέθοδος για πρόσβαση στο Singleton
    static GameState* getInstance();

    // Βοηθητικές μέθοδοι
    std::string getFullAssetPath(const std::string& asset) { return m_asset_path + asset; }
    float getCanvasWidth() { return m_canvas_width; }
    float getCanvasHeight() { return m_canvas_height; }
};
