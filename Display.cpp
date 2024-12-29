class Display {
public:
    void initialize();
    void drawM(int x, int y);
    void drawT(int x, int y);
    void clearScreen();
    void drawText(int x, int y, const char* text);

private:
    MatrixPanel_I2S_DMA* dma_display;
    // Outros atributos e métodos de display...
};
