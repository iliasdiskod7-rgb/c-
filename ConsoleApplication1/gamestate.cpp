#include "gamestate.h"
#include "level.h"
#include "player.h"


// Αρχικοποίηση του στατικού δείκτη σε nullptr
GameState* GameState::m_unique_instance = nullptr;//δεν υπάρχει ακόμα GameState

GameState::GameState() {}

// Υλοποίηση της getInstance
GameState* GameState::getInstance()
{
    if (!m_unique_instance)
        m_unique_instance = new GameState();//φτιαχνει ενα pointer
    return m_unique_instance;
}
//όλοι παίρνουν την ίδια διεύθυνση μνήμης
//όλοι δουλεύουν στο ίδιο αντικείμενο

void GameState::init()
//«Αυτή είναι μια συνάρτηση που ανήκει στην κλάση GameState, δεν επιστρέφει τίποτα, και αρχικοποιεί το αντικείμενο GameState.»
{
    // Δημιουργία και αρχικοποίηση του επιπέδου (Grid)
    m_current_level = new Level();
    m_current_level->init();

    // Δημιουργία και αρχικοποίηση του παίκτη
    m_player = new Player("Player1");
    m_player->init();
    std::string music_path = getFullAssetPath("Idea 22 (1).mp3");
    graphics::playMusic(music_path, 0.5f, true);
}

void GameState::draw()
{
    // 1. Σχεδιάζουμε ΠΑΝΤΑ το παιχνίδι πρώτο (το background μας)
    if (m_current_level) m_current_level->draw();
    if (m_player) m_player->draw();

    // 2. Αν είμαστε στο μενού, σχεδιάζουμε το Overlay ΑΠΟ ΠΑΝΩ
    if (m_status == STATUS_MENU) {
        graphics::Brush br;

        // ΕΦΕ ΘΟΛΩΜΑΤΟΣ / ΣΚΟΤΕΙΝΙΑΣΜΑΤΟΣ
        // Χρησιμοποιούμε μαύρο χρώμα με opacity 0.7f για να "χαθεί" το φόντο
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.7f;
        br.outline_opacity = 0.0f;
        graphics::drawRect(5.0f, 5.0f, 10.0f, 10.0f, br);

        // ΣΧΕΔΙΑΣΗ ΚΟΥΜΠΙΟΥ
        br.fill_opacity = 1.0f;
        br.fill_color[0] = 1.0f; br.fill_color[1] = 0.8f; br.fill_color[2] = 0.0f; // Χρυσό
        graphics::drawRect(5.0f, 5.0f, 3.0f, 1.0f, br);

        // ΣΧΕΔΙΑΣΗ ΚΕΙΜΕΝΟΥ "PLAY"
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f; // Μαύρο
        br.texture = getFullAssetPath("xa.ttf");
        // Χαμηλώνουμε το μέγεθος στο 0.6f για να χωρέσει όμορφα
        graphics::drawText(4.3f, 5.2f, 0.6f, "PLAY", br);

        // Προαιρετικά: Ένας τίτλος παιχνιδιού πιο πάνω
        br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
        graphics::drawText(3.2f, 3.0f, 0.8f, "GRID RUNNER", br);

        // ΣΗΜΑΝΤΙΚΟ: Σταματάμε τη draw εδώ αν είμαστε στο μενού
        return;
    }

    // Αν ο κώδικας φτάσει εδώ, σημαίνει ότι m_status == STATUS_PLAYING
    // Δεν χρειάζεται να ξαναγράψεις m_current_level->draw() γιατί το κάναμε στην αρχή!
}

void GameState::update(float dt) {
    if (m_status == STATUS_MENU) {
        graphics::MouseState ms;
        graphics::getMouseState(ms);

        // Μετατροπή ποντικιού σε μονάδες καμβά (0-10)
        float mx = ms.cur_pos_x / 80.0f;
        float my = ms.cur_pos_y / 80.0f;

        if (ms.button_left_pressed) {
            // Έλεγχος αν το κλικ έγινε μέσα στο κουμπί PLAY (που είναι στο κέντρο 5,5)
            if (mx >= 3.5f && mx <= 6.5f && my >= 4.5f && my <= 5.5f) {
                m_status = STATUS_PLAYING;
                graphics::playSound(getFullAssetPath("start.mp3"), 0.5f, false); //
            }
        }
        return; // Όσο είναι μενού, ο παίκτης δεν κουνιέται
    }

    // Κανονικό update αν παίζουμε
    if (m_player) m_player->update(dt);
    if (m_current_level) m_current_level->update(dt);
}
void GameState::nextLevel() {
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