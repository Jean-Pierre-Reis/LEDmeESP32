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
