#ifndef SGL_H
#define SGL_H

void sglSwapBuffers();

void sglClear();

void sglDrawPixel(int x, int y, unsigned short color);

void sglDrawLine(int x0, int y0, int x1, int y1, unsigned short color);

void sglDrawRectangle(int x, int y, int width, int height, unsigned short color);

void sglDrawCircle(int xc, int yc, int r, unsigned short color);

void sglDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

void sglDrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

#endif