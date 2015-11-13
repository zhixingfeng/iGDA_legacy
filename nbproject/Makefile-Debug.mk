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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/iGDA.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModeler.o \
	${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModelerHomo.o \
	${OBJECTDIR}/src/plugin/PileupParser/PileupParser.o \
	${OBJECTDIR}/src/plugin/PileupParser/PileupParserGDA.o \
	${OBJECTDIR}/src/plugin/PreCaller/PreCaller.o \
	${OBJECTDIR}/src/plugin/PreCaller/PreCallerMultiple.o \
	${OBJECTDIR}/src/plugin/PreCaller/PreCallerSingle.o \
	${OBJECTDIR}/test/test_PileupParser.o \
	${OBJECTDIR}/test/test_data_type.o \
	${OBJECTDIR}/test/test_file.o \
	${OBJECTDIR}/test/test_iGDA.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/igda

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/igda: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/igda ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/iGDA.o: src/iGDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/iGDA.o src/iGDA.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModeler.o: src/plugin/ErrorModeler/ErrorModeler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/ErrorModeler
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModeler.o src/plugin/ErrorModeler/ErrorModeler.cpp

${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModelerHomo.o: src/plugin/ErrorModeler/ErrorModelerHomo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/ErrorModeler
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModelerHomo.o src/plugin/ErrorModeler/ErrorModelerHomo.cpp

${OBJECTDIR}/src/plugin/PileupParser/PileupParser.o: src/plugin/PileupParser/PileupParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PileupParser
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PileupParser/PileupParser.o src/plugin/PileupParser/PileupParser.cpp

${OBJECTDIR}/src/plugin/PileupParser/PileupParserGDA.o: src/plugin/PileupParser/PileupParserGDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PileupParser
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PileupParser/PileupParserGDA.o src/plugin/PileupParser/PileupParserGDA.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCaller.o: src/plugin/PreCaller/PreCaller.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCaller.o src/plugin/PreCaller/PreCaller.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCallerMultiple.o: src/plugin/PreCaller/PreCallerMultiple.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCallerMultiple.o src/plugin/PreCaller/PreCallerMultiple.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCallerSingle.o: src/plugin/PreCaller/PreCallerSingle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCallerSingle.o src/plugin/PreCaller/PreCallerSingle.cpp

${OBJECTDIR}/test/test_PileupParser.o: test/test_PileupParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_PileupParser.o test/test_PileupParser.cpp

${OBJECTDIR}/test/test_data_type.o: test/test_data_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_data_type.o test/test_data_type.cpp

${OBJECTDIR}/test/test_file.o: test/test_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_file.o test/test_file.cpp

${OBJECTDIR}/test/test_iGDA.o: test/test_iGDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_iGDA.o test/test_iGDA.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/igda

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
