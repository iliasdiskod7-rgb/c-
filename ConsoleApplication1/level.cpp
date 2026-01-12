#include "level.h"
#include "cell.h"
#include "gamestate.h"
//#include <iostream>
/*Το level.cpp λέει:

πώς στήνεται ο χάρτης,
πώς αντιδρά στο ποντίκι,
και πώς συγκρούεται ο παίκτης με τον κόσμο.*/
void Level::init() {
    // Δημιουργία Grid 10x10
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Δυναμική δημιουργία (new) [cite: 76]
            // Το i+0.5 και j+0.5 τοποθετεί τα κελιά ακριβώς στα κέντρα των μονάδων
            Cell* c = new Cell(i + 0.5f, j + 0.5f, 1.0f);
            // 1. Ορισμός θέσεων που πρέπει να μείνουν ΠΑΝΤΑ κενές
            // Εκκίνηση παίκτη: (0,0) και Στόχος: (9,9)
            bool is_start_zone = (i == 0 && j == 0);
            bool is_goal_zone = (i == 9 && j == 9);
            // Παράδειγμα: Κάνε μερικά τυχαία εμπόδια
            if (!is_start_zone && !is_goal_zone && rand() % 5 == 0) c->m_is_obstacle = true;
            m_goal = new Goal(9.5f, 9.5f);
            m_goal->init();
            m_cells.push_back(c);
        }
    }
}
void Level::checkCollisions() {
    // Παίρνουμε τον παίκτη από το GameState
    Player* player = m_state->m_player;
    if (!player || !m_goal) return;
    // Έλεγχος αν ο παίκτης έφτασε στον στόχο
    if (player->intersect(*m_goal)) {
        // Καλούμε την αλλαγή επιπέδου στην GameState [cite: 86]
        m_state->nextLevel();
        return; // Διακοπή γιατί το τρέχον Level θα διαγραφεί
    }

    // Ελέγχουμε κάθε κελί του Grid
    for (auto cell : m_cells) {
        // Μας ενδιαφέρουν μόνο τα εμπόδια
        if (cell->m_is_obstacle) {
            // Αν ο παίκτης ακουμπήσει το εμπόδιο
            if (player->intersect(*cell)) {
                graphics::playSound(m_state->getFullAssetPath("error.mp3"), 0.5f, false);
                player->m_pos_x = player->m_old_x;
                player->m_pos_y = player->m_old_y;
                // Απλή λύση: Σταμάτα την κίνηση ή "σπρώξε" τον παίκτη πίσω
                // Για αρχή, ας εκτυπώσουμε ένα μήνυμα debugging όπως ο καθηγητής
                if (m_state->m_debugging) {
                    printf("Collision with obstacle %d!\n", cell->m_id);
                }

                // Εδώ θα μπορούσαμε να προσθέσουμε λογική για να σταματάει ο παίκτης
            }
        }
    }
}

void Level::draw() {
    // Πολυμορφική κλήση της draw για κάθε κελί
    for (auto cell : m_cells) {
        cell->draw();
    }
    if (m_goal) m_goal->draw();
}

void Level::update(float dt) {
    // 1. Ενημέρωση αντικειμένων
    for (auto cell : m_cells) cell->update(dt);

    // 2. Λήψη κατάστασης ποντικιού
    graphics::MouseState ms;
    graphics::getMouseState(ms);

    // Μετατροπή των pixels σε συντεταγμένες καμβά (0-10)
    // Υποθέτουμε παράθυρο 800x800 και καμβά 10x10
    float mx = ms.cur_pos_x / 80.0f;
    float my = ms.cur_pos_y / 80.0f;

    // Δημιουργούμε ένα εικονικό "Box" στη θέση του ποντικιού για να δούμε τι πατάμε
    Box mouse_box;
    mouse_box.m_pos_x = mx;
    mouse_box.m_pos_y = my;
    mouse_box.m_width = 0.00001f;
    mouse_box.m_height = 0.00001f;

    // 3. Έλεγχος για κλικ 
    if (ms.button_left_pressed) {
        for (auto cell : m_cells) {
            // Αν το ποντίκι "ακουμπάει" το κελί
            if (cell->m_is_obstacle && cell->intersect(mouse_box)) {
                cell->m_is_fading = true; // Ενεργοποίηση εφέ
                cell->m_is_obstacle = false; // Αφαίρεση εμποδίου ΑΜΕΣΩΣ για το gameplay
                break; // Σταματάμε στο πρώτο κελί που βρήκαμε
            }
            
        }

    }


    if (ms.button_right_pressed) {
        if (m_goal) {
            // “Κούμπωσε” το goal στο κέντρο του κελιού που πατάς
           // m_goal->m_pos_x = floor(mx) + 0.5f;
           // m_goal->m_pos_y = floor(my) + 0.5f;
            if (ms.button_right_pressed) {

                int gx = (int)floor(mx);
                int gy = (int)floor(my);


                // ξε-γίνεται obstacle το κελί
                for (auto cell : m_cells) {
                    int cx = (int)floor(cell->m_pos_x);
                    int cy = (int)floor(cell->m_pos_y);

                    if (cx == gx && cy == gy) {
                        cell->m_is_obstacle = false;
                        break;
                    }
                }
            }

            // Κάνε το κελί του goal ΠΑΝΤΑ ελεύθερο
            for (auto cell : m_cells) {
                if (cell->intersect(*m_goal)) {
                    cell->m_is_obstacle = false;
                    break;
                }
            }
        }
    }



    /*if (ms.button_right_pressed) {
        // Μετακίνηση του στόχου (Goal) στη θέση του κλικ
        if (m_goal) {
            // Στρογγυλοποίηση για να "κουμπώσει" ακριβώς στο κέντρο του κελιού
            m_goal->m_pos_x = floor(mx) + 0.5f;
            m_goal->m_pos_y = floor(my) + 0.5f;
        }
    }*/

    checkCollisions();
}

Level::~Level() {
    // Υποχρεωτικός καθαρισμός δυναμικής μνήμης
    for (auto cell : m_cells) {
        delete cell;
    }
    if (m_goal) delete m_goal;
    m_cells.clear();
}