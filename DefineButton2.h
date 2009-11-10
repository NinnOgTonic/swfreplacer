#pragma once


#include "TagInstance.h"
#include "Rect.h"
#include "SWFReader.h"
#include "SWFWriter.h"
#include "Matrix.h"

#include <list>
using namespace std;



struct stCXFORM{
	// HasAddTerms UB[1] Has color addition values if equal
	//to 1
	byte HasAddTerms;
	//HasMultTerms UB[1] Has color multiply values if equal to
	//1
	byte HasMultTerms;
	//Nbits UB[4] Bits in each value field
	byte Nbits;
	//RedMultTerm If HasMultTerms = 1, SB[Nbits] Red multiply value
	Int32 RedMultTerm;
	//GreenMultTerm If HasMultTerms = 1, SB[Nbits] Green multiply value
	Int32 GreenMultTerm;
	//BlueMultTerm If HasMultTerms = 1, SB[Nbits] Blue multiply value
	Int32 BlueMultTerm;
	//RedAddTerm If HasAddTerms = 1, SB[Nbits] Red addition value
	Int32 RedAddTerm;
	//GreenAddTerm If HasAddTerms = 1, SB[Nbits] Green addition value
	Int32 GreenAddTerm;
	//BlueAddTerm If HasAddTerms = 1, SB[Nbits] Blue addition value
	Int32 BlueAddTerm;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		HasAddTerms = swf->ReadUB(1); iTotBits+=1;
		HasMultTerms = swf->ReadUB(1); iTotBits+=1;
		Nbits = swf->ReadUB(4); iTotBits+=4;
		if(HasMultTerms)
		{
			RedMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			GreenMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			BlueMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
		}
		if(HasAddTerms){
			RedAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			GreenAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			BlueAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
		}


		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		swf->WriteUB(HasAddTerms, 1); iTotBits+=1;
		swf->WriteUB(HasMultTerms, 1); iTotBits+=1;
		swf->WriteUB(Nbits, 4); iTotBits+=4;
		if(HasMultTerms){
			swf->WriteSB(RedMultTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(GreenMultTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(BlueMultTerm, Nbits); iTotBits+=Nbits;
		}
		if(HasAddTerms){
			swf->WriteSB(RedAddTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(GreenAddTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(BlueAddTerm, Nbits); iTotBits+=Nbits;
		}

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stCXFORMWITHALPHA{
	//HasAddTerms UB[1] Has color addition values if
	//equal to 1
	byte HasAddTerms;
	//HasMultTerms UB[1] Has color multiply values if
	//equal to 1
	byte HasMultTerms;
	//Nbits UB[4] Bits in each value field
	byte Nbits;
	//RedMultTerm If HasMultTerms = 1, SB[Nbits] Red multiply value
	Int32 RedMultTerm;
	//GreenMultTerm If HasMultTerms = 1, SB[Nbits] Green multiply value
	Int32 GreenMultTerm;
	//BlueMultTerm If HasMultTerms = 1, SB[Nbits] Blue multiply value
	Int32 BlueMultTerm;
	//AlphaMultTerm If HasMultTerms = 1, SB[Nbits] Alpha multiply value
	Int32 AlphaMultTerm;
	//RedAddTerm If HasAddTerms = 1, SB[Nbits] Red addition value
	Int32 RedAddTerm;
	//GreenAddTerm If HasAddTerms = 1, SB[Nbits] Green addition value
	Int32 GreenAddTerm;
	//BlueAddTerm If HasAddTerms = 1, SB[Nbits] Blue addition value
	Int32 BlueAddTerm;
	//AlphaAddTerm If HasAddTerms = 1, SB[Nbits] Transparency addition
	//value
	Int32 AlphaAddTerm;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		HasAddTerms = swf->ReadUB(1); iTotBits+=1;
		HasMultTerms = swf->ReadUB(1); iTotBits+=1;
		Nbits = swf->ReadUB(4); iTotBits+=4;

		if(HasMultTerms){
			RedMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			GreenMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			BlueMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			AlphaMultTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
		}
		if(HasAddTerms){
			RedAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			GreenAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			BlueAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
			AlphaAddTerm = swf->ReadSB(Nbits); iTotBits+=Nbits;
		}
		printf("      stCXFORMWITHALPHA_BITS = %d\n", iTotBits);


		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		swf->WriteUB(HasAddTerms, 1); iTotBits+=1;
		swf->WriteUB(HasMultTerms, 1); iTotBits+=1;
		swf->WriteUB(Nbits, 4); iTotBits+=4;

		if(HasMultTerms){
			swf->WriteSB(RedMultTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(GreenMultTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(BlueMultTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(AlphaMultTerm, Nbits); iTotBits+=Nbits;
		}
		if(HasAddTerms){
			swf->WriteSB(RedAddTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(GreenAddTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(BlueAddTerm, Nbits); iTotBits+=Nbits;
			swf->WriteSB(AlphaAddTerm, Nbits); iTotBits+=Nbits;
		}

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};


struct stBLURFILTER{
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Passes UB[5] Number of blur passes
	byte Passes;
	//Reserved UB[3] Must be 0
	byte Reserved;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf( "      stBLURFILTER\n");
		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Passes = swf->ReadUB(5); iTotBits += 5;
		Reserved = swf->ReadUB(3); iTotBits += 3;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf( "      stBLURFILTER\n");
		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUB(Passes, 5); iTotBits += 5;
		swf->WriteUB(Reserved, 3); iTotBits += 3;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stDROPSHADOWFILTER{
	//DropShadowColor RGBA Color of the shadow
	byte DropShadowColor[4];
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Angle FIXED Radian angle of the drop
	//shadow
	UInt32 Angle;
	//Distance FIXED Distance of the drop
	//shadow
	UInt32 Distance;
	//Strength FIXED8 Strength of the drop
	//shadow
	UInt16 Strength;
	//InnerShadow UB[1] Inner shadow mode
	byte InnerShadow;
	//Knockout UB[1] Knockout mode
	byte Knockout;
	//CompositeSource UB[1] Composite source
	//Always 1
	byte CompositeSource;
	//Passes UB[5] Number of blur passes
	byte Passes;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf( "      stDROPSHADOWFILTER\n");
		for(int i=0; i<4; i++) DropShadowColor[i] = swf->ReadByte();
		iTotBits += 32;
		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Angle = swf->ReadUI32(); iTotBits += 32;
		Distance = swf->ReadUI32(); iTotBits += 32;
		Strength = swf->ReadUI16(); iTotBits += 16;
		InnerShadow = swf->ReadUB(1); iTotBits += 1;
		Knockout = swf->ReadUB(1); iTotBits += 1;
		CompositeSource = swf->ReadUB(1); iTotBits += 1;
		Passes = swf->ReadUB(5); iTotBits += 5;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf( "      stDROPSHADOWFILTER\n");
		for(int i=0; i<4; i++) swf->WriteByte(DropShadowColor[i]);
		iTotBits += 32;
		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUI32(Angle); iTotBits += 32;
		swf->WriteUI32(Distance); iTotBits += 32;
		swf->WriteUI16(Strength); iTotBits += 16;
		swf->WriteUB(InnerShadow, 1); iTotBits += 1;
		swf->WriteUB(Knockout, 1); iTotBits += 1;
		swf->WriteUB(CompositeSource, 1); iTotBits += 1;
		swf->WriteUB(Passes, 5); iTotBits += 5;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stGLOWFILTER{
	//GlowColor RGBA Color of the shadow
	byte GlowColor[4];
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Strength FIXED8 Strength of the glow
	UInt16 Strength;
	//InnerGlow UB[1] Inner glow mode
	byte InnerGlow;
	//Knockout UB[1] Knockout mode
	byte Knockout;
	//CompositeSource UB[1] Composite source
	//Always 1
	byte CompositeSource;
	//Passes UB[5] Number of blur passes
	byte Passes;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      stGLOWFILTER\n");
		for(int i=0; i<4; i++) GlowColor[i] = swf->ReadByte();
		iTotBits += 32;
		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Strength = swf->ReadUI16(); iTotBits += 16;
		Knockout = swf->ReadUB(1); iTotBits += 1;
		CompositeSource = swf->ReadUB(1); iTotBits += 1;
		Passes = swf->ReadUB(5); iTotBits += 5;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      stGLOWFILTER\n");
		for(int i=0; i<4; i++) swf->WriteByte(GlowColor[i]);
		iTotBits += 32;
		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUI16(Strength); iTotBits += 16;
		swf->WriteUB(Knockout, 1); iTotBits += 1;
		swf->WriteUB(CompositeSource, 1); iTotBits += 1;
		swf->WriteUB(Passes, 5); iTotBits += 5;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stBEVELFILTER{
	//ShadowColor RGBA Color of the shadow
	byte ShadowColor[4];
	//HighlightColor RGBA Color of the highlight
	byte HighlightColor[4];
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Angle FIXED Radian angle of the drop
	//shadow
	UInt32 Angle;
	//Distance FIXED Distance of the drop
	//shadow
	UInt32 Distance;
	//Strength FIXED8 Strength of the drop
	//shadow
	UInt16 Strength;
	//InnerShadow UB[1] Inner shadow mode
	byte InnerShadow;
	//Knockout UB[1] Knockout mode
	byte Knockout;
	//CompositeSource UB[1] Composite source
	//Always 1
	byte CompositeSource;
	//OnTop UB[1] OnTop mode
	byte OnTop;
	//Passes UB[4] Number of blur passes
	byte Passes;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      stBEVELFILTER\n");
		for(int i=0; i<4; i++) ShadowColor[i] = swf->ReadByte();
		iTotBits += 32;
		for(int i=0; i<4; i++) HighlightColor[i] = swf->ReadByte();
		iTotBits += 32;
		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Angle = swf->ReadUI32(); iTotBits += 32;
		Distance = swf->ReadUI32(); iTotBits += 32;
		Strength = swf->ReadUI16(); iTotBits += 16;
		InnerShadow = swf->ReadUB(1); iTotBits += 1;
		Knockout = swf->ReadUB(1); iTotBits += 1;
		CompositeSource = swf->ReadUB(1); iTotBits += 1;
		OnTop = swf->ReadUB(1); iTotBits += 1;
		Passes = swf->ReadUB(4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      stBEVELFILTER\n");
		for(int i=0; i<4; i++) swf->WriteByte(ShadowColor[i]);
		iTotBits += 32;
		for(int i=0; i<4; i++) swf->WriteByte(HighlightColor[i]);
		iTotBits += 32;
		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUI32(Angle); iTotBits += 32;
		swf->WriteUI32(Distance); iTotBits += 32;
		swf->WriteUI16(Strength); iTotBits += 16;
		swf->WriteUB(InnerShadow, 1); iTotBits += 1;
		swf->WriteUB(Knockout, 1); iTotBits += 1;
		swf->WriteUB(CompositeSource, 1); iTotBits += 1;
		swf->WriteUB(OnTop, 1); iTotBits += 1;
		swf->WriteUB(Passes, 4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stGRADIENTGLOWFILTER{
	//NumColors UI8 Number of colors in the
	//gradient
	byte NumColors;
	//GradientColors RGBA[NumColors] Gradient colors
	byte *GradientColors;
	//GradientRatio UI8[NumColors] Gradient ratios
	byte *GradientRatio;
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Angle FIXED Radian angle of the
	//gradient glow
	UInt32 Angle;
	//Distance FIXED Distance of the gradient
	//glow
	UInt32 Distance;
	//Strength FIXED8 Strength of the gradient
	//glow
	UInt16 Strength;
	//InnerShadow UB[1] Inner glow mode
	byte InnerShadow;
	//Knockout UB[1] Knockout mode
	byte Knockout;
	//CompositeSource UB[1] Composite source
	//Always 1
	byte CompositeSource;
	//OnTop UB[1] OnTop mode
	byte OnTop;
	//Passes UB[4] Number of blur passes
	byte Passes;

	stGRADIENTGLOWFILTER(){
		GradientColors = 0;
		GradientRatio = 0;
	}
	~stGRADIENTGLOWFILTER(){
		if(GradientColors) free(GradientColors);
		if(GradientRatio) free(GradientRatio);
	}

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      stGRADIENTGLOWFILTER\n");
		NumColors = swf->ReadByte(); iTotBits += 8;
		GradientColors = (byte*)malloc( 4*NumColors );
		GradientRatio =  (byte*)malloc( NumColors );

		for(int j=0; j<NumColors; j++){
			for(int i=0; i<4; i++) GradientColors[j*4+i] = swf->ReadByte();
			iTotBits += 32;
		}
		for(int i=0; i<NumColors; i++) GradientRatio[i] = swf->ReadByte();
		iTotBits += 32;

		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Angle = swf->ReadUI32(); iTotBits += 32;
		Distance = swf->ReadUI32(); iTotBits += 32;
		Strength = swf->ReadUI16(); iTotBits += 16;
		InnerShadow = swf->ReadUB(1); iTotBits += 1;
		Knockout = swf->ReadUB(1); iTotBits += 1;
		CompositeSource = swf->ReadUB(1); iTotBits += 1;
		OnTop = swf->ReadUB(1); iTotBits += 1;
		Passes = swf->ReadUB(4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      stGRADIENTGLOWFILTER\n");
		swf->WriteByte(NumColors); iTotBits += 8;

		for(int j=0; j<NumColors; j++){
			for(int i=0; i<4; i++) swf->WriteByte(GradientColors[j*4+i]);
			iTotBits += 32;
		}
		for(int i=0; i<NumColors; i++) swf->WriteByte(GradientRatio[i]);
		iTotBits += 32;

		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUI32(Angle); iTotBits += 32;
		swf->WriteUI32(Distance); iTotBits += 32;
		swf->WriteUI16(Strength); iTotBits += 16;
		swf->WriteUB(InnerShadow, 1); iTotBits += 1;
		swf->WriteUB(Knockout, 1); iTotBits += 1;
		swf->WriteUB(CompositeSource, 1); iTotBits += 1;
		swf->WriteUB(OnTop, 1); iTotBits += 1;
		swf->WriteUB(Passes, 4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stGRADIENTBEVELFILTER{
	//NumColors UI8 Number of colors in the
	//gradient
	byte NumColors;
	//GradientColors RGBA[NumColors] Gradient colors
	byte *GradientColors;
	//GradientRatio UI8[NumColors] Gradient ratios
	byte *GradientRatio;
	//BlurX FIXED Horizontal blur amount
	UInt32 BlurX;
	//BlurY FIXED Vertical blur amount
	UInt32 BlurY;
	//Angle FIXED Radian angle of the
	//gradient glow
	UInt32 Angle;
	//Distance FIXED Distance of the gradient
	//glow
	UInt32 Distance;
	//Strength FIXED8 Strength of the gradient
	//glow
	UInt16 Strength;
	//InnerShadow UB[1] Inner glow mode
	byte InnerShadow;
	//Knockout UB[1] Knockout mode
	byte Knockout;
	//CompositeSource UB[1] Composite source
	//Always 1
	byte CompositeSource;
	//OnTop UB[1] OnTop mode
	byte OnTop;
	//Passes UB[4] Number of blur passes
	byte Passes;

	stGRADIENTBEVELFILTER(){
		GradientColors = 0;
		GradientRatio = 0;
	}
	~stGRADIENTBEVELFILTER(){
		if(GradientColors) free(GradientColors);
		if(GradientRatio) free(GradientRatio);
	}

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      stGRADIENTBEVELFILTER\n");
		NumColors = swf->ReadByte(); iTotBits += 8;
		GradientColors = (byte*)malloc( 4*NumColors );
		GradientRatio =  (byte*)malloc( NumColors );

		for(int j=0; j<NumColors; j++){
			for(int i=0; i<4; i++) GradientColors[j*4+i] = swf->ReadByte();
			iTotBits += 32;
		}
		for(int i=0; i<NumColors; i++) GradientRatio[i] = swf->ReadByte();
		iTotBits += 32;

		BlurX = swf->ReadUI32(); iTotBits += 32;
		BlurY = swf->ReadUI32(); iTotBits += 32;
		Angle = swf->ReadUI32(); iTotBits += 32;
		Distance = swf->ReadUI32(); iTotBits += 32;
		Strength = swf->ReadUI16(); iTotBits += 16;
		InnerShadow = swf->ReadUB(1); iTotBits += 1;
		Knockout = swf->ReadUB(1); iTotBits += 1;
		CompositeSource = swf->ReadUB(1); iTotBits += 1;
		OnTop = swf->ReadUB(1); iTotBits += 1;
		Passes = swf->ReadUB(4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      stGRADIENTBEVELFILTER\n");
		swf->WriteByte(NumColors); iTotBits += 8;

		for(int j=0; j<NumColors; j++){
			for(int i=0; i<4; i++) swf->WriteByte(GradientColors[j*4+i]);
			iTotBits += 32;
		}
		for(int i=0; i<NumColors; i++) swf->WriteByte(GradientRatio[i]);
		iTotBits += 32;

		swf->WriteUI32(BlurX); iTotBits += 32;
		swf->WriteUI32(BlurY); iTotBits += 32;
		swf->WriteUI32(Angle); iTotBits += 32;
		swf->WriteUI32(Distance); iTotBits += 32;
		swf->WriteUI16(Strength); iTotBits += 16;
		swf->WriteUB(InnerShadow, 1); iTotBits += 1;
		swf->WriteUB(Knockout, 1); iTotBits += 1;
		swf->WriteUB(CompositeSource, 1); iTotBits += 1;
		swf->WriteUB(OnTop, 1); iTotBits += 1;
		swf->WriteUB(Passes, 4); iTotBits += 4;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};


struct stCONVOLUTIONFILTER{
	//MatrixX UI8 Horizontal matrix size
	byte MatrixX;
	//MatrixY UI8 Vertical matrix size
	byte MatrixY;
	//Divisor FLOAT Divisor applied to the
	//matrix values
	UInt32 Divisor;
	//Bias FLOAT Bias applied to the matrix
	//values
	UInt32 Bias;
	//Matrix FLOAT[MatrixX * MatrixY] Matrix values
	UInt32 *Matrix;
	//DefaultColor RGBA Default color for pixels
	//outside the image
	byte DefaultColor[4];
	//Reserved UB[6] Must be 0
	byte Reserved;
	//Clamp UB[1] Clamp mode
	byte Clamp;
	//PreserveAlpha UB[1] Preserve the alpha
	byte PreserveAlpha;

	stCONVOLUTIONFILTER(){
		Matrix=0;
	}
	~stCONVOLUTIONFILTER(){
		if(Matrix) free(Matrix);
	}

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      stCONVOLUTIONFILTER\n" );
		MatrixX = swf->ReadByte(); iTotBits += 8;
		MatrixY = swf->ReadByte(); iTotBits += 8;
		Divisor = swf->ReadUI32(); iTotBits += 32;
		Bias = swf->ReadUI32(); iTotBits += 32;
		Matrix = (UInt32*)malloc( sizeof(UInt32) * MatrixX * MatrixY );
		for(int i=0;i<MatrixX * MatrixY;i++){
			Matrix[i] = swf->ReadUI32();
			iTotBits += 32;
		}
		for(int i=0;i<4;i++){
			DefaultColor[i] = swf->ReadByte();
			iTotBits += 8;
		}
		Reserved = swf->ReadUB(6);iTotBits += 6;
		Clamp = swf->ReadUB(1);iTotBits += 1;
		PreserveAlpha = swf->ReadUB(1);iTotBits += 1;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      stCONVOLUTIONFILTER\n" );
		swf->WriteByte(MatrixX); iTotBits += 8;
		swf->WriteByte(MatrixY); iTotBits += 8;
		swf->WriteUI32(Divisor); iTotBits += 32;
		swf->WriteUI32(Bias); iTotBits += 32;
		Matrix = (UInt32*)malloc( sizeof(UInt32) * MatrixX * MatrixY );
		for(int i=0;i<MatrixX * MatrixY;i++){
			swf->WriteUI32(Matrix[i]);
			iTotBits += 32;
		}
		for(int i=0;i<4;i++){
			swf->WriteByte(DefaultColor[i]);
			iTotBits += 8;
		}
		swf->WriteUB(Reserved, 6);iTotBits += 6;
		swf->WriteUB(Clamp, 1);iTotBits += 1;
		swf->WriteUB(PreserveAlpha, 1);iTotBits += 1;

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};

struct stCOLORMATRIXFILTER{
	//Matrix FLOAT[20] Color matrix values
	UInt32 Matrix[20];

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		printf("      ColorMatrixFilter\n" );
		for(int i=0;i<20;i++){
			Matrix[i] = swf->ReadUI32();
			iTotBits += 32;
		}

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		printf("      ColorMatrixFilter\n" );
		for(int i=0;i<20;i++){
			swf->WriteUI32(Matrix[i]);
			iTotBits += 32;
		}

		return iTotBits;//(iTotBits%8==0 ? (iTotBits/8) : (iTotBits/8+1));
	};
};
struct stFILTER{
	//FilterID UI8 0 = Has DropShadowFilter
	//1 = Has BlurFilter
	//2 = Has GlowFilter
	//3 = Has BevelFilter
	//4 = Has GradientGlowFilter
	//5 = Has ConvolutionFilter
	//6 = Has ColorMatrixFilter
	//7 = Has GradientBevelFilter
	byte FilterID;
	//DropShadowFilter If FilterID = 0,
	//DROPSHADOWFILTER
	//Drop Shadow filter
	stDROPSHADOWFILTER DropShadowFilter;
	//BlurFilter If FilterID = 1, BLURFILTER Blur filter
	stBLURFILTER BlurFilter;
	//GlowFilter If FilterID = 2, GLOWFILTER Glow filter
	stGLOWFILTER GlowFilter;
	//BevelFilter If FilterID = 3, BEVELFILTER Bevel filter
	stBEVELFILTER BevelFilter;
	//GradientGlowFilter If FilterID = 4,
	//GRADIENTGLOWFILTER
	//Gradient Glow filter
	stGRADIENTGLOWFILTER GradientGlowFilter;
	//ConvolutionFilter If FilterID = 5,
	//CONVOLUTIONFILTER
	//Convolution filter
	stCONVOLUTIONFILTER ConvolutionFilter;
	//ColorMatrixFilter If FilterID = 6,
	//COLORMATRIXFILTER
	//Color Matrix filter
	stCOLORMATRIXFILTER ColorMatrixFilter;
	//GradientBevelFilter If FilterID = 7,
	//GRADIENTBEVELFILTER
	//Gradient Bevel filter
	stGRADIENTBEVELFILTER GradientBevelFilter;

	int Read_Bits(SWFReader *swf){
		int iTotBits= 0;
		FilterID = swf->ReadByte(); iTotBits+=8;
		if(FilterID==0){
			iTotBits+=DropShadowFilter.Read_Bits(swf);
		}
		if(FilterID==1){
			iTotBits+=BlurFilter.Read_Bits(swf);
		}
		if(FilterID==2){
			iTotBits+=GlowFilter.Read_Bits(swf);
		}
		if(FilterID==3){
			iTotBits+=BevelFilter.Read_Bits(swf);
		}
		if(FilterID==4){
			iTotBits+=GradientGlowFilter.Read_Bits(swf);
		}
		if(FilterID==5){
			iTotBits+=ConvolutionFilter.Read_Bits(swf);
		}
		if(FilterID==6){
			iTotBits+=ColorMatrixFilter.Read_Bits(swf);
		}
		if(FilterID==7){
			iTotBits+=GradientBevelFilter.Read_Bits(swf);
		}
		return iTotBits;
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits = 0;
		swf->WriteByte(FilterID); iTotBits+=8;
		if(FilterID==0){
			iTotBits+=DropShadowFilter.Write_Bits(swf);
		}
		if(FilterID==1){
			iTotBits+=BlurFilter.Write_Bits(swf);
		}
		if(FilterID==2){
			iTotBits+=GlowFilter.Write_Bits(swf);
		}
		if(FilterID==3){
			iTotBits+=BevelFilter.Write_Bits(swf);
		}
		if(FilterID==4){
			iTotBits+=GradientGlowFilter.Write_Bits(swf);
		}
		if(FilterID==5){
			iTotBits+=ConvolutionFilter.Write_Bits(swf);
		}
		if(FilterID==6){
			iTotBits+=ColorMatrixFilter.Write_Bits(swf);
		}
		if(FilterID==7){
			iTotBits+=GradientBevelFilter.Write_Bits(swf);
		}
		return iTotBits;
	};
};

struct stFILTERLIST{
	//NumberOfFilters UI8 Number of Filters
	byte NumberOfFilters;
	//Filter FILTER[NumberOfFilters] List of filters
	stFILTER *Filters;

	stFILTERLIST(){
		Filters = 0;
	}
	~stFILTERLIST(){
		if(Filters) delete[] Filters;
	}

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		NumberOfFilters = swf->ReadByte(); iTotBits+=8;
		Filters = new stFILTER[NumberOfFilters];
		for(int i=0; i<NumberOfFilters; i++){
			iTotBits+=Filters[i].Read_Bits(swf);
		}

		return iTotBits;
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		swf->WriteByte(NumberOfFilters); iTotBits+=8;
		for(int i=0; i<NumberOfFilters; i++){
			iTotBits+=Filters[i].Write_Bits(swf);
		}

		return iTotBits;
	};
};



struct stACTIONRECORD{
	//ActionCode UI8 An action code
	byte ActionCode;
	//Length If code >= 0x80, UI16 The number of bytes in the
	//ACTIONRECORDHEADER, not
	//counting the ActionCode and
	//Length fields.
	UInt16 Length;
	byte *Data;

	stACTIONRECORD(){
		Data=0;
	}
	~stACTIONRECORD(){
		if(Data) free(Data);
	}

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;
		printf( "    ButtonAction : " );

		ActionCode = swf->ReadByte(); iTotBits+=8;
		if(ActionCode==0){
			printf( "ButtonAction_END\n" );
			return 0; // End of Action
		}
		if(ActionCode>=0x80){
			Length = swf->ReadUI16(); iTotBits+=16;

			if(Data) free(Data);
			Data = (byte*)malloc(Length);
			printf( "bytecode : [" );
			for(int i=0; i<Length; i++ ){
				Data[i] = swf->ReadByte();
				printf("%02x ", Data[i]);
				iTotBits+=8;
			}
			printf("]\n");
		}
		else{
			printf("ActionCode[%d]\n",ActionCode);
		}

		return iTotBits;
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;
		printf( "    ButtonAction : " );

		swf->WriteByte(ActionCode); iTotBits+=8;
		if(ActionCode==0){
			printf( "ButtonAction_END\n" );
			return 0; // End of Action
		}
		if(ActionCode>=0x80){
			swf->WriteUI16(Length); iTotBits+=16;

			printf( "bytecode : [" );
			for(int i=0; i<Length; i++ ){
				swf->WriteByte(Data[i]);
				printf("%02x ", Data[i]);
				iTotBits+=8;
			}
			printf("]\n");
		}
		else{
			printf("ActionCode[%d]\n",ActionCode);
		}

		return iTotBits;
	};
};

struct stBUTTONCONDACTION{
	//CondActionSize UI16 Offset in bytes from start of this
	//field to next
	//BUTTONCONDACTION, or 0
	//if last action
	UInt16 CondActionSize;
	//CondIdleToOverDown UB[1] Idle to OverDown
	byte CondIdleToOverDown;
	//CondOutDownToIdle UB[1] OutDown to Idle
	byte CondOutDownToIdle;
	//CondOutDownToOverDown UB[1] OutDown to OverDown
	byte CondOutDownToOverDown;
	//CondOverDownToOutDown UB[1] OverDown to OutDown
	byte CondOverDownToOutDown;
	//CondOverDownToOverUp UB[1] OverDown to OverUp
	byte CondOverDownToOverUp;
	//CondOverUpToOverDown UB[1] OverUp to OverDown
	byte CondOverUpToOverDown;
	//CondOverUpToIdle UB[1] OverUp to Idle
	byte CondOverUpToIdle;
	//CondIdleToOverUp UB[1] Idle to OverUp
	byte CondIdleToOverUp;
	//CondKeyPress UB[7] SWF 4 or later: key code
	//Otherwise: always 0
	//Valid key codes:
	//1 = left arrow
	//2 = right arrow
	//3 = home
	//4 = end
	//5 = insert
	//6 = delete
	//8 = backspace
	//13 = enter
	//14 = up arrow
	//15 = down arrow
	//16 = page up
	//17 = page down
	//18 = tab
	//19 = escape
	//32 to 126: follows ASCII
	byte CondKeyPress;
	//CondOverDownToIdle UB[1] OverDown to Idle
	byte CondOverDownToIdle;
	//Actions ACTIONRECORD
	//[zero or more]
	//Actions to perform. See
	//DoAction.
	stACTIONRECORD Actions[256];
	//ActionEndFlag UI8 Must be 0
	byte ActionEndFlag;

	int Read_Bits(SWFReader *swf){
		int iTotBits=0;

		CondActionSize = swf->ReadUI16(); iTotBits+=16;
		CondIdleToOverDown = swf->ReadUB(1);
		CondOutDownToIdle = swf->ReadUB(1);
		CondOutDownToOverDown = swf->ReadUB(1);
		CondOverDownToOutDown = swf->ReadUB(1);
		CondOverDownToOverUp = swf->ReadUB(1);
		CondOverUpToOverDown = swf->ReadUB(1);
		CondOverUpToIdle = swf->ReadUB(1);
		CondIdleToOverUp = swf->ReadUB(1);
		CondKeyPress = swf->ReadUB(7);
		CondOverDownToIdle = swf->ReadUB(1);
		iTotBits+=16;

		for(int i=0; i<256; i++){
			int iTemp=Actions[i].Read_Bits(swf); 
			iTotBits+=iTemp;
			if(iTemp<=0){
				break;
			}
		}
		// Each 'Actions' reads in the 'end of action' byte.
		//ActionEndFlag = swf->ReadByte();iTotBits+=8;

		return iTotBits;
	};
	int Write_Bits(SWFWriter *swf){
		int iTotBits=0;

		swf->WriteUI16(CondActionSize); iTotBits+=16;
		swf->WriteUB(CondIdleToOverDown, 1);
		swf->WriteUB(CondOutDownToIdle, 1);
		swf->WriteUB(CondOutDownToOverDown, 1);
		swf->WriteUB(CondOverDownToOutDown, 1);
		swf->WriteUB(CondOverDownToOverUp, 1);
		swf->WriteUB(CondOverUpToOverDown, 1);
		swf->WriteUB(CondOverUpToIdle, 1);
		swf->WriteUB(CondIdleToOverUp, 1);
		swf->WriteUB(CondKeyPress, 7);
		swf->WriteUB(CondOverDownToIdle, 1);
		iTotBits+=16;

		for(int i=0; i<256; i++){
			int iTemp=Actions[i].Write_Bits(swf); 
			iTotBits+=iTemp;
			if(iTemp<=0){
				break;
			}
		}
		// Each 'Actions' contains the 'end of action' byte.
		//swf->WriteByte(ActionEndFlag);iTotBits+=8;

		return iTotBits;
	};
};



//
struct stBUTTONRECORD{
	//ButtonReserved UB[2] Reserved bits; always 0
	byte ButtonReserved;
	//ButtonHasBlendMode UB[1] 0 = No blend mode
	//1 = Has blend mode (SWF 8
	//and later only)
	byte ButtonHasBlendMode;
	//ButtonHasFilterList UB[1] 0 = No filter list
	//1 = Has filter list (SWF 8 and
	//later only)
	byte ButtonHasFilterList;
	//ButtonStateHitTest UB[1] Present in hit test state
	byte ButtonStateHitTest;
	//ButtonStateDown UB[1] Present in down state
	byte ButtonStateDown;
	//ButtonStateOver UB[1] Present in over state
	byte ButtonStateOver;
	//ButtonStateUp UB[1] Present in up state
	byte ButtonStateUp;
	//CharacterID UI16 ID of character to place
	UInt16 CharacterID;
	//PlaceDepth UI16 Depth at which to place
	//character
	UInt16 PlaceDepth;
	//PlaceMatrix MATRIX Transformation matrix for
	//character placement
	stMatrix PlaceMatrix;
	//ColorTransform If within DefineButton2,
	//CXFORMWITHALPHA
	//Character color transform
	stCXFORMWITHALPHA ColorTransform;
	//FilterList If within DefineButton2 and
	//ButtonHasFilterList = 1,
	//FILTERLIST
	//List of filters on this button
	stFILTERLIST FilterList;
	//BlendMode If within DefineButton2 and
	//ButtonHasBlendMode = 1,
	//UI8
	//0 or 1 = normal
	//2 = layer
	//3 = multiply
	//4 = screen
	//5 = lighten
	//6 = darken
	//7 = difference
	//8 = add
	//9 = subtract
	//10 = invert
	//11 = alpha
	//12 = erase
	//13 = overlay
	//14 = hardlight
	//Values 15 to 255 are reserved.
	byte BlendMode;

	byte bTemp;


	int Read_Bits(SWFReader *swf, int iIndex){
		int iTotBits=0;
		printf("    ButtonRecord[%d]\n",iIndex);

		ButtonReserved = swf->ReadUB(2);
		ButtonHasBlendMode = swf->ReadUB(1);
		ButtonHasFilterList = swf->ReadUB(1);
		ButtonStateHitTest = swf->ReadUB(1);
		ButtonStateDown = swf->ReadUB(1);
		ButtonStateOver = swf->ReadUB(1);
		ButtonStateUp = swf->ReadUB(1);
		if( ButtonReserved==0 && ButtonHasBlendMode==0 && ButtonHasFilterList==0 && 
			ButtonStateHitTest==0 && ButtonStateDown==0 && ButtonStateOver==0 && 
			ButtonStateUp==0 ){
				printf ("    END_of_ButtonRecord\n" );
				return 8;
		}
		else
		{
			printf( "      ButtonState(%d/%d/%d/%d/%d/%d/%d)\n", 
				ButtonReserved,ButtonHasBlendMode,ButtonHasFilterList,
				ButtonStateHitTest,ButtonStateDown,ButtonStateOver,ButtonStateUp);
			iTotBits += 8;
		}

		// 2009-11-07 brucewang
		// If the first 8 byte of this record is 0,
		// the Flash player will misunderstood that this is the end of
		// button records. So, I think the Adobe Flash will put some
		// additional information in the rest of bits area after it write
		// the above 8bits..
		// So for later use, I copy those unknown bits..
		int iCurBitPos = swf->GetBitPosition();
		if( iCurBitPos>0 && iCurBitPos<7 ){
			printf( "      ## Reading in bumper data ? curPos=%d, so read %d more bits\n", iCurBitPos,7-iCurBitPos);
			bTemp = swf->ReadUB(7-iCurBitPos);
		}

		CharacterID = swf->ReadUI16(); iTotBits += 16;
		printf( "      CharacterID = %d\n", CharacterID); 
		PlaceDepth = swf->ReadUI16(); iTotBits += 16;
		printf( "      PlaceDepth = %d\n", PlaceDepth);
		iTotBits += PlaceMatrix.Read_Bits(swf);
		iTotBits += ColorTransform.Read_Bits(swf);
		/*
		 * SWF 8 and later only !!!!!
		 *
		if(ButtonHasFilterList){
			iByteTotal += FilterList.Read_Bits(swf);
			printf( "      Use filters\n");
		}
		if(ButtonHasBlendMode){
			BlendMode = swf->ReadByte(); iByteTotal += 1;
			printf( "      Use Blend mode %d\n", BlendMode);
		}
		/**/

		return iTotBits;
	};
	int Write_Bits(SWFWriter *swf, int iIndex){
		int iTotBits=0;
		printf("    ButtonRecord[%d]\n", iIndex);

		swf->WriteUB(ButtonReserved, 2);
		swf->WriteUB(ButtonHasBlendMode, 1);
		swf->WriteUB(ButtonHasFilterList, 1);
		swf->WriteUB(ButtonStateHitTest, 1);
		swf->WriteUB(ButtonStateDown, 1);
		swf->WriteUB(ButtonStateOver, 1);
		swf->WriteUB(ButtonStateUp, 1);
	


		if( ButtonReserved==0 && ButtonHasBlendMode==0 && ButtonHasFilterList==0 && 
			ButtonStateHitTest==0 && ButtonStateDown==0 && ButtonStateOver==0 && 
			ButtonStateUp==0 ){
				printf ("    END_of_ButtonRecord\n" );
				return 8;
		}
		else
		{
			printf( "      ButtonState(%d/%d/%d/%d/%d/%d/%d)\n", 
				ButtonReserved,ButtonHasBlendMode,ButtonHasFilterList,
				ButtonStateHitTest,ButtonStateDown,ButtonStateOver,ButtonStateUp);
			iTotBits += 8;
		}


		// 2009-11-07 brucewang
		// If the first 8 byte of this record is 0,
		// the Flash player will misunderstood that this is the end of
		// button records. So, I think the Adobe Flash will put some
		// additional information in the rest of bits area after it write
		// the above 8bits..
		// So for later use, I copy those unknown bits..
		int iCurBitPos = swf->GetBitPosition();
		if( iCurBitPos>0 ) swf->WriteUB(bTemp, 7-iCurBitPos);
		// Even after the above trial, the leading byte becomes 0
		// so in that case, I make it 1 forcively.
		if( swf->GetBuffer()[swf->GetPosition()]== 0 ){
			((byte*)(swf->GetBuffer()))[swf->GetPosition()]=1;
		}


		swf->WriteUI16(CharacterID); iTotBits += 16;
		printf( "      CharacterID = %d\n", CharacterID); 
		swf->WriteUI16(PlaceDepth); iTotBits += 16;
		printf( "      PlaceDepth = %d\n", PlaceDepth);
		iTotBits += PlaceMatrix.Write_Bits(swf);
		iTotBits += ColorTransform.Write_Bits(swf);

		//((char*)swf->GetBuffer())[iSwfStartPos+1] |= 0x01;
		/*
		 * SWF 8 and later only !!!!!
		if(ButtonHasFilterList){
			iByteTotal += FilterList.Write_Bits(swf);
			printf( "      Use filters\n");
		}
		if(ButtonHasBlendMode){
			swf->WriteByte(BlendMode); iByteTotal += 1;
			printf( "      Use Blend mode %d\n", BlendMode);
		}
		*/

		return iTotBits;
	};
};

struct stDefineButton2{
	//ButtonId UI16 ID for this character
	UInt16 ButtonId;
	//ReservedFlags UB[7] Always 0
	byte ReservedFlags;
	//TrackAsMenu UB[1] 0 = track as normal button
	//1 = track as menu button
	byte TrackAsMenu;
	//ActionOffset UI16 Offset in bytes from start of this
	//field to the first
	//BUTTONCONDACTION, or 0
	//if no actions occur
	UInt16 ActionOffset;
	//Characters BUTTONRECORD
	//[one or more]
	//Characters that make up the
	//button
	stBUTTONRECORD Characters[256];
	//CharacterEndFlag UI8 Must be 0
	byte CharacterEndFlag;
	//Actions BUTTONCONDACTION
	//[zero or more]
	//Actions to execute at particular
	//button events
	stBUTTONCONDACTION Actions;

	int mi_NumCharacters;
	stDefineButton2(){
		mi_NumCharacters=0;
	}
	~stDefineButton2(){
	}

	int Read(SWFReader *swf){
		long lOrgSwfPos=swf->GetPosition();
		int iTotBits=0;

		ButtonId = swf->ReadUI16(); iTotBits+=16;
		printf("  ButtonId = %d\n", ButtonId );

		ReservedFlags = swf->ReadUB(7);
		TrackAsMenu = swf->ReadUB(1);
		printf("  TrackAsMenu = %d\n", TrackAsMenu );
		iTotBits+=8;

		ActionOffset = swf->ReadUI16(); iTotBits+=16;
		long lSwfPos = swf->GetPosition();
		if( ActionOffset>0 ){///
			int iIndex=0;
			while( swf->GetPosition()-lSwfPos+4 < ActionOffset ){
				iTotBits+=Characters[iIndex].Read_Bits(swf, iIndex);
				iIndex++;
			}
			mi_NumCharacters=iIndex;
			byte a = swf->ReadByte();
			iTotBits+=Actions.Read_Bits(swf);
		}

		return (swf->GetPosition()-lOrgSwfPos);//iTotBits;
	};
	int Write(SWFWriter *swf){
		long lOrgSwfPos=swf->GetPosition();
		int iTotBits=0;

		swf->WriteUI16(ButtonId); iTotBits+=16;
		printf("  ButtonId = %d\n", ButtonId );

		swf->WriteUB(ReservedFlags, 7);
		swf->WriteUB(TrackAsMenu, 1);
		printf("  TrackAsMenu = %d\n", TrackAsMenu );
		iTotBits+=8;

		swf->WriteUI16(ActionOffset); iTotBits+=16;
		long lSwfPos = swf->GetPosition();
		if( ActionOffset>0 ){///
			int iIndex=0;
			while( swf->GetPosition()-lSwfPos+4 < ActionOffset ){
				iTotBits+=Characters[iIndex].Write_Bits(swf, iIndex);
				iIndex++;
			}
			swf->WriteByte(0);
			iTotBits+=Actions.Write_Bits(swf);
		}

		return (swf->GetPosition()-lOrgSwfPos);//iTotBits;
	};
};

//
class DefineButton2 :
	public TagInstance
{
	stDefineButton2 mButton;

public:
	DefineButton2(void);
	~DefineButton2(void);

	virtual void ReadData(SWFReader *swf, int length);
    virtual void WriteData(SWFWriter *swf, int length);
    virtual ulong GetLength(void);
    virtual void SetLength(ulong len);

    virtual UInt16 GetCharacterID();
    virtual void SetCharacterID(UInt16 IdNew);
    virtual void IncreaseCharacterID(UInt16 nAmount);
};
