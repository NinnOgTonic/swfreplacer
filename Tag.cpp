/* 
 * File:   Tag.cpp
 * Author: brucewang
 * 
 * Created on October 24, 2009, 9:05 PM
 */

#include "Tag.h"
#include "Rect.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "DefineEditText.h"
#include "DefineJPEG2.h"
#include "Exports.h"
#include "DefineSprite.h"
#include "TagWithCharacterID.h"
#include "PlaceObject2.h"
#include "DefineShape.h"
#include "DefineButton2.h"
#include "DefineFont2.h"
#include "DefineText.h"

std::map<unsigned short, const char*> Tag::m_IdNameTable;

ushort Tag::ID() {
    return id;
}

ulong Tag::GetLength() {
    if (m_pTagInstance) {
        ulong lHdrLen = 0;
        ulong lCntLen = m_pTagInstance->GetLength();
        lHdrLen += 2; // TagInfo.
        if (lCntLen > 63) {
            lHdrLen += 4; // Long size
        }

        return lHdrLen + lCntLen;
    }

    printf("No Tag instance exists.\n");
    return 0;
}

Tag::Tag(SWFReader *swf) {
    m_pTagInstance = 0;
    Tag::_initMatchTable();

    Read(swf);
}

Tag::~Tag() {
    if (m_pTagInstance) delete(m_pTagInstance);
}

void Tag::_readIdAndLength(SWFReader *swf) {
    tagInfo = swf->ReadUI16();
    this->id = (ushort) (tagInfo >> 6);
    ulong length = (ulong) (tagInfo & 0x3f);

    // Is this a long data block?
    if (length == 0x3f) {
        length = swf->ReadUI32();
    }

    printf("Tag : %s (length : %ld)\n", GetType(this->ID()), length);


    if (37 == this->ID()) //EditText
    {
        m_pTagInstance = new DefineEditText();
    } else if (21 == this->ID()) // DefineBitsJPEG2
    {
        m_pTagInstance = new DefineJPEG2();
    } else if (56 == this->ID()) {
        m_pTagInstance = new Exports();
    } else if (39 == this->ID()) {
        m_pTagInstance = new DefineSprite();
    } else if (26 == this->ID()) {
        m_pTagInstance = new PlaceObject2();
    }
    else if (2 == this->ID()) {
        m_pTagInstance = new DefineShape();
    } else if (34 == this->ID()) {
        m_pTagInstance = new DefineButton2();
    } else if (48 == this->ID()) {
        m_pTagInstance = new DefineFont2();
    }
    else if (11 == this->ID()) {
        m_pTagInstance = new DefineText();
    } else if (
            0 == strncmp(GetType(this->ID()), "Define", strlen("Define"))
            ||
            4 == this->ID() // PlaceObject
            ||
            5 == this->ID() // RemoveObject
            ) {
        m_pTagInstance = new TagWithCharacterID();
    } else {
        m_pTagInstance = new TagInstance();
    }

    m_pTagInstance->SetLength(length);
}

void Tag::Read(SWFReader *swf) {
    _readIdAndLength(swf);

    m_pTagInstance->ReadData(swf, m_pTagInstance->GetLength());
}

void Tag::_writeIdAndLength(SWFWriter *swf) {
    // Make TagInfo value.
    UInt16 tagInfoTmp;
    tagInfoTmp = this->id << 6;
    if (m_pTagInstance->GetLength() >= 63) {
        tagInfoTmp |= 0x003f;
    } else {
        tagInfoTmp |= (0x003f & m_pTagInstance->GetLength());
    }
    swf->WriteUI16(tagInfoTmp);
    if (m_pTagInstance->GetLength() > 63) {
        swf->WriteUI32(m_pTagInstance->GetLength()); // long length
    }

    printf("Tag : %s (length : %ld)\n", GetType(this->ID()), m_pTagInstance->GetLength());
}

void Tag::Write(SWFWriter *swf) {
    _writeIdAndLength(swf);

    m_pTagInstance->WriteData(swf, m_pTagInstance->GetLength());
}

// Return the tag type
// Special thanks to Alexis: http://sswf.sourceforge.net/SWFalexref.html#table_of_swf_tags

const char* Tag::GetType(ushort id) {
    //szstring result = (char*) "(unknown)";
    const char *sz = Tag::m_IdNameTable[id];
    return sz == 0 ? "UnKnown" : sz;
}

void Tag::_initMatchTable() {
    if (!Tag::m_IdNameTable.empty())
        return;

    Tag::m_IdNameTable[0] = "End (V1.0)";
    Tag::m_IdNameTable[1] = "ShowFrame (V1.0)";
    Tag::m_IdNameTable[2] = "DefineShape (V1.0)";
    Tag::m_IdNameTable[3] = "FreeCharacter (V1.0)";
    Tag::m_IdNameTable[4] = "PlaceObject (V1.0)";
    Tag::m_IdNameTable[5] = "RemoveObject (V1.0)";
    Tag::m_IdNameTable[6] = "DefineBits (V1.0)";
    Tag::m_IdNameTable[7] = "DefineButton (V1.0)";
    Tag::m_IdNameTable[8] = "JPEGTables (V1.0)";
    Tag::m_IdNameTable[9] = "SetBackgroundColor (V1.0)";
    Tag::m_IdNameTable[10] = "DefineFont (V1.0)";
    Tag::m_IdNameTable[11] = "DefineText (V1.0)";
    Tag::m_IdNameTable[12] = "DoAction (V1.0)";
    Tag::m_IdNameTable[13] = "DefineFontInfo (V1.0)";
    Tag::m_IdNameTable[14] = "DefineSound (V2.0)";
    Tag::m_IdNameTable[15] = "StartSound (V2.0)";
    Tag::m_IdNameTable[16] = "StopSound (V2.0)";
    Tag::m_IdNameTable[17] = "DefineButtonSound (V2.0)";
    Tag::m_IdNameTable[18] = "SoundStreamHead (V2.0)";
    Tag::m_IdNameTable[19] = "SoundStreamBlock (V2.0)";
    Tag::m_IdNameTable[20] = "DefineBitsLossless (V2.0)";
    Tag::m_IdNameTable[21] = "DefineBitsJPEG2 (V2.0)";
    Tag::m_IdNameTable[22] = "DefineShape2 (V2.0)";
    Tag::m_IdNameTable[23] = "DefineButtonCxform (V2.0)";
    Tag::m_IdNameTable[24] = "Protect (V2.0)";
    Tag::m_IdNameTable[25] = "PathsArePostscript (V3.0)";
    Tag::m_IdNameTable[26] = "PlaceObject2 (V3.0)";
    Tag::m_IdNameTable[28] = "RemoveObject2 (V3.0)";
    Tag::m_IdNameTable[29] = "SyncFrame (V3.0)";
    Tag::m_IdNameTable[31] = "FreeAll (V3.0)";
    Tag::m_IdNameTable[32] = "DefineShape3 (V3.0)";
    Tag::m_IdNameTable[33] = "DefineText2 (V3.0)";
    Tag::m_IdNameTable[34] = "DefineButton2 (V3.0)";
    Tag::m_IdNameTable[35] = "DefineBitsJPEG3 (V3.0)";
    Tag::m_IdNameTable[36] = "DefineBitsLossless2 (V3.0)";
    Tag::m_IdNameTable[37] = "DefineEditText (V4.0)";
    Tag::m_IdNameTable[38] = "DefineVideo (V4.0)";
    Tag::m_IdNameTable[39] = "DefineSprite (V3.0)";
    Tag::m_IdNameTable[40] = "NameCharacter (V3.0)";
    Tag::m_IdNameTable[41] = "SerialNumber (V3.0)";
    Tag::m_IdNameTable[42] = "DefineTextFormat (V3.0)";
    Tag::m_IdNameTable[43] = "FrameLabel (V3.0)";
    Tag::m_IdNameTable[45] = "SoundStreamHead2 (V3.0)";
    Tag::m_IdNameTable[46] = "DefineMorphShape (V3.0)";
    Tag::m_IdNameTable[47] = "GenerateFrame (V3.0)";
    Tag::m_IdNameTable[48] = "DefineFont2 (V3.0)";
    Tag::m_IdNameTable[49] = "GeneratorCommand (V3.0)";
    Tag::m_IdNameTable[50] = "DefineCommandObject (V5.0)";
    Tag::m_IdNameTable[51] = "CharacterSet (V5.0)";
    Tag::m_IdNameTable[52] = "ExternalFont (V5.0)";
    Tag::m_IdNameTable[56] = "Export (V5.0)";
    Tag::m_IdNameTable[57] = "Import (V5.0)";
    Tag::m_IdNameTable[58] = "ProtectDebug (V5.0)";
    Tag::m_IdNameTable[59] = "DoInitAction (V6.0)";
    Tag::m_IdNameTable[60] = "DefineVideoStream (V6.0)";
    Tag::m_IdNameTable[61] = "VideoFrame (V6.0)";
    Tag::m_IdNameTable[62] = "DefineFontInfo2 (V6.0)";
    Tag::m_IdNameTable[64] = "ProtectDebug2 (V6.0)";
    Tag::m_IdNameTable[65] = "ScriptLimits (V7.0)";
    Tag::m_IdNameTable[66] = "SetTabIndex (V7.0)";
    Tag::m_IdNameTable[69] = "FileAttributes (V8.0)";
    Tag::m_IdNameTable[70] = "PlaceObject3 (V8.0)";
    Tag::m_IdNameTable[71] = "Import2 (V8.0)";
    Tag::m_IdNameTable[73] = "DefineFontAlignZones (V8.0)";
    Tag::m_IdNameTable[74] = "CSMTextSettings (V8.0)";
    Tag::m_IdNameTable[75] = "DefineFont3 (V8.0)";
    Tag::m_IdNameTable[77] = "Metadata (V8.0)";
    Tag::m_IdNameTable[78] = "DefineScalingGrid (V8.0)";
    Tag::m_IdNameTable[83] = "DefineShape4 (V8.0)";
    Tag::m_IdNameTable[84] = "DefineMorphShape2 (V8.0)";
}