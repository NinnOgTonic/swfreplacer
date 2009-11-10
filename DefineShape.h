#pragma once


#include "TagInstance.h"
#include "Rect.h"
#include "SWFReader.h"
#include "SWFWriter.h"
#include "Matrix.h"

#include <list>
using namespace std;



//--------------------------------------------------------------
// GradientRecord -> Gradient
//--------------------------------------------------------------
struct stGradRecord{
	byte Ratio;
	byte Color[3]; // RGB

	int Read_Bits(SWFReader *swf){
		printf("    Gradient\n");
		Ratio = swf->ReadByte();
		for(int i=0; i<3; i++){
			Color[i] = swf->ReadByte();
		}

		return 4*8;
	}
	int Write_Bits(SWFWriter *swf){
		printf("    Gradient\n");
		swf->WriteByte(Ratio);
		for(int i=0; i<3; i++){
			swf->WriteByte(Color[i]);
		}

		return 4*8;
	}
};
struct stGradient {
	//SpreadMode UB[2] 0 = Pad mode
	//1 = Reflect mode
	//2 = Repeat mode
	//3 = Reserved
	UInt16 SpreadMode;
	//InterpolationMode UB[2] 0 = Normal RGB mode
	//interpolation
	//1 = Linear RGB mode
	//interpolation
	//2 and 3 = Reserved
	UInt16 InterpolationMode;
	//NumGradients UB[4] 1 to 15
	UInt16 NumGradients;
	
	stGradRecord GradientRecords[16];

	int Read_Bits(SWFReader *swf){
		int iTot=0;

		SpreadMode = swf->ReadUB(2);
		InterpolationMode = swf->ReadUB(2);
		NumGradients = swf->ReadUB(4);
		iTot += 8;

		printf("  #Gradients : SpreadMode[%d] InterpolationMode[%d]\n", SpreadMode, InterpolationMode);

		for(int i=0;i<NumGradients; i++ ){
			iTot += GradientRecords[i].Read_Bits(swf);
		}

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		int iTot=0;

		swf->WriteUB(SpreadMode, 2);
		swf->WriteUB(InterpolationMode, 2);
		swf->WriteUB(NumGradients, 4);
		iTot += 8;

		printf("  #Gradients : SpreadMode[%d] InterpolationMode[%d]\n", SpreadMode, InterpolationMode);

		for(int i=0;i<NumGradients; i++ ){
			iTot += GradientRecords[i].Write_Bits(swf);
		}

		return iTot;
	}
};



//--------------------------------------------------------------
// LineStyle
//--------------------------------------------------------------
struct stLineStyle {
	UInt16 Width;
	//byte RGB[3];
	byte RGB[4];

	int Read_Bits(SWFReader *swf){
		printf("    LineStyle\n");
		Width = swf->ReadUI16();
		for(int i=0; i<3; i++){
			RGB[i] = swf->ReadByte();
		}

		return 5*8;
	}
	int Write_Bits(SWFWriter *swf){
		printf("    LineStyle\n");
		swf->WriteUI16(Width);
		for(int i=0; i<3; i++){
			swf->WriteByte(RGB[i]);
		}

		return 5*8;
	}
};

// LineStyleArray
struct stLineStyleArray {
	byte Count;
	//if(  Count == 255) {
	UInt16 CountExtented;
	
	stLineStyle *pStyles;


	int iRealCount;
	stLineStyleArray(){
		iRealCount=0;
		pStyles=0;
	}
	~stLineStyleArray(){
		if(pStyles){
			delete[] pStyles;
		}
	}

	int Read_Bits(SWFReader *swf){
		int iTot=0;

		Count = swf->ReadByte();
		iTot+=8;
		if(Count==255){
			CountExtented = swf->ReadUI16();
			iTot+=16;
			iRealCount = CountExtented;
		}
		else
		{
			iRealCount = Count;
		}

		printf( "  LineStyles [%d]\n",iRealCount  );

		if(pStyles) delete[] pStyles;
		pStyles = new stLineStyle[iRealCount];
		for(int i=0;i<iRealCount; i++ ){
			iTot+=pStyles[i].Read_Bits(swf);
		}

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		int iTot=0;

		swf->WriteByte(iRealCount>=255 ? 255 : Count);
		iTot+=8;
		if(iRealCount>=255){
			swf->WriteUI16(iRealCount);
			iTot+=16;
		}

		printf( "  LineStyles [%d]\n",iRealCount  );

		for(int i=0;i<iRealCount; i++ ){
			iTot+=pStyles[i].Write_Bits(swf);
		}

		return iTot;
	}
};



//--------------------------------------------------------------
// FillStyle
//--------------------------------------------------------------
struct stFillStyle{
	byte FillStyleType;
	// If type = 0x00
	byte Color[4]; // RGB

	//If type = 0x10, 0x12, or 0x13, MATRIX..... Matrix for gradient fill
	stMatrix GradientMatrix; 

	// If type = 0x10 or 0x12, GRADIENT
	// If type = 0x13, FOCALGRADIENT
	// (SWF 8 and later only)
	stGradient Gradient;

	// If type = 0x40, 0x41, 0x42 or 0x43,
	// UI16
	// ID of bitmap character for fill.
	UInt16 BitmapId;

	//If type = 0x40, 0x41, 0x42 or 0x43,
	//MATRIX
	//Matrix for bitmap fill.
	stMatrix BitmapMatrix;


	int Read_Bits(SWFReader *swf){
		printf( "    FillStyle\n" );
		int iTot=0;
		FillStyleType = swf->ReadByte();
		printf( "      Type = %d\n", FillStyleType );
		iTot += 8;

		if( FillStyleType==0 ){
			for(int i=0; i<3; i++){
				Color[i] = swf->ReadByte();
			}
			printf("    RGB = (%d,%d,%d)\n", Color[0], Color[1], Color[2]);
			iTot += 24;
		}

		

		if( FillStyleType == 0x10 || FillStyleType == 0x12 || FillStyleType == 0x13 ){
			iTot += GradientMatrix.Read_Bits(swf);
		}
		if( FillStyleType == 0x40 || FillStyleType == 0x41 || FillStyleType == 0x42 
				|| FillStyleType == 0x43 ){
			BitmapId = swf->ReadUI16();
			printf("    Use Bitmap [%d]\n", BitmapId);
			iTot += 16;
		}
		if( FillStyleType == 0x40 || FillStyleType == 0x41 || FillStyleType == 0x42 
				|| FillStyleType == 0x43 ){
			iTot += BitmapMatrix.Read_Bits(swf);
		}

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		printf( "    FillStyle\n" );
		int iTot=0;
		swf->WriteByte(FillStyleType);
		printf( "      Type = %d\n", FillStyleType );
		iTot += 8;
		if( FillStyleType==0 ){
			for(int i=0; i<3; i++){
				swf->WriteByte(Color[i]);
			}
			printf("    RGB = (%d,%d,%d)\n", Color[0], Color[1], Color[2]);
			iTot += 24;
		}

		if( FillStyleType == 0x10 || FillStyleType == 0x12 || FillStyleType == 0x13 ){
			iTot += GradientMatrix.Write_Bits(swf);
		}
		if( FillStyleType == 0x40 || FillStyleType == 0x41 || FillStyleType == 0x42 
				|| FillStyleType == 0x43 ){
			swf->WriteUI16(BitmapId);
			printf("    Use Bitmap [%d]\n", BitmapId);
			iTot += 16;
		}
		if( FillStyleType == 0x40 || FillStyleType == 0x41 || FillStyleType == 0x42 
				|| FillStyleType == 0x43 ){
			iTot += BitmapMatrix.Write_Bits(swf);
		}

		return iTot;
	}
};

// Fill style
struct stFillStyleArray {
	byte Count;
	//if(  Count == 255) {
	UInt16 CountExtented;
	
	stFillStyle *pStyles;

	int iRealCount;
	stFillStyleArray(){
		iRealCount=0;
		pStyles=0;
	}
	~stFillStyleArray(){
		if(pStyles){
			delete[] pStyles;
		}
	}


	int Read_Bits(SWFReader *swf){
		int iTot=0;

		Count = swf->ReadByte();
		iTot+=8;
		if(Count==255){
			CountExtented = swf->ReadUI16();
			iTot+=16;
			iRealCount = CountExtented;
		}
		else
		{
			iRealCount = Count;
		}

		printf( "  FillStyles [%d]\n", iRealCount );

		if(pStyles) delete[] pStyles;
		pStyles = new stFillStyle[iRealCount];
		for(int i=0;i<iRealCount; i++ ){
			iTot+=pStyles[i].Read_Bits(swf);
		}

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		int iTot=0;

		swf->WriteByte(iRealCount>=255 ? 255 : iRealCount);
		iTot+=8;
		if(iRealCount>=255){
			swf->WriteUI16(iRealCount);
			iTot+=16;
		}
		printf( "  FillStyles [%d]\n", iRealCount );

		for(int i=0;i<iRealCount; i++ ){
			iTot+=pStyles[i].Write_Bits(swf);
		}

		return iTot;
	}
};



//--------------------------------------------------------------
// 
//--------------------------------------------------------------
class ShapeRecordBasic{
protected:
	byte TypeFlag;
	byte flg1;
	byte flg2;
	byte flg3;
	byte flg4;
	byte flg5;

	// UB[4] Number of fill index bits.
	byte FillBits;
	// UB[4] Number of line index bits.
	byte LineBits;
public:
	ShapeRecordBasic(){
	}
	virtual ~ShapeRecordBasic(){
	}

	void SetFillBits(byte b){
		FillBits=b;
	}
	void SetLineBits(byte b){
		LineBits=b;
	}

	virtual int Read_Bits(SWFReader *swf){
		printf("  ShapeRecordBasic::Read\n");
		return 8; // basically 6bit
	}
	virtual int Write_Bits(SWFWriter *swf){
		printf("  ShapeRecordBasic::Write\n");
		return 8; // basically 6bit
	}
	virtual void SetHead(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5){
		TypeFlag=b0;
		flg1=b1;
		flg2=b2;
		flg3=b3;
		flg4=b4;
		flg5=b5;
	}
};


class ShapeRecord_End : public ShapeRecordBasic{
	byte EndOfShape;// UB[5] 
	                  // Always 0.
public:
	ShapeRecord_End(){
	}
	virtual ~ShapeRecord_End(){
	}
	virtual int Read_Bits(SWFReader *swf){
		printf( "  ShapeRecord_End\n" );
		return 6; // basically 6bit
	}
	virtual int Write_Bits(SWFWriter *swf){
		printf( "  ShapeRecord_End\n" );
		
		// Write Header
		swf->WriteUB(TypeFlag, 1);
		swf->WriteUB(EndOfShape, 5);

		return 6; // basically 6bit
	}
	virtual void SetHead(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5){
		TypeFlag=0;
		EndOfShape=0;
	}

};


class ShapeRecord_StyleChange : public ShapeRecordBasic{
	//UB[1]
	byte StateNewStyles;
	//UB[1]
	byte StateLineStyle;
	//UB[1]
	byte StateFillStyle1;
	//UB[1]
	byte StateFillStyle0;
	//UB[1]
	byte StateMoveTo;

	byte MoveBits; //  If StateMoveTo, UB[5] Move bit count.
	Int16 MoveDeltaX; // If StateMoveTo, SB[MoveBits] Delta X value.
	Int16 MoveDeltaY; // If StateMoveTo, SB[MoveBits] Delta Y value.
	byte FillStyle0; // If StateFillStyle0, UB[FillBits] Fill 0 Style.
	byte FillStyle1; // If StateFillStyle1, UB[FillBits] Fill 1 Style.
	byte LineStyle; // If StateLineStyle, UB[LineBits] Line Style.
	//If StateNewStyles,
	//FILLSTYLEARRAY
	//Array of new fill styles.
	stFillStyleArray FillStyles;

	//If StateNewStyles,
	//LINESTYLEARRAY
	//Array of new line styles.
	stLineStyleArray LineStyles;
	byte NumFillBits; // If StateNewStyles, UB[4] Number of fill index bits for new styles.
	byte NumLineBits; // If StateNewStyles, UB[4] Number of line index bits for new styles.

public:
	ShapeRecord_StyleChange(){
	}
	virtual ~ShapeRecord_StyleChange(){
	}

	virtual int Read_Bits(SWFReader *swf){
		int iBitTotal=0;
		int iByteTotal=0;

		printf("  ShapeRecord_StyleChange\n" );

		if(StateMoveTo){
			MoveBits = swf->ReadUB(5); //  If StateMoveTo, UB[5] Move bit count.
			MoveDeltaX = swf->ReadSB(MoveBits);//MoveBits); // If StateMoveTo, SB[MoveBits] Delta X value.
			MoveDeltaY = swf->ReadUB(MoveBits);//MoveBits); // If StateMoveTo, SB[MoveBits] Delta Y value.
			printf( "    MoveTo %d,%d\n", MoveDeltaX, MoveDeltaY );

			iBitTotal += 5 + MoveBits*2;
		}

		if(StateFillStyle0){
			FillStyle0 = swf->ReadUB(FillBits); // If StateFillStyle0, UB[FillBits] Fill 0 Style.
			iBitTotal += FillBits;
			printf( "    FillStyle0 = %d (FillBits=%d)\n", FillStyle0, FillBits );
		}
		if(StateFillStyle1){
			FillStyle1 = swf->ReadUB(FillBits); // If StateFillStyle1, UB[FillBits] Fill 1 Style.
			iBitTotal += FillBits;
			printf( "    FillStyle1 = %d (FillBits=%d)\n", FillStyle1, FillBits );
		}
		if(StateLineStyle){
			if(LineBits>0){
				LineStyle = swf->ReadUB(LineBits); // If StateLineStyle, UB[LineBits] Line Style.
				iBitTotal += LineBits;
				printf( "    LineStyle = %d (LineBits=%d)\n", LineStyle, LineBits );
			}
		}
		iBitTotal += 6; // basic leading 6bits
		
		//If StateNewStyles,
		//FILLSTYLEARRAY
		//Array of new fill styles.
		if(StateNewStyles){
			printf( "    HasNewStyles\n");
			iByteTotal += FillStyles.Read_Bits(swf);
			iByteTotal += LineStyles.Read_Bits(swf);
			NumFillBits = swf->ReadUB(4);
			NumLineBits = swf->ReadUB(4);
			iBitTotal += 8;
		}

		//iByteTotal = (iBitTotal%8>0)?(1+iBitTotal/8):(iBitTotal/8);
		return iBitTotal;
	}

	virtual int Write_Bits(SWFWriter *swf){
		int iBitTotal=0;
		int iByteTotal=0;

		// Write Header
		swf->WriteUB(TypeFlag, 1);
		swf->WriteUB(StateNewStyles, 1);
		swf->WriteUB(StateLineStyle, 1);
		swf->WriteUB(StateFillStyle1, 1);
		swf->WriteUB(StateFillStyle0, 1);
		swf->WriteUB(StateMoveTo, 1);

		printf("  ShapeRecord_StyleChange\n" );

		if(StateMoveTo){
			swf->WriteUB(MoveBits, 5); //  If StateMoveTo, UB[5] Move bit count.
			swf->WriteUB(MoveDeltaX, MoveBits); // If StateMoveTo, SB[MoveBits] Delta X value.
			swf->WriteUB(MoveDeltaY, MoveBits); // If StateMoveTo, SB[MoveBits] Delta Y value.
			printf( "    MoveTo %d,%d\n", MoveDeltaX, MoveDeltaY );

			iBitTotal += 5 + MoveBits*2;
		}

		if(StateFillStyle0){
			swf->WriteUB(FillStyle0, FillBits); // If StateFillStyle0, UB[FillBits] Fill 0 Style.
			iBitTotal += FillBits;
			printf( "    FillStyle0 = %d (FillBits=%d)\n", FillStyle0, FillBits );
		}
		if(StateFillStyle1){
			swf->WriteUB(FillStyle1, FillBits); // If StateFillStyle1, UB[FillBits] Fill 1 Style.
			iBitTotal += FillBits;
			printf( "    FillStyle1 = %d (FillBits=%d)\n", FillStyle1, FillBits );
		}
		if(StateLineStyle){
			if(LineBits>0){
				swf->WriteUB(LineStyle, LineBits); // If StateLineStyle, UB[LineBits] Line Style.
				iBitTotal += LineBits;
				printf( "    LineStyle = %d (LineBits=%d)\n", LineStyle, LineBits );
			}
		}
		iBitTotal += 6; // basic leading 6bits
		//If StateNewStyles,
		//FILLSTYLEARRAY
		//Array of new fill styles.
		if(StateNewStyles){
			printf( "    HasNewStyles\n");
			iByteTotal += FillStyles.Write_Bits(swf);
			iByteTotal += LineStyles.Write_Bits(swf);
			swf->WriteUB(NumFillBits,4);
			swf->WriteUB(NumLineBits, 4);
			iBitTotal += 8;
		}

		//iByteTotal = (iBitTotal%8>0)?(1+iBitTotal/8):(iBitTotal/8);
		return iByteTotal;
	}
	
	virtual void SetHead(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5){
		TypeFlag=b0;
		StateNewStyles=b1;
		StateLineStyle=b2;
		StateFillStyle1=b3;
		StateFillStyle0=b4;
		StateMoveTo=b5;
	}
};



class ShapeRecord_StraightEdge : public ShapeRecordBasic{
	byte StraightFlag; // UB[1] Straight edge. Always 1.
	byte NumBits; // UB[4] Number of bits per value (2 less than the actual number).


	byte GeneralLineFlag; // UB[1] General Line equals 1.
	                      // Vert/Horz Line equals 0.
	sbyte VertLineFlag; // If GeneralLineFlag = 0, SB[1]
	                    // Vertical Line equals 1.
	                    // Horizontal Line equals 0.
	Int16 DeltaX; // If GeneralLineFlag = 1 or
	              // if VertLineFlag = 0,
	              // SB[NumBits+2]
	              // X delta.
	Int16 DeltaY; // If GeneralLineFlag = 1 or
	              // if VertLineFlag = 1,
	              // SB[NumBits+2]
public:
	ShapeRecord_StraightEdge(){
	}
	virtual ~ShapeRecord_StraightEdge(){
	}
	virtual int Read_Bits(SWFReader *swf){

		printf( "  ShapeRecord_StraightEdge\n" );

		int iTotBits = 0;
		GeneralLineFlag = swf->ReadUB(1);
		iTotBits += 1;

		VertLineFlag = 0;
		DeltaX = DeltaY = 0;
		if( GeneralLineFlag==0 ){
			VertLineFlag = swf->ReadSB(1);
			iTotBits += 1;
		}
		if( GeneralLineFlag || VertLineFlag==0 ){
		    DeltaX = swf->ReadSB(NumBits+2);
			iTotBits += NumBits+2;
		}
		if( GeneralLineFlag || VertLineFlag!=0 ){
			DeltaY = swf->ReadSB(NumBits+2);
			iTotBits += NumBits+2;
		}
		printf("    Delta X/Y = %d/%d\n", DeltaX, DeltaY );

		iTotBits += 6; // basic leading 6bits
		return  iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	}

	virtual int Write_Bits(SWFWriter *swf){
		// Write Header
		swf->WriteUB(TypeFlag, 1);
		swf->WriteUB(StraightFlag, 1);
		swf->WriteUB(NumBits, 4);
		printf( "  ShapeRecord_StraightEdge\n" );

		int iTotBits = 0;
		swf->WriteUB(GeneralLineFlag, 1);
		iTotBits += 1;
		if(GeneralLineFlag==0 ){
			swf->WriteSB(VertLineFlag, 1);
			iTotBits += 1;
		}
		if( GeneralLineFlag || VertLineFlag==0 ){
		    swf->WriteSB(DeltaX, NumBits+2);
			iTotBits += NumBits+2;
		}
		if( GeneralLineFlag || VertLineFlag!=0 ){
			swf->WriteSB(DeltaY, NumBits+2);
			iTotBits += NumBits+2;
		}
		printf("    Delta X/Y = %d/%d\n", DeltaX, DeltaY );

		iTotBits += 6; // basic leading 6bits
		return  iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	}
	virtual void SetHead(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5){
		TypeFlag=b0;
		StraightFlag=b1;
		NumBits= 0x00 | (b2<<3) | (b3<<2) | (b4<<1) | (b5<<0);
	}
};

class ShapeRecord_CurvedEdge : public ShapeRecordBasic{
	byte StraightFlag;// UB[1] Curved edge.
	                  // Always 0.
	byte NumBits; // UB[4] Number of bits per value
	              // (2 less than the actual number).
	Int32 ControlDeltaX; // SB[NumBits+2] X control point change.
	Int32 ControlDeltaY; // SB[NumBits+2] Y control point change.
	Int32 AnchorDeltaX; // SB[NumBits+2] X anchor point change.
	Int32 AnchorDeltaY; // SB[NumBits+2] Y anchor point change.
public:
	ShapeRecord_CurvedEdge(){
	}
	virtual ~ShapeRecord_CurvedEdge(){
	}
	virtual int Read_Bits(SWFReader *swf){
		printf( "  ShapeRecord_CurvedEdge\n" );
		ControlDeltaX = swf->ReadSB(NumBits+2);
		ControlDeltaY = swf->ReadSB(NumBits+2);
		AnchorDeltaX = swf->ReadSB(NumBits+2);
		AnchorDeltaY = swf->ReadSB(NumBits+2);

		int iTotBits = 4*(NumBits+2);
		iTotBits += 6; // basic leading 6bits
		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	}
	virtual int Write_Bits(SWFWriter *swf){
		// Write Header
		swf->WriteUB(TypeFlag, 1);
		swf->WriteUB(StraightFlag, 1);
		swf->WriteUB(NumBits, 4);
		printf( "  ShapeRecord_CurvedEdge\n" );
		swf->WriteSB(ControlDeltaX, NumBits+2);
		swf->WriteSB(ControlDeltaY, NumBits+2);
		swf->WriteSB(AnchorDeltaX, NumBits+2);
		swf->WriteSB(AnchorDeltaY, NumBits+2);

		int iTotBits = 4*(NumBits+2);
		iTotBits += 6; // basic leading 6bits
		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	}
	virtual void SetHead(byte b0,byte b1,byte b2,byte b3,byte b4,byte b5){
		TypeFlag=b0;
		StraightFlag=b1;
		NumBits= 0x00 | (b2<<3) | (b3<<2) | (b4<<1) | (b5<<0);
	}

};



class ShapeRecords{

	list<ShapeRecordBasic*> shapeRecordItems;
	int FillBits;
	int LineBits;

public:
	ShapeRecords(){
		FillBits = LineBits = 0;
	}
	~ShapeRecords(){
		shapeRecordItems.clear();
	}

	void SetFillBits(byte b){
		FillBits=b;
	}
	void SetLineBits(byte b){
		LineBits=b;
	}

	int Read_Bits(SWFReader *swf){
		int iTot=0;
		byte TypeFlag;
		byte flg1;
		byte flg2;
		byte flg3;
		byte flg4;
		byte flg5;

		do{
			TypeFlag = swf->ReadUB(1);
			flg1 = swf->ReadUB(1);
			flg2 = swf->ReadUB(1);
			flg3 = swf->ReadUB(1);
			flg4 = swf->ReadUB(1);
			flg5 = swf->ReadUB(1);
			iTot += 6;

			if( TypeFlag==0 ){ // Non Edge tags
				if( flg1==0&&flg2==0&&flg3==0&&flg4==0&&flg5==0) {
					// End
					ShapeRecord_End *pitem = new ShapeRecord_End;
					pitem->SetFillBits(FillBits);
					pitem->SetLineBits(LineBits);
					pitem->SetHead(TypeFlag, flg1, flg2, flg3, flg4, flg5);

					iTot += pitem->Read_Bits(swf);

					
					shapeRecordItems.push_back( pitem );

					break;
				}
				else{
					// Style Change
					ShapeRecord_StyleChange *pitem = new ShapeRecord_StyleChange;
					pitem->SetFillBits(FillBits);
					pitem->SetLineBits(LineBits);
					pitem->SetHead(TypeFlag, flg1, flg2, flg3, flg4, flg5);

					iTot += pitem->Read_Bits(swf);
					shapeRecordItems.push_back( pitem );
				}
			}
			else{ // Edge tags
				if( flg1==1 ){ 
					// Straight Edge
					ShapeRecord_StraightEdge *pitem = new ShapeRecord_StraightEdge;
					pitem->SetFillBits(FillBits);
					pitem->SetLineBits(LineBits);
					pitem->SetHead(TypeFlag, flg1, flg2, flg3, flg4, flg5);
					iTot += pitem->Read_Bits(swf);
					shapeRecordItems.push_back( pitem );
				}
				else{
					// Curved Edge
					ShapeRecord_CurvedEdge *pitem = new ShapeRecord_CurvedEdge;
					pitem->SetFillBits(FillBits);
					pitem->SetLineBits(LineBits);
					pitem->SetHead(TypeFlag, flg1, flg2, flg3, flg4, flg5);
					iTot += pitem->Read_Bits(swf);
					shapeRecordItems.push_back( pitem );
				}
			}
		}while(true);

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		int iTot=0;

		list<ShapeRecordBasic*>::iterator i;
		for( i = shapeRecordItems.begin(); i!=shapeRecordItems.end(); ++i ){
			iTot += (*i)->Write_Bits(swf);
		}

		return iTot;
	}
};

//--------------------------------------------------------------
// stShapeWithStyle
//--------------------------------------------------------------
class stShapeWithStyle {
	
public:
	stFillStyleArray	FillStyles;
	stLineStyleArray	LineStyles;
	
	// UB[4] Number of fill index bits.
	byte NumFillBits;
	// UB[4] Number of line index bits.
	byte NumLineBits;

	ShapeRecords ShapeRecord;



	int Read_Bits(SWFReader *swf){
		int iTot=0;

		iTot += FillStyles.Read_Bits(swf);
		iTot += LineStyles.Read_Bits(swf);
		NumFillBits = swf->ReadUB(4);
		NumLineBits = swf->ReadUB(4);
		iTot+=8;
		printf( "  NumFillBits = %d, NumLineBits = %d\n", NumFillBits, NumLineBits );

		ShapeRecord.SetFillBits(NumFillBits);
		ShapeRecord.SetLineBits(NumLineBits);
		iTot+=ShapeRecord.Read_Bits(swf);

		return iTot;
	}
	int Write_Bits(SWFWriter *swf){
		int iTot=0;

		iTot += FillStyles.Write_Bits(swf);
		iTot += LineStyles.Write_Bits(swf);
		swf->WriteUB(NumFillBits, 4);
		swf->WriteUB(NumLineBits, 4);
		iTot+=8;
		printf( "  NumFillBits = %d, NumLineBits = %d\n", NumFillBits, NumLineBits );

		ShapeRecord.SetFillBits(NumFillBits);
		ShapeRecord.SetLineBits(NumLineBits);
		iTot+=ShapeRecord.Write_Bits(swf);

		return iTot;
	}
};


//--------------------------------------------------------------
// stDefineShape
//--------------------------------------------------------------
struct stDefineShape {
	UInt16 ShapeId;
	Rect ShapeBounds;
	stShapeWithStyle Shapes;

	stDefineShape(){
	}
	~stDefineShape(){
	}
	
	// There comes more data for 'stShapeWithStyle' but
	// I didn't specified those structures 'cuase I don't need them.
	// So to read the rest of the data, I pass the original length
	// of dat to read.
	int Read(SWFReader *swf, int len){
		long lOrgSwfPos=swf->GetPosition();
		int iTot=0;

		ShapeId = swf->ReadUI16();
		printf( "  ShapeID = %d\n", ShapeId );
		iTot += 16;
		
		iTot += 8*ShapeBounds.Read(swf);
		printf( "  ShapeBounds (%d, %d, %d, %d)\n", 
			ShapeBounds.XMin(), ShapeBounds.YMin(),
			ShapeBounds.XMax(), ShapeBounds.YMax());

		iTot += Shapes.Read_Bits(swf);

		return (swf->GetPosition()-lOrgSwfPos);//iTot;
	}
	int Write(SWFWriter *swf, int len){
		long lOrgSwfPos=swf->GetPosition();
		int iTot=0;

		printf( "  ShapeID = %d\n", ShapeId );
		swf->WriteUI16(ShapeId);
		iTot += 16;
		iTot += 8*ShapeBounds.Write(swf);
		printf( "  ShapeBounds (%d, %d, %d, %d)\n", 
			ShapeBounds.XMin(), ShapeBounds.YMin(),
			ShapeBounds.XMax(), ShapeBounds.YMax());

		iTot += Shapes.Write_Bits(swf);

		return (swf->GetPosition()-lOrgSwfPos);//iTot;
	}
};




class DefineShape :
	public TagInstance
{
	stDefineShape Shape;

public:
	DefineShape(void);
	virtual ~DefineShape(void);


	virtual void ReadData(SWFReader *swf, int length);
    virtual void WriteData(SWFWriter *swf, int length);
    virtual ulong GetLength(void);
    virtual void SetLength(ulong len);

    virtual UInt16 GetCharacterID();
    virtual void SetCharacterID(UInt16 IdNew);
    virtual void IncreaseCharacterID(UInt16 nAmount);
};
