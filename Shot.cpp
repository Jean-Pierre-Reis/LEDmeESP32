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
