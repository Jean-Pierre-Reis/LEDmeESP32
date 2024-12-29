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

class PlayerShip {
public:
    void initialize();
    void move();
    void fire();
    void draw();
    void explode();
    int getShieldEnergy() const;

private:
    byte x;
    byte y;
    int shieldEnergy;

    void handleInput();
};

void PlayerShip::initialize() {
    x = 4;
    y = 14;
    shieldEnergy = 100; // Inicializar energia do escudo
}

void PlayerShip::move() {
    handleInput();
    // Lógica adicional para restringir o movimento dentro dos limites da tela
    if (x < 0) x = 0;
    if (x > 31) x = 31; // Supondo largura de 32 pixels
    if (y < 0) y = 0;
    if (y > 15) y = 15; // Supondo altura de 16 pixels
}

void PlayerShip::handleInput() {
    // Lógica para capturar entrada do jogador
    // Placeholder: Atualizar x e y com base na entrada
    // Por exemplo, lendo botões ou joystick
}

void PlayerShip::fire() {
    // Lógica para disparar um tiro
    // Criar um objeto Shot e inicializá-lo na posição atual da nave
}

void PlayerShip::draw() {
    // Lógica para desenhar a nave na tela
    // Por exemplo, usando display.drawM(x, y);
}

void PlayerShip::explode() {
    shieldEnergy = 0; // Reduzir a energia do escudo para zero
    // Lógica para animação ou efeitos visuais da explosão
}

int PlayerShip::getShieldEnergy() const {
    return shieldEnergy;
}

class Enemy {
public:
    void initialize(byte type);
    void move();
    void draw();
    void fire();
    void explode();

private:
    double x;
    double y;
    byte type;
    int hitPoints;
    byte status;
};

void Enemy::initialize(byte type) {
    this->type = type;
    this->x = rand() % 32; // Posição horizontal aleatória na tela
    this->y = 0; // Começa na parte superior da tela
    this->hitPoints = (type + 1) * 10; // Pontos de vida baseados no tipo
    this->status = 1; // Ativo
}

void Enemy::move() {
    if (status == 0) return; // Inimigo inativo

    y += 0.5; // Move para baixo

    if (y > 15) {
        status = 0; // Desativar se sair da tela
    }
}

void Enemy::draw() {
    if (status == 0) return; // Não desenhar inimigos inativos

    // Lógica para desenhar o inimigo
    // Exemplo: display.drawT((int)x, (int)y);
}

void Enemy::fire() {
    if (status == 0) return; // Não atira se inativo

    // Lógica para disparar tiros do inimigo
}

void Enemy::explode() {
    status = 0; // Desativar inimigo
    hitPoints = 0; // Zerar os pontos de vida
    // Lógica para animação ou efeitos visuais da explosão
}

class Shot {
public:
    void initialize(double startX, double startY, double vectorX, double vectorY);
    void move();
    void draw();
    bool isActive() const;

private:
    double x;
    double y;
    double vectorX;
    double vectorY;
    byte status; // 1 ativo, 0 inativo
};

void Shot::initialize(double startX, double startY, double vectorX, double vectorY) {
    this->x = startX;
    this->y = startY;
    this->vectorX = vectorX;
    this->vectorY = vectorY;
    this->status = 1; // Ativo
}

void Shot::move() {
    if (status == 0) return; // Não mover se inativo

    x += vectorX;
    y += vectorY;

    // Desativar se sair da tela
    if (x < 0 || x >= 32 || y < 0 || y >= 16) {
        status = 0;
    }
}

void Shot::draw() {
    if (status == 0) return; // Não desenhar se inativo

    // Lógica para desenhar o tiro
    // Exemplo: display.drawPixel((int)x, (int)y);
}

bool Shot::isActive() const {
    return status == 1;
}

class PowerUp {
public:
    void initialize(double startX, double startY, byte type);
    void move();
    void draw();
    bool isActive() const;

private:
    double x;
    double y;
    byte type;
    bool active;
};

void PowerUp::initialize(double startX, double startY, byte type) {
    this->x = startX;
    this->y = startY;
    this->type = type;
    this->active = true; // Ativo ao ser inicializado
}

void PowerUp::move() {
    if (!active) return; // Não mover se inativo

    y += 0.2; // Velocidade de movimento do power-up

    if (y > 15) {
        active = false; // Desativar se sair da tela
    }
}

void PowerUp::draw() {
    if (!active) return; // Não desenhar se inativo

    // Lógica para desenhar o power-up
    // Exemplo: display.drawM((int)x, (int)y);
}

bool PowerUp::isActive() const {
    return active;
}

class Display {
public:
    void initialize();
    void drawM(int x, int y);
    void drawT(int x, int y);
    void clearScreen();
    void drawText(int x, int y, const char* text);

private:
    MatrixPanel_I2S_DMA* dma_display;
};

void Display::initialize() {
    dma_display = new MatrixPanel_I2S_DMA();
    dma_display->begin();
    dma_display->clearScreen();
}

void Display::drawM(int x, int y) {
    dma_display->drawPixel(x, y, dma_display->color565(0, 255, 0)); // Desenhar um pixel verde
}

void Display::drawT(int x, int y) {
    dma_display->drawPixel(x, y, dma_display->color565(255, 0, 0)); // Desenhar um pixel vermelho
}

void Display::clearScreen() {
    dma_display->clearScreen();
}

void Display::drawText(int x, int y, const char* text) {
    dma_display->setCursor(x, y);
    dma_display->setTextColor(dma_display->color565(255, 255, 255));
    dma_display->print(text);
}

class SoundManager {
public:
    void playTone(int frequency, int duration);
    void playSoundtrack(int* soundtrack, int length);
    void playBossMelody();

private:
    int currentToneIndex;
};

void SoundManager::playTone(int frequency, int duration) {
    // Lógica para tocar um tom com a frequência e duração especificadas
    // Exemplo: tone(buzzerPin, frequency, duration);
}

void SoundManager::playSoundtrack(int* soundtrack, int length) {
    // Lógica para tocar uma sequência de sons representada por um array de frequências
    for (int i = 0; i < length; ++i) {
        playTone(soundtrack[i], 200); // Toca cada tom por 200 ms
    }
}

void SoundManager::playBossMelody() {
    int bossMelody[] = {440, 880, 660, 440, 550};
    playSoundtrack(bossMelody, sizeof(bossMelody) / sizeof(bossMelody[0]));
}
