#pragma once
#pragma once
#include <string>

class GameObject
{
    // Στατική μεταβλητή για να δίνουμε μοναδικό ID σε κάθε αντικείμενο
    static int m_next_id;

protected:
    class GameState* m_state; // Δείκτης στο Singleton GameState
    std::string m_name;       // Το όνομα του αντικειμένου
    bool m_active = true;     // Αν το αντικείμενο είναι ενεργό

public:
    // Constructor που παίρνει το όνομα και αρχικοποιεί το m_state
    GameObject(const std::string& name = "");
    int m_id = 0;             // Το μοναδικό ID του αντικειμένου


    // Virtual μέθοδοι που θα κάνουμε override στις υποκλάσεις (π.χ. Cell, Player)
    virtual void update(float dt) {}
    virtual void init() {}
    virtual void draw() {}

    // Virtual destructor: Απαραίτητος για σωστή διαγραφή από τη μνήμη
    virtual ~GameObject() {}

    // Getters και Setters για την κατάσταση του αντικειμένου
    bool isActive() { return m_active; }
    void setActive(bool a) { m_active = a; }
};