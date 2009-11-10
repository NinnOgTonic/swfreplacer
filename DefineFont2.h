#pragma once


#include "TagInstance.h"
#include "DefineShape.h"

#include <list>
using namespace std;


struct stSHAPE{
	//NumFillBits UB[4] Number of fill index bits.
	byte NumFillBits;
	//NumLineBits UB[4] Number of line index bits.
	byte NumLineBits;
	//ShapeRecords SHAPERECORD[one or more] Shape records (see following).
	//list<ShapeRecords> Shapes;
	ShapeRecords Shapes;

	stSHAPE(){
	}
	~stSHAPE(){
		//Shapes.clear();
	}
	void ReadData(SWFReader *swf){//, int numGlyphs){
		NumFillBits = swf->ReadUB(4);
		NumLineBits = swf->ReadUB(4);
		Shapes.Read_Bits(swf);
		/*
		for( int i=0; i<numGlyphs;  i++ ){
			ShapeRecords *shape = new ShapeRecords();
			shape->SetFillBits(NumFillBits);
			shape->SetLineBits(NumLineBits);
			shape->Read_Bits(swf);
			Shapes.push_back( *shape );
		}
		*/
	}
	void WriteData(SWFWriter *swf){//, int numGlyphs){
		swf->WriteUB(NumFillBits, 4);
		swf->WriteUB(NumLineBits, 4);	
		/*
		list<ShapeRecords>::iterator iter;
		for( iter=Shapes.begin(); iter!=Shapes.end(); ++iter ){
			(*iter).Write_Bits(swf);
		}
		*/
		Shapes.Write_Bits(swf);
	}
};

struct stKERNINGRECORD{
	//FontKerningCode1 If FontFlagsWideCodes,
	//UI16
	//Otherwise UI8
	//Character code of the left
	//character.
	UInt16 FontKerningCode1;
	//FontKerningCode2 If FontFlagsWideCodes,
	//UI16
	//Otherwise UI8
	//Character code of the right
	//character.
	UInt16 FontKerningCode2;
	//FontKerningAdjustment SI16 Adjustment relative to left
	//character��s advance value.
	Int16 FontKerningAdjustment;

	void ReadData(SWFReader *swf, bool FontFlagsWideCodes){
		if(FontFlagsWideCodes){
			FontKerningCode1 = swf->ReadUI16();
			FontKerningCode2 = swf->ReadUI16();
		}
		else{
			FontKerningCode1 = swf->ReadByte();
			FontKerningCode2 = swf->ReadByte();
		}
		FontKerningAdjustment = swf->ReadSI16();
	}
	void WriteData(SWFWriter *swf, bool FontFlagsWideCodes){
		if(FontFlagsWideCodes){
			swf->WriteUI16(FontKerningCode1);
			swf->WriteUI16(FontKerningCode2);
		}
		else{
			swf->WriteByte(FontKerningCode1);
			swf->WriteByte(FontKerningCode2);
		}
		swf->WriteSI16(FontKerningAdjustment);
	}
};


class DefineFont2 :
	public TagInstance
{
	//FontID UI16 ID for this font character
	UInt16 FontID;

	//FontID UI16 ID for this font character.
	//FontFlagsHasLayout UB[1] Has font metrics/layout
	//information.
	byte FontFlagsHasLayout;
	//FontFlagsShiftJIS UB[1] ShiftJIS encoding.
	byte FontFlagsShiftJIS;
	//FontFlagsSmallText UB[1] SWF 7 or later:
	//Font is small. Character glyphs
	//are aligned on pixel boundaries
	//for dynamic and input text.
	byte FontFlagsSmallText;
	//FontFlagsANSI UB[1] ANSI encoding.
	byte FontFlagsANSI;
	//FontFlagsWideOffsets UB[1] If 1, uses 32 bit offsets.
	byte FontFlagsWideOffsets;
	//FontFlagsWideCodes UB[1] If 1, font uses 16-bit codes;
	//otherwise font uses 8 bit codes.
	byte FontFlagsWideCodes;
	//FontFlagsItalic UB[1] Italic Font.
	byte FontFlagsItalic;
	//FontFlagsBold UB[1] Bold Font.
	byte FontFlagsBold;
	//LanguageCode LANGCODE SWF 5 or earlier:
	//always 0
	//SWF 6 or later:
	//language code
	byte LanguageCode;
	//FontNameLen UI8 Length of name.
	byte FontNameLen;
	//FontName UI8[FontNameLen] Name of font (see
	//DefineFontInfo).
	char FontName[256];
	//NumGlyphs UI16 Count of glyphs in font.
	//May be zero for device fonts.
	UInt16 NumGlyphs;
	//OffsetTable If FontFlagsWideOffsets,
	//UI32[NumGlyphs]
	//Otherwise UI16[NumGlyphs]
	//Same as in DefineFont.
	list<UInt32> OffsetTable;
	//CodeTableOffset If FontFlagsWideOffsets,
	//UI32
	//Otherwise UI16
	//Byte count from start of
	//OffsetTable to start of
	//CodeTable.
	UInt32 CodeTableOffset;
	//GlyphShapeTable SHAPE[NumGlyphs] Same as in DefineFont.
	list<stSHAPE> GlyphShapeTable;
	//CodeTable If FontFlagsWideCodes,
	//UI16[NumGlyphs]
	//Otherwise UI8[NumGlyphs]
	//Sorted in ascending order.
	//Always UCS-2 in SWF 6 or later.
	list<UInt16> CodeTable;
	//FontAscent If FontFlagsHasLayout, SI16 Font ascender height.
	Int16 FontAscent;
	//FontDescent If FontFlagsHasLayout, SI16 Font descender height.
	Int16 FontDescent;
	//FontLeading If FontFlagsHasLayout, SI16 Font leading height (see
	//following).
	Int16 FontLeading;
	//FontAdvanceTable If FontFlagsHasLayout,
	//SI16[NumGlyphs]
	//Advance value to be used for
	//each glyph in dynamic glyph text.
	list<Int16> FontAdvanceTable;
	//FontBoundsTable If FontFlagsHasLayout,
	//RECT[NumGlyphs]
	//Not used in Flash Player through
	//version 7 (but must be present).
	list<Rect> FontBoundsTable;
	//KerningCount If FontFlagsHasLayout, UI16 Not used in Flash Player through
	//version 7 (always set to 0 to save
	//space).
	UInt16 KerningCount;
	//FontKerningTable If FontFlagsHasLayout,
	//KERNINGRECORD
	//[KerningCount]
	//Not used in Flash Player through
	//version 7 (omit with
	//KerningCount of 0).
	list<stKERNINGRECORD> FontKerningTable;

	// TODO
	// Analyze and use the SHAPE information...
	byte *GlyphData;
	int iGlyphDataSize;

public:
	DefineFont2(void);
	~DefineFont2(void);

	virtual void ReadData(SWFReader *swf, int length);
    virtual void WriteData(SWFWriter *swf, int length);
    virtual ulong GetLength(void);
    virtual void SetLength(ulong len);

    virtual UInt16 GetCharacterID();
    virtual void SetCharacterID(UInt16 IdNew);
    virtual void IncreaseCharacterID(UInt16 nAmount);
};
