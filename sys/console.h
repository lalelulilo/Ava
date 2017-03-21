/* In-Game Console */

#ifndef __SYS_CONSOLE__
#define __SYS_CONSOLE__

typedef struct {
    char **text;
    int size;        // Size of ring buffer
    int dataSize;    // Size of each text entry
    int idx;         // Current index
} textRingBuffer_t;

class Console {
public:
    Console( int layerInit, int widthInit, int heightInit );
    ~Console();

    /* Show the console and start it's loop */
    void show();

private:
    textRingBuffer_t textBuf;
    char *inputBuf;
    int inputBufSize;

    color_t fgColor;
    color_t bgColor;

    int layer;
    int width;
    int height;
    int runConsole;
};

#endif /* __SYS_CONSOLE__ */
