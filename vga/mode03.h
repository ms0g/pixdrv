#ifndef MODE03_H
#define MODE03_H

#include "register.h"

static const ExternalGeneral extRegs03 = {
    .miscOutput = 0x67
};

static const Sequencer seqRegs03 = {
    .reset = 0x03,
    .clockingMode = 0x00,
    .mapMask = 0x03,
    .charMapSelect = 0x00,
    .seqMemoryMode = 0x02
};

static CRTController crtcRegs03 = {
    .horizontalTotal = 0x5F,
    .endHorizontalDisplay = 0x4F,
    .startHorizontalBlanking = 0x50,
    .endHorizontalBlanking = 0x82,
    .startHorizontalRetrace = 0x55,
    .endHorizontalRetrace = 0x81,
    .verticalTotal = 0xBF,
    .overflow = 0x1F,
    .presetRowScan = 0x00,
    .maximumScanLine = 0x4F,
    .cursorStart = 0x0D,
    .cursorEnd = 0x0E,
    .startAddressHigh = 0x00,
    .startAddressLow = 0x00,
    .cursorLocationHigh = 0x00,
    .cursorLocationLow = 0x50,
    .verticalRetraceStart = 0x9C,
    .verticalRetraceEnd = 0x0E,
    .verticalDisplayEnd = 0x8F,
    .offset = 0x28,
    .underlineLocation = 0x1F,
    .startVerticalBlanking = 0x96,
    .endVerticalBlanking = 0xB9,
    .CRTCModeControl = 0xA3,
    .lineCompare = 0xFF
};

static const GraphicsController gfxcRegs03 = {
    .setReset = 0x00,
    .enableSetReset = 0x00,
    .colorCompare = 0x00,
    .dataRotate = 0x00,
    .readMapSelect = 0x00,
    .graphicsMode = 0x10,
    .miscGraphics = 0x0E,
    .colorDontCare = 0x00,
    .bitMask = 0xFF
};

static const AttributeController attrcRegs03 = {
    .palette = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F},
    .attrModeControl = 0x0C,
    .overscanColor = 0x00,
    .colorPlaneEnable = 0x0F,
    .horizontalPixelPanning = 0x08,
    .colorSelect = 0x00
};

#endif