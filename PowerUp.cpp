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
