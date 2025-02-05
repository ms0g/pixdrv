#ifndef SGL_H
#define SGL_H

void sglSwapBuffers();

void sglClear(unsigned short color);

void sglPutPixel(int x, int y, unsigned short color);

void sglDrawLine(int x0, int y0, int x1, int y1, unsigned short color);

void sglDrawRect(int x, int y, int width, int height, unsigned short color);

void sglDrawCircle(int xc, int yc, int r, unsigned short color);

void sglDrawTri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

void sglDrawFilledTri(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

#endif