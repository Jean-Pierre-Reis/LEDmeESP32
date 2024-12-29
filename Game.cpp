#include <vector>
#include "Display.h"
#include "SoundManager.h"
#include "PlayerShip.h"
#include "Enemy.h"
#include "Shot.h"
#include "PowerUp.h"

class Game {
public:
    void setup();
    void loop();
    void selectDifficulty();
    void selectLevel();

private:
    byte level;
    byte maxLevelReached;
    byte difficulty;
    long score;
    long highScore;

    PlayerShip player;
    std::vector<Enemy> enemies;
    std::vector<Shot> shots;
    std::vector<PowerUp> powerUps;
    Display display;
    SoundManager soundManager;

    void spawnEnemies();
    void handleCollisions();
    void updateScore();
    void checkGameOver();
};

void Game::setup() {
    display.initialize();
    soundManager.playTone(1024, 200);
    player.initialize();

    level = 1;
    maxLevelReached = 1;
    difficulty = 1;
    score = 0;
    highScore = 0;

    enemies.clear();
    shots.clear();
    powerUps.clear();
    spawnEnemies();
}

void Game::loop() {
    // Atualizar jogador
    player.move();
    player.draw();

    // Atualizar inimigos
    for (auto& enemy : enemies) {
        enemy.move();
        enemy.draw();
    }

    // Atualizar tiros
    for (auto& shot : shots) {
        shot.move();
        if (shot.isActive()) {
            shot.draw();
        }
    }

    // Atualizar power-ups
    for (auto& powerUp : powerUps) {
        powerUp.move();
        if (powerUp.isActive()) {
            powerUp.draw();
        }
    }

    // Lidar com colisões
    handleCollisions();

    // Atualizar score e verificar fim de jogo
    updateScore();
    checkGameOver();
}

void Game::selectDifficulty() {
    // Lógica para selecionar dificuldade
    display.clearScreen();
    display.drawText(1, 1, "Select Difficulty:");
    difficulty = 1; // Placeholder para a dificuldade inicial
    // Aguardando interação do jogador para ajustar dificuldade...
}

void Game::selectLevel() {
    // Lógica para selecionar nível
    display.clearScreen();
    display.drawText(1, 1, "Select Level:");
    level = 1; // Placeholder para o nível inicial
    // Aguardando interação do jogador para ajustar nível...
}

void Game::spawnEnemies() {
    // Lógica para gerar inimigos com base no nível e dificuldade
    for (int i = 0; i < level * difficulty; ++i) {
        Enemy enemy;
        enemy.initialize(rand() % 3); // Tipo aleatório de inimigo
        enemies.push_back(enemy);
    }
}

void Game::handleCollisions() {
    // Lógica para lidar com colisões entre tiros, inimigos e o jogador
    for (auto& shot : shots) {
        if (!shot.isActive()) continue;

        for (auto& enemy : enemies) {
            if (/* colisão entre shot e enemy */) {
                enemy.explode();
                shot.status = 0; // Desativar o tiro
                score += 100;
            }
        }
    }

    for (auto& enemy : enemies) {
        if (/* colisão entre player e enemy */) {
            player.explode();
            checkGameOver();
            return;
        }
    }
}

void Game::updateScore() {
    if (score > highScore) {
        highScore = score;
    }
    display.drawText(0, 0, ("Score: " + std::to_string(score)).c_str());
}

void Game::checkGameOver() {
    if (player.getShieldEnergy() <= 0) {
        display.clearScreen();
        display.drawText(5, 5, "Game Over!");
        soundManager.playTone(200, 500);
        // Reiniciar ou retornar ao menu inicial...
    }
}

// Função principal do loop
void loop() {
    static Game game;
    game.loop();
}
