#ifndef MODE12_H
#define MODE12_H

#include "register.h"

static const ExternalGeneral extRegs12 = {
    .miscOutput = 0xE3
};

static const Sequencer seqRegs12 = {
    .reset = 0x03,
    .clockingMode = 0x01,
    .mapMask = 0x0F,
    .charMapSelect = 0x00,
    .seqMemoryMode = 0x06
};

static CRTController crtcRegs12 = {
    .horizontalTotal = 0x5F,
    .endHorizontalDisplay = 0x4F,
    .startHorizontalBlanking = 0x50,
    .endHorizontalBlanking = 0x82,
    .startHorizontalRetrace = 0x54,
    .endHorizontalRetrace = 0x80,
    .verticalTotal = 0x0B,
    .overflow = 0x3E,
    .presetRowScan = 0x00,
    .maximumScanLine = 0x40,
    .cursorStart = 0x00,
    .cursorEnd = 0x00,
    .startAddressHigh = 0x00,
    .startAddressLow = 0x00,
    .cursorLocationHigh = 0x00,
    .cursorLocationLow = 0x59,
    .verticalRetraceStart = 0xEA,
    .verticalRetraceEnd = 0x8C,
    .verticalDisplayEnd = 0x0DF,
    .offset = 0x28,
    .underlineLocation = 0x00,
    .startVerticalBlanking = 0x0E7,
    .endVerticalBlanking = 0x04,
    .CRTCModeControl = 0xE3,
    .lineCompare = 0xFF
};

static const GraphicsController gfxcRegs12 = {
    .setReset = 0x00,
    .enableSetReset = 0x00,
    .colorCompare = 0x00,
    .dataRotate = 0x00,
    .readMapSelect = 0x00,
    .graphicsMode = 0x00,
    .miscGraphics = 0x05,
    .colorDontCare = 0x0F,
    .bitMask = 0xFF
};

static const AttributeController attrcRegs12 = {
    .palette = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F},
    .attrModeControl = 0x01,
    .overscanColor = 0x00,
    .colorPlaneEnable = 0x0F,
    .horizontalPixelPanning = 0x00,
    .colorSelect = 0x00
};

#endif