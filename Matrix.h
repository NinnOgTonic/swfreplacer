#pragma once


#include "types.h"
#include "SWFReader.h"
#include "SWFWriter.h"


//--------------------------------------------------------------
// Matrix
//--------------------------------------------------------------
struct stMatrix {
	// Has scale values if equal to 1
	byte HasScale;
	// If HasScale = 1 {
		UInt16 NScaleBits;// If HasScale = 1, UB[5] Bits in each scale value field
		UInt32 ScaleX;// If HasScale = 1, FB[NScaleBits] x scale value
		UInt32 ScaleY;// If HasScale = 1, FB[NScaleBits] y scale value
	// }
	

	// UB[1] Has rotate and skew values if equal to 1
	byte HasRotate;
	// If HasRotate = 1{
		UInt16 NRotateBits;// If HasRotate = 1, UB[5] Bits in each rotate value field
		UInt32 RotateSkew0;// If HasRotate = 1, FB[NRotateBits] First rotate and skew value
		UInt32 RotateSkew1;// If HasRotate = 1, FB[NRotateBits] Second rotate and skew value
	// }


	byte NTranslateBits;// UB[5] Bits in each translate value field
	UInt32 TranslateX;// SB[NTranslateBits] x translate value in twips
	UInt32 TranslateY;// SB[NTranslateBits]  y translate value in twips

	int Read_Bits(SWFReader *swf){
		int iTotBit = 0;

		printf("      Matrix\n" );

		HasScale = swf->ReadUB(1);
		iTotBit+=1;
		if( HasScale!=0){
			NScaleBits  = swf->ReadUB(5);
			ScaleX = swf->ReadUB(NScaleBits);
			ScaleY = swf->ReadUB(NScaleBits);
			printf( "        ScaleX/ScaleY = %d.%d/%d.%d\n", (int)(ScaleX>>16),  (int)(ScaleX&0x0000ffff), (int)(ScaleY>>16), (int)(ScaleY&0x0000ffff));

			iTotBit = 5 + (NScaleBits*2);
		}
		HasRotate = swf->ReadUB(1);
		iTotBit += 1;
		if( HasRotate!=0){
			NRotateBits  = swf->ReadUB(5);
			RotateSkew0 = swf->ReadUB(NRotateBits);
			RotateSkew1 = swf->ReadUB(NRotateBits);
			printf( "        RotateSkew0/RotateSkew1 = %d/%d\n", RotateSkew0, RotateSkew1);

			iTotBit = 5 + (NRotateBits*2);
		}

		NTranslateBits = swf->ReadUB(5);
		TranslateX = swf->ReadUB(NTranslateBits);
		TranslateY = swf->ReadUB(NTranslateBits);
		printf("        TranslateX/TranslateY = %d.%d/%d.%d\n", (int)(TranslateX>>16),  (int)(TranslateX&0x0000ffff), (int)(TranslateY>>16), (int)(TranslateY&0x0000ffff));
		
		iTotBit = 5 + (NTranslateBits*2);
		//int iTotSize =  (iTotBit%8==0 ? (iTotBit/8) : (iTotBit/8+1));

		return iTotBit;
	}
	int Write_Bits(SWFWriter *swf){
		int iTotBit = 0;

		printf("      Matrix\n" );

		swf->WriteUB(HasScale,1);
		iTotBit += 1;
		if( HasScale==1){
			swf->WriteUB(NScaleBits, 5);
			swf->WriteUB(ScaleX, NScaleBits);
			swf->WriteUB(ScaleY, NScaleBits);
			printf( "        ScaleX/ScaleY = %d.%d/%d.%d\n", (int)(ScaleX>>16),  (int)(ScaleX&0x0000ffff), (int)(ScaleY>>16), (int)(ScaleY&0x0000ffff));

			iTotBit = (5 + (NScaleBits*2));
		}
		swf->WriteUB(HasRotate,1);
		iTotBit += 1;
		if( HasRotate==1){
			swf->WriteUB(NRotateBits, 5);
			swf->WriteUB(RotateSkew0, NRotateBits);
			swf->WriteUB(RotateSkew1, NRotateBits);
			printf( "        RotateSkew0/RotateSkew1 = %d/%d\n", RotateSkew0, RotateSkew1);

			iTotBit = (5 + (NRotateBits*2));
		}
		printf( "        TranslateX/TranslateY = %d.%d/%d.%d\n", (int)(TranslateX>>16),  (int)(TranslateX&0x0000ffff), (int)(TranslateY>>16), (int)(TranslateY&0x0000ffff));
		
		swf->WriteUB(NTranslateBits, 5);
		swf->WriteUB(TranslateX, NTranslateBits);
		swf->WriteUB(TranslateY, NTranslateBits);
		
		iTotBit = (5 + (NTranslateBits*2));
		//int iTotSize = (iTotBit%8==0 ? (iTotBit/8) : (iTotBit/8+1));

		return iTotBit;
	}
};
