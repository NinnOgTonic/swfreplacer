#pragma once


#include "TagInstance.h"
#include "DefineShape.h"

#include <list>
using namespace std;




class DefineFont :
	public TagInstance
{
	//FontID UI16 ID for this font character
	UInt16 FontID;
	//OffsetTable UI16[nGlyphs] Array of shape offsets
	list<UInt16> OffsetTable;
	//GlyphShapeTable SHAPE[nGlyphs] Array of shapes
	list<DefineShape> GlyphShapeTable;

	int nGlyphs;

public:
	DefineFont(void);
	~DefineFont(void);

	virtual void ReadData(SWFReader *swf, int length);
    virtual void WriteData(SWFWriter *swf, int length);
    virtual ulong GetLength(void);
    virtual void SetLength(ulong len);

    virtual UInt16 GetCharacterID();
    virtual void SetCharacterID(UInt16 IdNew);
    virtual void IncreaseCharacterID(UInt16 nAmount);
};
