#ifndef VGA_H
#define VGA_H

enum GfxMode {
    MODE13H
};

enum COLORS {
    BLACK,		    /* dark colors */
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,		/* light colors */
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

void vgaInitGfxMode(int mode);

void vgaPlotPixel(int x, int y, unsigned short color);

void vgaPlotPixelf(int x, int y, unsigned short color);

void vgaclrscreen();

void vgaclroffscreen();

void vgaWaitVRetrace();

void vgaSwapBuffers();

#endif