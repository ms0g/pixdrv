#include "sgl.h"
#include "vga.h"

#define abs(x) (x < 0 ? 0 - x : x)

#define ceil(x) ((int)x + 1)

#define floor(x) (int)x

#define signbit(x) (x < 0.0 ? 1 : 0)

#define round(x) signbit(x) ? ceil(x - 0.5) : floor(x + 0.5)

#define swap(x, y) { (x)=(x)^(y); (y)=(x)^(y); (x)=(x)^(y); }

/********************************
 *      Private Functions       *
 ********************************/

static void circle(int xc, int yc, int x, int y, unsigned short color);

static void sglFillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

static void sglFillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color);

/********************************
 *      Public SGL API          *
 ********************************/

void sglSwapBuffers() {
    vgaSwapBuffers();
}

void sglClear() {
    vgaclroffscreen();
}

void sglDrawPixel(int x, int y, unsigned short color) {
    vgaPlotPixelf(x, y, color);
}

void sglDrawLine(int x0, int y0, int x1, int y1, unsigned short color) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    int step = (abs(dx) >= abs(dy)) ? abs(dx) : abs(dy);

    float xinc = dx / (float)(step);
    float yinc = dy / (float)(step);

    float x = x0;
    float y = y0;

    for (int i = 0; i < step; ++i) {
        sglDrawPixel(round(x), round(y), color);
        
        x += xinc;
        y += yinc;
    }
}

void sglDrawRectangle(int x, int y, int width, int height, unsigned short color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            sglDrawPixel(x+i, y+j, color);
        }
    }
}

void sglDrawCircle(int xc, int yc, int r, unsigned short color) {
    int x = 0, y = r; 
    int d = 3 - 2 * r;

    circle(xc, yc, x, y, color); 
    
    while (y >= x) { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } else {
            d = d + 4 * x + 6;
        }
             
        circle(xc, yc, x, y, color);
    }
}

void sglDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    sglDrawLine(x0, y0, x1, y1, color);
    sglDrawLine(x1, y1, x2, y2, color);
    sglDrawLine(x2, y2, x0, y0, color);
}

/**
* Draw a filled triangle with the flat-top/flat-bottom method
* We split the original triangle in two, half flat-bottom and half flat-top
*
*
*          (x0,y0)
*            / \
*           /   \
*          /     \
*         /       \
*        /         \
*   (x1,y1)------(Mx,My)
*       \_           \
*          \_         \
*             \_       \
*                \_     \
*                   \    \
*                     \_  \
*                        \_\
*                           \
*                         (x2,y2)
*
*/
void sglDrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y1 > y2) {
        swap(y1, y2);
        swap(x1, x2);
    }

    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        sglFillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        sglFillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        sglFillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        sglFillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
    }
}

/**
* Draw a filled a triangle with a flat bottom
*
*
*        (x0,y0)
*          / \
*         /   \
*        /     \
*       /       \
*      /         \
*  (x1,y1)------(x2,y2)
*
*/
void sglFillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    // Inverse slope because we're calculating the x changes with respect to y
    float invSlope1 = (float)(x1 - x0) / (y1 - y0);
    float invSlope2 = (float)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x0;
    float xEnd = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; ++y) {
        sglDrawLine(xStart, y, xEnd, y, color);
        xStart += invSlope1;
        xEnd += invSlope2;
    }
}


/**
* Draw a filled a triangle with a flat top
*
*
*  (x0,y0)------(x1,y1)
*      \         /
*       \       /
*        \     /
*         \   /
*          \ /
*        (x2,y2)
*
*/
void sglFillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, unsigned short color) {
    float invSlope1 = (float)(x2 - x0) / (y2 - y0);
    float invSlope2 = (float)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the top vertex (x0,y0)
    float xStart = x2;
    float xEnd = x2;

    // Loop all the scanlines from top to bottom
    for (int y = y2; y >= y0; --y) {
        sglDrawLine(xStart, y, xEnd, y, color);
        xStart -= invSlope1;
        xEnd -= invSlope2;
    }
}

void circle(int xc, int yc, int x, int y, unsigned short color) {
    sglDrawPixel(xc+x, yc+y, color); 
    sglDrawPixel(xc-x, yc+y, color); 
    sglDrawPixel(xc+x, yc-y, color); 
    sglDrawPixel(xc-x, yc-y, color); 
    sglDrawPixel(xc+y, yc+x, color); 
    sglDrawPixel(xc-y, yc+x, color); 
    sglDrawPixel(xc+y, yc-x, color); 
    sglDrawPixel(xc-y, yc-x, color); 
}