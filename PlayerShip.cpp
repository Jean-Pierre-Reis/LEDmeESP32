class PlayerShip {
public:
    void initialize();
    void move();
    void fire();
    void draw();

private:
    byte x;
    byte y;
    int shieldEnergy;
    // Outros atributos da nave...

    void explode();
};
