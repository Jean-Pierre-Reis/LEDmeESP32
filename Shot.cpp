class Shot {
public:
    void initialize(double startX, double startY, double vectorX, double vectorY);
    void move();
    void draw();
    bool isActive();

private:
    double x;
    double y;
    double vectorX;
    double vectorY;
    byte status;
    // Outros atributos do tiro...
};
