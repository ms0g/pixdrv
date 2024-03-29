#ifndef MODE13_H
#define MODE13_H

#include "regs.h"

/**
 * Register Values for Mode 13h
 * 
 * http://www.osdever.net/FreeVGA/vga/vga.htm
 * https://files.osdev.org/mirrors/geezer/osd/graphics/modes.c
 */

static const ExternalGeneral extRegs13 = {
    .miscOutput = 0x63
};

static const Sequencer seqRegs13 = {
    .reset = 0x03,
    .clockingMode = 0x01,
    .mapMask = 0x0F,
    .charMapSelect = 0x00,
    .seqMemoryMode = 0x0E
};

static CRTController crtcRegs13 = {
    .horizontalTotal = 0x5F,
    .endHorizontalDisplay = 0x4F,
    .startHorizontalBlanking = 0x50,
    .endHorizontalBlanking = 0x82,
    .startHorizontalRetrace = 0x54,
    .endHorizontalRetrace = 0x80,
    .verticalTotal = 0xBF,
    .overflow = 0x1F,
    .presetRowScan = 0x00,
    .maximumScanLine = 0x41,
    .cursorStart = 0x00,
    .cursorEnd = 0x00,
    .startAddressHigh = 0x00,
    .startAddressLow = 0x00,
    .cursorLocationHigh = 0x00,
    .cursorLocationLow = 0x00,
    .verticalRetraceStart = 0x9C,
    .verticalRetraceEnd = 0x0E,
    .verticalDisplayEnd = 0x8F,
    .offset = 0x28,
    .underlineLocation = 0x40,
    .startVerticalBlanking = 0x96,
    .endVerticalBlanking = 0xB9,
    .CRTCModeControl = 0xA3,
    .lineCompare = 0xFF
};

static const GraphicsController gfxcRegs13 = {
    .setReset = 0x00,
    .enableSetReset = 0x00,
    .colorCompare = 0x00,
    .dataRotate = 0x00,
    .readMapSelect = 0x00,
    .graphicsMode = 0x40,
    .miscGraphics = 0x05,
    .colorDontCare = 0x0F,
    .bitMask = 0xFF
};

static const AttributeController attrcRegs13 = {
    .palette = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    .attrModeControl = 0x41,
    .overscanColor = 0x00,
    .colorPlaneEnable = 0x0F,
    .horizontalPixelPanning = 0x00,
    .colorSelect = 0x00
};

#endif
