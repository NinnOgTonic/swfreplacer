#pragma once
#include "TagInstance.h"
#include "Rect.h"
#include "SWFReader.h"
#include "SWFWriter.h"
#include "Matrix.h"

#include <list>
using namespace std;

struct stGLYPHENTRY {
    int GlyphBits;
    int AdvanceBits;

    //GlyphIndex UB[GlyphBits] Glyph index into current font.
    UInt16 GlyphIndex;
    //GlyphAdvance SB[AdvanceBits] x advance value for glyph.
    Int16 GlyphAdvance;

    stGLYPHENTRY() {
        GlyphBits = 0;
        AdvanceBits = 0;
        GlyphIndex = 0;
        GlyphAdvance = 0;
    }

    ~stGLYPHENTRY() {
    }

    int Read(SWFReader * swf) {
        GlyphIndex = swf->ReadUB(GlyphBits);
        GlyphAdvance = swf->ReadSB(AdvanceBits);
        printf( "      GlyphIndex, GlyphAdvance = %d, %d\n", GlyphIndex, GlyphAdvance );
        return GlyphIndex + AdvanceBits;
    }

    int Write(SWFWriter * swf) {
        swf->WriteUB(GlyphIndex, GlyphBits);
        swf->WriteSB(GlyphAdvance, AdvanceBits);
        printf( "      GlyphIndex, GlyphAdvance = %d, %d\n", GlyphIndex, GlyphAdvance );
        return GlyphIndex + AdvanceBits;
    }
};

struct stTEXTRECORD {
    //TextRecordType UB[1] Always 1.
    byte TextRecordType;
    //StyleFlagsReserved UB[3] Always 0.
    byte StyleFlagsReserved;
    //StyleFlagsHasFont UB[1] 1 if text font specified.
    byte StyleFlagsHasFont;
    //StyleFlagsHasColor UB[1] 1 if text color specified.
    byte StyleFlagsHasColor;
    //StyleFlagsHasYOffset UB[1] 1 if y offset specified.
    byte StyleFlagsHasYOffset;
    //StyleFlagsHasXOffset UB[1] 1 if x offset specified.
    byte StyleFlagsHasXOffset;
    //FontID If StyleFlagsHasFont, UI16 Font ID for following text.
    UInt16 FontID;
    //TextColor If StyleFlagsHasColor, RGB
    //If this record is part of a
    //DefineText2 tag, RGBA
    //Font color for following text.
    byte TextColor[3];
    //XOffset If StyleFlagsHasXOffset, SI16 x offset for following text.
    Int16 XOffset;
    //YOffset If StyleFlagsHasYOffset, SI16 y offset for following text.
    Int16 YOffset;
    //TextHeight If hasFont, UI16 Font height for following text.
    UInt16 TextHeight;
    //GlyphCount UI8 Number of glyphs in record.
    byte GlyphCount;
    //GlyphEntries GLYPHENTRY[GlyphCount] Glyph entry (see following).
    stGLYPHENTRY *GlyphEntries;

    int GlyphBits;
    int AdvanceBits;

    stTEXTRECORD() {
        GlyphEntries = 0;
        GlyphBits = 0;
        AdvanceBits = 0;
    }

    ~stTEXTRECORD() {
        if (GlyphEntries) delete[] GlyphEntries;
    }

    int Read(SWFReader * swf) {
        int iBitTot = 0;

        // The first bit should be always 1.
        byte temp;
        TextRecordType = 0;
		StyleFlagsReserved = StyleFlagsHasFont = StyleFlagsHasColor = StyleFlagsHasYOffset = StyleFlagsHasXOffset = 0;
        for(int i=0; i<8; i++){
            temp = swf->ReadUB(1);
            if( temp==1 ){
                // The next 3 bits should be 0
                temp = swf->ReadUB(3);
                if( temp==0 ){
                    TextRecordType = 1;
                    StyleFlagsReserved = 0;
                    break;
                }
                i=0;
            }
        }
        if(TextRecordType!=1){
            printf("    END_OF_TEXTRECORD\n");
            return 8;
        }

        // //TextRecordType UB[1] Always 1.
        //TextRecordType = swf->ReadUB(1);
        iBitTot += 1;

        // //StyleFlagsReserved UB[3] Always 0.
        //StyleFlagsReserved = swf->ReadUB(3);
        iBitTot += 3;

        //StyleFlagsHasFont UB[1] 1 if text font specified.
        StyleFlagsHasFont = swf->ReadUB(1);
        iBitTot += 1;
        //StyleFlagsHasColor UB[1] 1 if text color specified.
        StyleFlagsHasColor = swf->ReadUB(1);
        iBitTot += 1;
        //StyleFlagsHasYOffset UB[1] 1 if y offset specified.
        StyleFlagsHasYOffset = swf->ReadUB(1);
        iBitTot += 1;
        //StyleFlagsHasXOffset UB[1] 1 if x offset specified.
        StyleFlagsHasXOffset = swf->ReadUB(1);
        iBitTot += 1;

		/*
        if (TextRecordType == 0 && StyleFlagsReserved == 0 && StyleFlagsHasFont == 0 &&
                StyleFlagsHasColor == 0 && StyleFlagsHasYOffset == 0 && StyleFlagsHasXOffset == 0) {
            printf("    END_OF_TEXTRECORD\n");
            return 8;
        }
		*/
        printf("    TEXTRECORD\n");

        //FontID If StyleFlagsHasFont, UI16 Font ID for following text.
        if (StyleFlagsHasFont) {
            FontID = swf->ReadUI16();
            iBitTot += 16;
            printf("      Uses the font %d\n", FontID);
        }
        //TextColor If StyleFlagsHasColor, RGB
        //If this record is part of a
        //DefineText2 tag, RGBA
        //Font color for following text.
        if (StyleFlagsHasColor) {
			printf("      Color = @");
            for (int i = 0; i < 3; i++) {
                TextColor[i] = swf->ReadByte();
                iBitTot += 8;
				printf( "%d ", TextColor[i] );
            }
			printf("\n");
        }
        //XOffset If StyleFlagsHasXOffset, SI16 x offset for following text.
        if (StyleFlagsHasXOffset) {
            XOffset = swf->ReadSI16();
            iBitTot += 16;
			printf("      XOffset = %d\n", XOffset);
        }
        //YOffset If StyleFlagsHasYOffset, SI16 y offset for following text.
        if (StyleFlagsHasYOffset) {
            YOffset = swf->ReadSI16();
            iBitTot += 16;
			printf("      YOffset = %d\n", YOffset);
        }
        //TextHeight If hasFont, UI16 Font height for following text.
        if (StyleFlagsHasFont) {
            TextHeight = swf->ReadUI16();
            iBitTot += 16;
        }
        //GlyphCount UI8 Number of glyphs in record.
        GlyphCount = swf->ReadByte();
        printf( "      GlyphCount = %d\n", GlyphCount);
        iBitTot += 8;
        //GlyphEntries GLYPHENTRY[GlyphCount] Glyph entry (see following).
        if (GlyphCount) {
            GlyphEntries = new stGLYPHENTRY[GlyphCount];
            for (int i = 0; i < GlyphCount; i++) {
                GlyphEntries[i].GlyphBits = GlyphBits;
                GlyphEntries[i].AdvanceBits = AdvanceBits;
                iBitTot += GlyphEntries[i].Read(swf);
            }
        }

        return iBitTot;
    }

    int Write(SWFWriter * swf) {
        int iBitTot = 0;

        //TextRecordType UB[1] Always 1.
        swf->WriteUB(TextRecordType, 1);
        iBitTot += 1;
        //StyleFlagsReserved UB[3] Always 0.
        swf->WriteUB(StyleFlagsReserved, 3);
        iBitTot += 3;
        //StyleFlagsHasFont UB[1] 1 if text font specified.
        swf->WriteUB(StyleFlagsHasFont, 1);
        iBitTot += 1;
        //StyleFlagsHasColor UB[1] 1 if text color specified.
        swf->WriteUB(StyleFlagsHasColor, 1);
        iBitTot += 1;
        //StyleFlagsHasYOffset UB[1] 1 if y offset specified.
        swf->WriteUB(StyleFlagsHasYOffset, 1);
        iBitTot += 1;
        //StyleFlagsHasXOffset UB[1] 1 if x offset specified.
        swf->WriteUB(StyleFlagsHasXOffset, 1);
        iBitTot += 1;

		if(TextRecordType!=1){
        /*if (TextRecordType == 0 && StyleFlagsReserved == 0 && StyleFlagsHasFont == 0 &&
                StyleFlagsHasColor == 0 && StyleFlagsHasYOffset == 0 && StyleFlagsHasXOffset == 0) {*/
            printf("    END_OF_TEXTRECORD\n");
            return 8;
        }
        printf("    TEXTRECORD\n");

        //FontID If StyleFlagsHasFont, UI16 Font ID for following text.
        if (StyleFlagsHasFont) {
            swf->WriteUI16(FontID);
            iBitTot += 16;
            printf("      Uses the font %d\n", FontID);
        }
        //TextColor If StyleFlagsHasColor, RGB
        //If this record is part of a
        //DefineText2 tag, RGBA
        //Font color for following text.
        if (StyleFlagsHasColor) {
			printf("      Color = @");
            for (int i = 0; i < 3; i++) {
                swf->WriteByte(TextColor[i]);
                iBitTot += 8;
				printf( "%d ", TextColor[i] );
            }
			printf("\n");
        }
        //XOffset If StyleFlagsHasXOffset, SI16 x offset for following text.
        if (StyleFlagsHasXOffset) {
            swf->WriteSI16(XOffset);
            iBitTot += 16;
			printf("      XOffset = %d\n", XOffset);
        }
        //YOffset If StyleFlagsHasYOffset, SI16 y offset for following text.
        if (StyleFlagsHasYOffset) {
            swf->WriteSI16(YOffset);
            iBitTot += 16;
			printf("      YOffset = %d\n", YOffset);
        }
        //TextHeight If hasFont, UI16 Font height for following text.
        if (StyleFlagsHasFont) {
            swf->WriteUI16(TextHeight);
            iBitTot += 16;
        }
        //GlyphCount UI8 Number of glyphs in record.
        swf->WriteByte(GlyphCount);
        iBitTot += 8;
        printf( "      GlyphCount = %d\n", GlyphCount);
        //GlyphEntries GLYPHENTRY[GlyphCount] Glyph entry (see following).
        if (GlyphCount) {
            for (int i = 0; i < GlyphCount; i++) {
                iBitTot += GlyphEntries[i].Write(swf);
            }
        }

        return iBitTot;
    }
};

class DefineText :
public TagInstance {
    //CharacterID UI16 ID for this text character.
    UInt16 CharacterID;
    //TextBounds RECT Bounds of the text.
    Rect TextBounds;
    //TextMatrix MATRIX Transformation matrix for the
    //text.
    stMatrix TextMatrix;
    //GlyphBits UI8 Bits in each glyph index.
    byte GlyphBits;
    //AdvanceBits UI8 Bits in each advance value.
    byte AdvanceBits;
    //TextRecords TEXTRECORD[zero or more] Text records.
    list<stTEXTRECORD> TextRecords;
    //EndOfRecordsFlag UI8 Must be 0.

	bool bAdditionalByte;
	byte byteAdditional;


public:
    DefineText(void);
    ~DefineText(void);

    virtual void ReadData(SWFReader *swf, int length);
    virtual void WriteData(SWFWriter *swf, int length);
    virtual ulong GetLength(void);
    virtual void SetLength(ulong len);

    virtual UInt16 GetCharacterID();
    virtual void SetCharacterID(UInt16 IdNew);
    virtual void IncreaseCharacterID(UInt16 nAmount);
};
