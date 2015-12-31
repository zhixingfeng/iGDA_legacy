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
CND_CONF=Release
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
	${OBJECTDIR}/src/tool/boost/src/filesystem/codecvt_error_category.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/operations.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/path.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/path_traits.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/portability.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/unique_path.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/utf8_codecvt_facet.o \
	${OBJECTDIR}/src/tool/boost/src/filesystem/windows_file_codecvt.o \
	${OBJECTDIR}/src/tool/boost/src/system/error_code.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_md5.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_md5wrapper.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha1.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha1wrapper.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha256.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha256wrapper.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha2ext.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha384wrapper.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_sha512wrapper.o \
	${OBJECTDIR}/src/tool/hashlibpp/hl_wrapperfactory.o \
	${OBJECTDIR}/src/tool/prob/prob.o \
	${OBJECTDIR}/src/util/BamFilter.o \
	${OBJECTDIR}/test/test_ErrorModeler.o \
	${OBJECTDIR}/test/test_PileupParser.o \
	${OBJECTDIR}/test/test_PreCaller.o \
	${OBJECTDIR}/test/test_basic.o \
	${OBJECTDIR}/test/test_data_type.o \
	${OBJECTDIR}/test/test_file.o \
	${OBJECTDIR}/test/test_iGDA.o \
	${OBJECTDIR}/test/test_performance.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Lthird_party/src/bamtools/lib -lbamtools
CXXFLAGS=-Lthird_party/src/bamtools/lib -lbamtools

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
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/iGDA.o src/iGDA.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModeler.o: src/plugin/ErrorModeler/ErrorModeler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/ErrorModeler
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModeler.o src/plugin/ErrorModeler/ErrorModeler.cpp

${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModelerHomo.o: src/plugin/ErrorModeler/ErrorModelerHomo.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/ErrorModeler
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/ErrorModeler/ErrorModelerHomo.o src/plugin/ErrorModeler/ErrorModelerHomo.cpp

${OBJECTDIR}/src/plugin/PileupParser/PileupParser.o: src/plugin/PileupParser/PileupParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PileupParser
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PileupParser/PileupParser.o src/plugin/PileupParser/PileupParser.cpp

${OBJECTDIR}/src/plugin/PileupParser/PileupParserGDA.o: src/plugin/PileupParser/PileupParserGDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PileupParser
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PileupParser/PileupParserGDA.o src/plugin/PileupParser/PileupParserGDA.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCaller.o: src/plugin/PreCaller/PreCaller.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCaller.o src/plugin/PreCaller/PreCaller.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCallerMultiple.o: src/plugin/PreCaller/PreCallerMultiple.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCallerMultiple.o src/plugin/PreCaller/PreCallerMultiple.cpp

${OBJECTDIR}/src/plugin/PreCaller/PreCallerSingle.o: src/plugin/PreCaller/PreCallerSingle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/plugin/PreCaller
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/plugin/PreCaller/PreCallerSingle.o src/plugin/PreCaller/PreCallerSingle.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/codecvt_error_category.o: src/tool/boost/src/filesystem/codecvt_error_category.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/codecvt_error_category.o src/tool/boost/src/filesystem/codecvt_error_category.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/operations.o: src/tool/boost/src/filesystem/operations.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/operations.o src/tool/boost/src/filesystem/operations.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/path.o: src/tool/boost/src/filesystem/path.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/path.o src/tool/boost/src/filesystem/path.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/path_traits.o: src/tool/boost/src/filesystem/path_traits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/path_traits.o src/tool/boost/src/filesystem/path_traits.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/portability.o: src/tool/boost/src/filesystem/portability.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/portability.o src/tool/boost/src/filesystem/portability.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/unique_path.o: src/tool/boost/src/filesystem/unique_path.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/unique_path.o src/tool/boost/src/filesystem/unique_path.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/utf8_codecvt_facet.o: src/tool/boost/src/filesystem/utf8_codecvt_facet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/utf8_codecvt_facet.o src/tool/boost/src/filesystem/utf8_codecvt_facet.cpp

${OBJECTDIR}/src/tool/boost/src/filesystem/windows_file_codecvt.o: src/tool/boost/src/filesystem/windows_file_codecvt.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/filesystem
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/filesystem/windows_file_codecvt.o src/tool/boost/src/filesystem/windows_file_codecvt.cpp

${OBJECTDIR}/src/tool/boost/src/system/error_code.o: src/tool/boost/src/system/error_code.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/boost/src/system
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/boost/src/system/error_code.o src/tool/boost/src/system/error_code.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_md5.o: src/tool/hashlibpp/hl_md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_md5.o src/tool/hashlibpp/hl_md5.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_md5wrapper.o: src/tool/hashlibpp/hl_md5wrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_md5wrapper.o src/tool/hashlibpp/hl_md5wrapper.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha1.o: src/tool/hashlibpp/hl_sha1.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha1.o src/tool/hashlibpp/hl_sha1.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha1wrapper.o: src/tool/hashlibpp/hl_sha1wrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha1wrapper.o src/tool/hashlibpp/hl_sha1wrapper.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha256.o: src/tool/hashlibpp/hl_sha256.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha256.o src/tool/hashlibpp/hl_sha256.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha256wrapper.o: src/tool/hashlibpp/hl_sha256wrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha256wrapper.o src/tool/hashlibpp/hl_sha256wrapper.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha2ext.o: src/tool/hashlibpp/hl_sha2ext.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha2ext.o src/tool/hashlibpp/hl_sha2ext.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha384wrapper.o: src/tool/hashlibpp/hl_sha384wrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha384wrapper.o src/tool/hashlibpp/hl_sha384wrapper.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_sha512wrapper.o: src/tool/hashlibpp/hl_sha512wrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_sha512wrapper.o src/tool/hashlibpp/hl_sha512wrapper.cpp

${OBJECTDIR}/src/tool/hashlibpp/hl_wrapperfactory.o: src/tool/hashlibpp/hl_wrapperfactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/hashlibpp
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/hashlibpp/hl_wrapperfactory.o src/tool/hashlibpp/hl_wrapperfactory.cpp

${OBJECTDIR}/src/tool/prob/prob.o: src/tool/prob/prob.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/tool/prob
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/tool/prob/prob.o src/tool/prob/prob.cpp

${OBJECTDIR}/src/util/BamFilter.o: src/util/BamFilter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/util
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/util/BamFilter.o src/util/BamFilter.cpp

${OBJECTDIR}/test/test_ErrorModeler.o: test/test_ErrorModeler.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_ErrorModeler.o test/test_ErrorModeler.cpp

${OBJECTDIR}/test/test_PileupParser.o: test/test_PileupParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_PileupParser.o test/test_PileupParser.cpp

${OBJECTDIR}/test/test_PreCaller.o: test/test_PreCaller.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_PreCaller.o test/test_PreCaller.cpp

${OBJECTDIR}/test/test_basic.o: test/test_basic.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_basic.o test/test_basic.cpp

${OBJECTDIR}/test/test_data_type.o: test/test_data_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_data_type.o test/test_data_type.cpp

${OBJECTDIR}/test/test_file.o: test/test_file.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_file.o test/test_file.cpp

${OBJECTDIR}/test/test_iGDA.o: test/test_iGDA.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_iGDA.o test/test_iGDA.cpp

${OBJECTDIR}/test/test_performance.o: test/test_performance.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -Iinclude -Isrc/tool -Isrc/tool/hashlibpp -Isrc/tool/boost/include -Ithird_party/src/bamtools/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/test_performance.o test/test_performance.cpp

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
