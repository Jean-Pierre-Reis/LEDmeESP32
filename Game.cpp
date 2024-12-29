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
    // Outros atributos do jogo...

    PlayerShip player;
    std::vector<Enemy> enemies;
    std::vector<Shot> shots;
    std::vector<PowerUp> powerUps;
    Display display;
    SoundManager soundManager;
};
