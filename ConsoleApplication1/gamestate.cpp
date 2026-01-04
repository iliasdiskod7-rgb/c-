#include "gamestate.h"
#include "level.h"
#include "player.h"


// Αρχικοποίηση του στατικού δείκτη σε nullptr
GameState* GameState::m_unique_instance = nullptr;

GameState::GameState() {}

// Υλοποίηση της getInstance
GameState* GameState::getInstance()
{
    if (!m_unique_instance)
        m_unique_instance = new GameState();
    return m_unique_instance;
}

void GameState::init()
{
    // Δημιουργία και αρχικοποίηση του επιπέδου (Grid)
    m_current_level = new Level();
    m_current_level->init();

    // Δημιουργία και αρχικοποίηση του παίκτη
    m_player = new Player("Player1");
    m_player->init();
}

void GameState::draw()
{
    // Έλεγχος αν υπάρχει επίπεδο πριν τη σχεδίαση
    if (!m_current_level) return;

    // Σχεδίαση επιπέδου και παίκτη
    m_current_level->draw();
    if (m_player) m_player->draw();
}

void GameState::update(float dt) {
    if (dt > 500) return; // Προστασία από κολλήματα

    if (m_player) {
        m_player->update(dt); // ΑΥΤΗ η γραμμή κουνάει τον παίκτη
    }

    if (m_current_level) {
        m_current_level->update(dt);
    }
}
   void GameState::nextLevel(){
        // 1. Διαγραφή τρέχοντος επιπέδου (Memory Management) 
        if (m_current_level) {
            delete m_current_level;
            m_current_level = nullptr;
        }

        // 2. Δημιουργία νέου επιπέδου
        m_current_level = new Level();
        m_current_level->init();

        // 3. Επαναφορά παίκτη στην αρχή (0.5, 0.5)
        if (m_player) {
            m_player->m_pos_x = 0.5f;
            m_player->m_pos_y = 0.5f;
        }

        printf("Level Switched!\n");
    }
