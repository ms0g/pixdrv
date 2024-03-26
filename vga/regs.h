#ifndef REGS_H
#define REGS_H

typedef unsigned char u8;

/****************************
 *      VGA Registers       *
 ****************************/

typedef struct ExternalGeneral {
    u8 miscOutput;
    u8 featControl;
    u8 inputStatus0;
    u8 inputStatus1;
} ExternalGeneral;

typedef union Sequencer {
    struct {
        u8 reset;
        u8 clockingMode;
        u8 mapMask;
        u8 charMapSelect;
        u8 seqMemoryMode;
    };
    u8 m[5];
} Sequencer;

typedef union CRTController {
    struct {
        u8 horizontalTotal;
        u8 endHorizontalDisplay;
        u8 startHorizontalBlanking;
        u8 endHorizontalBlanking;
        u8 startHorizontalRetrace;
        u8 endHorizontalRetrace;
        u8 verticalTotal;
        u8 overflow;
        u8 presetRowScan;
        u8 maximumScanLine;
        u8 cursorStart;
        u8 cursorEnd;
        u8 startAddressHigh;
        u8 startAddressLow;
        u8 cursorLocationHigh;
        u8 cursorLocationLow;
        u8 verticalRetraceStart;
        u8 verticalRetraceEnd;
        u8 verticalDisplayEnd;
        u8 offset;
        u8 underlineLocation;
        u8 startVerticalBlanking;
        u8 endVerticalBlanking;
        u8 CRTCModeControl;
        u8 lineCompare;
    };
    u8 m[25];
} CRTController;

typedef union GraphicsController {
    struct {
        u8 setReset;
        u8 enableSetReset;
        u8 colorCompare;
        u8 dataRotate;
        u8 readMapSelect;
        u8 graphicsMode;
        u8 miscGraphics;
        u8 colorDontCare;
        u8 bitMask;
    };
    u8 m[9];
} GraphicsController;

typedef union AttributeController {
    struct {
        u8 palette[16];
        u8 attrModeControl;
        u8 overscanColor;
        u8 colorPlaneEnable;
        u8 horizontalPixelPanning;
        u8 colorSelect;
    };
    u8 m[21];
} AttributeController;

#endif 