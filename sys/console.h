/* In-Game Console */

#ifndef __SYS_CONSOLE__
#define __SYS_CONSOLE__

class Console {
public:
    Console( int layerInit, int widthInit, int heightInit );

    /* Show the console and start it's loop */
    void show();

private:
    char *textBuffer;
    int textBufferSize;

    color_t fgColor;
    color_t bgColor;

    int layer;
    int width;
    int height;
    int runConsole;
};

#endif /* __SYS_CONSOLE__ */
