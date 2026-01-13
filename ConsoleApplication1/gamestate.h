#pragma once
#include <string>
#include <sgg/graphics.h>

class GameState
{
private:
    // Singleton: Στατικός δείκτης στο μοναδικό αντικείμενο
    static GameState* m_unique_instance;

    // Τα βασικά δεδομένα της εφαρμογής
    std::string m_asset_path = "assets\\";
    float m_canvas_width = 10.0f; // Ορίζουμε μέγεθος 10x10 για το grid σας
    float m_canvas_height = 10.0f;

    // Private constructor για να μην μπορεί κανείς να φτιάξει άλλο αντικείμενο
    GameState();

public:
    // Καθολικές μεταβλητές για την κίνηση της κάμερας και το debugging
    enum status_t {STATUS_MENU,STATUS_PLAYING,STATUS_SETTINGS};
	status_t m_status = STATUS_MENU;
    float m_global_offset_x = 0.0f;
    float m_global_offset_y = 0.0f;
    bool m_play_hover = false;
    bool m_debugging = false;
    int m_max_levels = 3;
    bool m_settings_hover = false;
    int m_current_level_count = 0;
    bool m_victory = false;

    // Δείκτες στον παίκτη και το επίπεδο
    class Player* m_player = nullptr;
    class Level* m_current_level = nullptr;

    // Οι βασικές μέθοδοι ροής
    void init();
    void draw();
    void update(float dt);
	void nextLevel();

    // Η μέθοδος πρόσβασης στο Singleton
    static GameState* getInstance();

    // Βοηθητικές μέθοδοι για assets και διαστάσεις
    std::string getFullAssetPath(const std::string& asset) { return m_asset_path + asset; }
    float getCanvasWidth() { return m_canvas_width; }
    float getCanvasHeight() { return m_canvas_height; }
};
