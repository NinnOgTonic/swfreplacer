#include "DefineText.h"

DefineText::DefineText(void) {
	bAdditionalByte = false;
	byteAdditional = 0;
}

DefineText::~DefineText(void) {
    TextRecords.clear();
}

void DefineText::ReadData(SWFReader *swf, int l) {
    long swfPos = swf->GetPosition();
    //CharacterID UI16 ID for this text character.
    CharacterID = swf->ReadUI16();
    printf( "  CharacterID = %d\n", CharacterID );
    //TextBounds RECT Bounds of the text.
    TextBounds.Read(swf);
    //TextMatrix MATRIX Transformation matrix for the
    //text.
    TextMatrix.Read_Bits(swf);
    //GlyphBits UI8 Bits in each glyph index.
    GlyphBits = swf->ReadByte();
	if(GlyphBits==0){ 
		bAdditionalByte = true;
		byteAdditional = GlyphBits;
		printf( "      # Strange additional byte exists.. [%d]\n", byteAdditional);
		GlyphBits=swf->ReadByte(); //!!!!!!!!!!!!!
	}

    //AdvanceBits UI8 Bits in each advance value.
    AdvanceBits = swf->ReadByte();
    //TextRecords TEXTRECORD[zero or more] Text records.
    printf( "    GlyphBits, AdvanceBits = %d, %d\n", GlyphBits, AdvanceBits );
    list<stTEXTRECORD>::iterator itr;
    while(true) {
        stTEXTRECORD *txtrecord = new stTEXTRECORD();
        txtrecord->GlyphBits = GlyphBits;
        txtrecord->AdvanceBits = AdvanceBits;
        int iresult = txtrecord->Read(swf);
        TextRecords.push_back( *txtrecord );
        if (iresult <= 8) {
            break;
        }
    }
    //EndOfRecordsFlag UI8 Must be 0.
    printf( "  READLEN = %d\n", swf->GetPosition()-swfPos );
}

void DefineText::WriteData(SWFWriter *swf, int l) {
    //CharacterID UI16 ID for this text character.
    swf->WriteUI16(CharacterID);
    printf( "  CharacterID = %d\n", CharacterID );
    //TextBounds RECT Bounds of the text.
    TextBounds.Write(swf);
    //TextMatrix MATRIX Transformation matrix for the
    //text.
    TextMatrix.Write_Bits(swf);


	if( bAdditionalByte ){
		printf( "      # Strange additional byte exists.. [%d]\n", byteAdditional);
		swf->WriteByte(byteAdditional); // !!!!!!
	}


    //GlyphBits UI8 Bits in each glyph index.
    swf->WriteByte(GlyphBits);
    //AdvanceBits UI8 Bits in each advance value.
    swf->WriteByte(AdvanceBits);
    printf( "    GlyphBits, AdvanceBits = %d, %d\n", GlyphBits, AdvanceBits );
    //TextRecords TEXTRECORD[zero or more] Text records.
    list<stTEXTRECORD>::iterator itr;
    for (itr = TextRecords.begin(); itr != TextRecords.end(); ++itr) {
		/*
        if ((*itr).Write(swf) <= 8) {
            break;
        }
		*/
		(*itr).Write(swf);
    }
}

ulong DefineText::GetLength(void) {
    return this->length;
}

void DefineText::SetLength(ulong len) {
    this->length = len;
}

UInt16 DefineText::GetCharacterID() {
    return CharacterID;
}

void DefineText::SetCharacterID(UInt16 IdNew) {
    CharacterID = IdNew;
}

void DefineText::IncreaseCharacterID(UInt16 nAmount) {
    SetCharacterID(GetCharacterID() + nAmount);

    list<stTEXTRECORD>::iterator itr;
    for (itr = TextRecords.begin(); itr != TextRecords.end(); ++itr) {
        (*itr).FontID += nAmount;
    }
}