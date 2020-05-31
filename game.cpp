#include "game.h"

const uint32_t EEPROM_MAGIC = 0xF6E290C4;

int Game::reset() {
    solved_mask[0] = 0;
    solved_mask[1] = 0;
    num_solved = 0;
    target_solved = 0;
    time_left = 9999;
}

void Game::loadHighScore() {
    uint32_t v;
    EEPROM.get(256, v);
    if(v != EEPROM_MAGIC) {
        EEPROM.put(256, EEPROM_MAGIC);
        high_score = 0;
        setHighScore();
        return;
    }
    EEPROM.get(264, high_score);
}

void Game::setHighScore() {
    EEPROM.put(264, high_score);
}
