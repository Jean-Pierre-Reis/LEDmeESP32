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
    void explode();
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
