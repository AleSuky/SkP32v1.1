#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1770187969/SD-SPI.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/17042719/diskio.o ${OBJECTDIR}/_ext/17042719/ff.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/17042719/diskio.o.d ${OBJECTDIR}/_ext/17042719/ff.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1770187969/SD-SPI.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/17042719/diskio.o ${OBJECTDIR}/_ext/17042719/ff.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=,--script="..\app.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1770187969/SD-SPI.o: ../SD-SPI/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1770187969 
	@${RM} ${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1770187969/SD-SPI.o ../SD-SPI/SD-SPI.c  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/17042719/diskio.o: ../../fsfat/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17042719 
	@${RM} ${OBJECTDIR}/_ext/17042719/diskio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17042719/diskio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/17042719/diskio.o.d" -o ${OBJECTDIR}/_ext/17042719/diskio.o ../../fsfat/src/diskio.c  
	
${OBJECTDIR}/_ext/17042719/ff.o: ../../fsfat/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17042719 
	@${RM} ${OBJECTDIR}/_ext/17042719/ff.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17042719/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/17042719/ff.o.d" -o ${OBJECTDIR}/_ext/17042719/ff.o ../../fsfat/src/ff.c  
	
else
${OBJECTDIR}/_ext/1770187969/SD-SPI.o: ../SD-SPI/SD-SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1770187969 
	@${RM} ${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/1770187969/SD-SPI.o.d" -o ${OBJECTDIR}/_ext/1770187969/SD-SPI.o ../SD-SPI/SD-SPI.c  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/17042719/diskio.o: ../../fsfat/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17042719 
	@${RM} ${OBJECTDIR}/_ext/17042719/diskio.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17042719/diskio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/17042719/diskio.o.d" -o ${OBJECTDIR}/_ext/17042719/diskio.o ../../fsfat/src/diskio.c  
	
${OBJECTDIR}/_ext/17042719/ff.o: ../../fsfat/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/17042719 
	@${RM} ${OBJECTDIR}/_ext/17042719/ff.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/17042719/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../fsfat/src" -I"../SD-SPI" -I".." -MMD -MF "${OBJECTDIR}/_ext/17042719/ff.o.d" -o ${OBJECTDIR}/_ext/17042719/ff.o ../../fsfat/src/ff.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-L"..",-Map="${DISTDIR}/TestFSFat.X.${IMAGE_TYPE}.map" 
else
dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-L"..",-Map="${DISTDIR}/TestFSFat.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TestFSFat.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
