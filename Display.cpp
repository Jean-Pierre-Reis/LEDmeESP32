class Display {
public:
    void initialize();
    void drawM(int x, int y);
    void drawT(int x, int y);
    void clearScreen();
    void drawText(int x, int y, const char* text);

private:
    MatrixPanel_I2S_DMA* dma_display;
};

void Display::initialize() {
    dma_display = new MatrixPanel_I2S_DMA();
    dma_display->begin();
    dma_display->clearScreen();
}

void Display::drawM(int x, int y) {
    dma_display->drawPixel(x, y, dma_display->color565(0, 255, 0)); // Desenhar um pixel verde
}

void Display::drawT(int x, int y) {
    dma_display->drawPixel(x, y, dma_display->color565(255, 0, 0)); // Desenhar um pixel vermelho
}

void Display::clearScreen() {
    dma_display->clearScreen();
}

void Display::drawText(int x, int y, const char* text) {
    dma_display->setCursor(x, y);
    dma_display->setTextColor(dma_display->color565(255, 255, 255));
    dma_display->print(text);
}
