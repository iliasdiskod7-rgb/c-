#include "gameobject.h"
#include "gamestate.h" // Απαραίτητο για να ξέρει τι είναι το GameState

// Αρχικοποίηση της στατικής μεταβλητής στην αρχή του προγράμματος
int GameObject::m_next_id = 1;

// Υλοποίηση του Constructor
GameObject::GameObject(const std::string& name)
    : m_name(name) // Αρχικοποίηση ονόματος
{
    // Κάθε αντικείμενο παίρνει έναν δείκτη στην κεντρική κατάσταση
    m_state = GameState::getInstance();

    // Δίνουμε ένα μοναδικό νούμερο ταυτότητας και αυξάνουμε το στατικό ID
    m_id = m_next_id++;
}