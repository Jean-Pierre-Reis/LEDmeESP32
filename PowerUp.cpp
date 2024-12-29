class PowerUp {
public:
    void initialize(double startX, double startY, byte type);
    void move();
    void draw();
    bool isActive();

private:
    double x;
    double y;
    byte type;
    bool active;
    // Outros atributos do power-up...
};
