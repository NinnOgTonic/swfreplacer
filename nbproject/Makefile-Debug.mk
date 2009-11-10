#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DefineText.o \
	${OBJECTDIR}/Exports.o \
	${OBJECTDIR}/DefineFont2.o \
	${OBJECTDIR}/DefineFont.o \
	${OBJECTDIR}/Rect.o \
	${OBJECTDIR}/DefineEditText.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/PlaceObject2.o \
	${OBJECTDIR}/Tag.o \
	${OBJECTDIR}/DefineButton2.o \
	${OBJECTDIR}/TagWithCharacterID.o \
	${OBJECTDIR}/DefineShape.o \
	${OBJECTDIR}/SWFReader.o \
	${OBJECTDIR}/SWFFile.o \
	${OBJECTDIR}/Header.o \
	${OBJECTDIR}/DefineJPEG2.o \
	${OBJECTDIR}/DefineSprite.o \
	${OBJECTDIR}/TagInstance.o \
	${OBJECTDIR}/SWFWriter.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-MacOSX/swfreplacer

dist/Debug/GNU-MacOSX/swfreplacer: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-MacOSX
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/swfreplacer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/DefineText.o: nbproject/Makefile-${CND_CONF}.mk DefineText.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineText.o DefineText.cpp

${OBJECTDIR}/Exports.o: nbproject/Makefile-${CND_CONF}.mk Exports.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Exports.o Exports.cpp

${OBJECTDIR}/DefineFont2.o: nbproject/Makefile-${CND_CONF}.mk DefineFont2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineFont2.o DefineFont2.cpp

${OBJECTDIR}/DefineFont.o: nbproject/Makefile-${CND_CONF}.mk DefineFont.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineFont.o DefineFont.cpp

${OBJECTDIR}/Rect.o: nbproject/Makefile-${CND_CONF}.mk Rect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Rect.o Rect.cpp

${OBJECTDIR}/DefineEditText.o: nbproject/Makefile-${CND_CONF}.mk DefineEditText.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineEditText.o DefineEditText.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/PlaceObject2.o: nbproject/Makefile-${CND_CONF}.mk PlaceObject2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/PlaceObject2.o PlaceObject2.cpp

${OBJECTDIR}/Tag.o: nbproject/Makefile-${CND_CONF}.mk Tag.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Tag.o Tag.cpp

${OBJECTDIR}/DefineButton2.o: nbproject/Makefile-${CND_CONF}.mk DefineButton2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineButton2.o DefineButton2.cpp

${OBJECTDIR}/TagWithCharacterID.o: nbproject/Makefile-${CND_CONF}.mk TagWithCharacterID.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/TagWithCharacterID.o TagWithCharacterID.cpp

${OBJECTDIR}/DefineShape.o: nbproject/Makefile-${CND_CONF}.mk DefineShape.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineShape.o DefineShape.cpp

${OBJECTDIR}/SWFReader.o: nbproject/Makefile-${CND_CONF}.mk SWFReader.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SWFReader.o SWFReader.cpp

${OBJECTDIR}/SWFFile.o: nbproject/Makefile-${CND_CONF}.mk SWFFile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SWFFile.o SWFFile.cpp

${OBJECTDIR}/Header.o: nbproject/Makefile-${CND_CONF}.mk Header.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/Header.o Header.cpp

${OBJECTDIR}/DefineJPEG2.o: nbproject/Makefile-${CND_CONF}.mk DefineJPEG2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineJPEG2.o DefineJPEG2.cpp

${OBJECTDIR}/DefineSprite.o: nbproject/Makefile-${CND_CONF}.mk DefineSprite.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/DefineSprite.o DefineSprite.cpp

${OBJECTDIR}/TagInstance.o: nbproject/Makefile-${CND_CONF}.mk TagInstance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/TagInstance.o TagInstance.cpp

${OBJECTDIR}/SWFWriter.o: nbproject/Makefile-${CND_CONF}.mk SWFWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/SWFWriter.o SWFWriter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-MacOSX/swfreplacer

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
