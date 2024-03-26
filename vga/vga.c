#include "vga.h"
#include "io.h"
#include "mode13.h"

#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ			0x3C1
#define	VGA_STATUS_READ		0x3DA
#define	VGA_MISC_WRITE		0x3C2
#define	VGA_MISC_READ		0x3CC

/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5

#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_SEQ_REGS	5

/****************************
 *		VRAM Address		*
 ****************************/

static u8* VRAM = (u8 *) 0xA0000;

/**
 * Backbuffer
 * Extended memory area 0x00100000 - 0x00EFFFFF
 * https://wiki.osdev.org/Memory_Map_(x86)
 */
static u8* offscreen = (u8 *) 0x00100;

/**
 * Some globals 
 */
static unsigned int width;
static unsigned int height;
static unsigned int vram_size;

/********************************
 *		Private Functions		*
 ********************************/

static void initRegs(const ExternalGeneral* ext, const Sequencer* seq, CRTController* crtc, const GraphicsController* gfxc, const AttributeController* attrc);

/********************************
 *		Public Driver API		*
 ********************************/
 
void vgaInitGfxMode(int mode) {
	switch (mode) {
        case MODE13H:
			width = 320;
			height = 200;
			vram_size = width * height;
            
			initRegs(&extRegs13, &seqRegs13, &crtcRegs13, &gfxcRegs13, &attrcRegs13);
            break;
        default:
            break;
    }
	for (int i = 0; i < vram_size; ++i) {
		offscreen[i] = 0x00;
    }
}

void vgaPlotPixel(int x, int y, unsigned short color) {
    unsigned short offset = width * y + x;
    VRAM[offset] = color;
}

void vgaPlotPixelf(int x, int y, unsigned short color) {
	unsigned short offset = width * y + x;
	offscreen[offset] = color;
}

void vgaclrscreen() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vgaPlotPixel(i, j, BLACK);
		}
	}
}

void vgaclroffscreen() {
	for (int i = 0; i < vram_size; ++i) {
		offscreen[i] = 0x00;
	}
}

void vgaWaitVRetrace() {
    while (insb(VGA_STATUS_READ) & 0x08);
    while (!(insb(VGA_STATUS_READ) & 0x08)); 
}

void vgaSwapBuffers() {
	vgaWaitVRetrace();

    for (int i = 0; i < vram_size; ++i) {
        VRAM[i] = offscreen[i];
    }
}

void initRegs(const ExternalGeneral* ext, const Sequencer* seq, CRTController* crtc, const GraphicsController* gfxc, const AttributeController* attrc) {
	unsigned int i;
	
	// write MISCELLANEOUS reg
	outb(VGA_MISC_WRITE, ext->miscOutput);
	// write SEQUENCER regs
	for (i = 0; i < VGA_NUM_SEQ_REGS; ++i) {
		outb(VGA_SEQ_INDEX, i);
		outb(VGA_SEQ_DATA, seq->m[i]);
	}
		
	// unlock CRTC registers
	outb(VGA_CRTC_INDEX, 0x03);
	outb(VGA_CRTC_DATA, insb(VGA_CRTC_DATA) | 0x80);
	outb(VGA_CRTC_INDEX, 0x11);
	outb(VGA_CRTC_DATA, insb(VGA_CRTC_DATA) & ~0x80);
	// make sure they remain unlocked
	crtc->startHorizontalBlanking |= 0x80;
	crtc->cursorStart &= ~0x80;
	// write CRTC regs
	for (i = 0; i < VGA_NUM_CRTC_REGS; ++i) {
		outb(VGA_CRTC_INDEX, i);
		outb(VGA_CRTC_DATA, crtc->m[i]);
	}

	// write GRAPHICS CONTROLLER regs
	for (i = 0; i < VGA_NUM_GC_REGS; ++i) {
		outb(VGA_GC_INDEX, i);
		outb(VGA_GC_DATA, gfxc->m[i]);
	}

	// write ATTRIBUTE CONTROLLER regs
	for (int i = 0; i < VGA_NUM_AC_REGS; ++i) {
		(void)insb(VGA_STATUS_READ);
		outb(VGA_AC_INDEX, i);
		outb(VGA_AC_WRITE, attrc->m[i]);
	}
		
	// lock 16-color palette and unblank display
	(void)insb(VGA_STATUS_READ);
	outb(VGA_AC_INDEX, 0x20);
}