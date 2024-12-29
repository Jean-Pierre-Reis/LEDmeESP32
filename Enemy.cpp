class Enemy {
public:
    void initialize(byte type);
    void move();
    void draw();
    void fire();

private:
    double x;
    double y;
    byte type;
    int hitPoints;
    byte status;
    // Outros atributos do inimigo...

    void explode();
};
