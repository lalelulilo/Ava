/* In-Game Console */

#ifndef __SYS_CONSOLE__
#define __SYS_CONSOLE__

class Console {
public:G
    Console( int layer );

    /* Show the console and start it's loop */
    int show();
private:
    int layer;
    int runConsole;
};

#endif /* __SYS_CONSOLE__ */
