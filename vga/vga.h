#ifndef VGA_H
#define VGA_H

enum GfxMode {
    MODE13H,
    MODE12H,
    MODE03H
};

enum COLORS {
    BLACK,          /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,       /* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

void xvInitGfxMode(int mode);

void xvPlotPixel(int x, int y, unsigned short color);

void xvPlotPixelf(int x, int y, unsigned short color);

void xvclrscreen(unsigned short color);

void xvclroffscreen(unsigned short color);

void xvWaitVRetrace();

void xvSwapBuffers();

#endif