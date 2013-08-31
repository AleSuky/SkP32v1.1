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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1106642868/mbascii.o ${OBJECTDIR}/_ext/772365078/mbfunccoils.o ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o ${OBJECTDIR}/_ext/772365078/mbfuncholding.o ${OBJECTDIR}/_ext/772365078/mbfuncinput.o ${OBJECTDIR}/_ext/772365078/mbfuncother.o ${OBJECTDIR}/_ext/772365078/mbutils.o ${OBJECTDIR}/_ext/463668782/mbcrc.o ${OBJECTDIR}/_ext/463668782/mbrtu.o ${OBJECTDIR}/_ext/463670172/mbtcp.o ${OBJECTDIR}/_ext/1350393014/mb.o ${OBJECTDIR}/_ext/385479254/TimeDelay.o ${OBJECTDIR}/_ext/760710288/portevent.o ${OBJECTDIR}/_ext/760710288/portserial.o ${OBJECTDIR}/_ext/760710288/porttimer.o ${OBJECTDIR}/_ext/1472/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1106642868/mbascii.o.d ${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d ${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d ${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d ${OBJECTDIR}/_ext/772365078/mbfuncother.o.d ${OBJECTDIR}/_ext/772365078/mbutils.o.d ${OBJECTDIR}/_ext/463668782/mbcrc.o.d ${OBJECTDIR}/_ext/463668782/mbrtu.o.d ${OBJECTDIR}/_ext/463670172/mbtcp.o.d ${OBJECTDIR}/_ext/1350393014/mb.o.d ${OBJECTDIR}/_ext/385479254/TimeDelay.o.d ${OBJECTDIR}/_ext/760710288/portevent.o.d ${OBJECTDIR}/_ext/760710288/portserial.o.d ${OBJECTDIR}/_ext/760710288/porttimer.o.d ${OBJECTDIR}/_ext/1472/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1106642868/mbascii.o ${OBJECTDIR}/_ext/772365078/mbfunccoils.o ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o ${OBJECTDIR}/_ext/772365078/mbfuncholding.o ${OBJECTDIR}/_ext/772365078/mbfuncinput.o ${OBJECTDIR}/_ext/772365078/mbfuncother.o ${OBJECTDIR}/_ext/772365078/mbutils.o ${OBJECTDIR}/_ext/463668782/mbcrc.o ${OBJECTDIR}/_ext/463668782/mbrtu.o ${OBJECTDIR}/_ext/463670172/mbtcp.o ${OBJECTDIR}/_ext/1350393014/mb.o ${OBJECTDIR}/_ext/385479254/TimeDelay.o ${OBJECTDIR}/_ext/760710288/portevent.o ${OBJECTDIR}/_ext/760710288/portserial.o ${OBJECTDIR}/_ext/760710288/porttimer.o ${OBJECTDIR}/_ext/1472/main.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1106642868/mbascii.o: ../../freemodbus/ascii/mbascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1106642868 
	@${RM} ${OBJECTDIR}/_ext/1106642868/mbascii.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1106642868/mbascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1106642868/mbascii.o.d" -o ${OBJECTDIR}/_ext/1106642868/mbascii.o ../../freemodbus/ascii/mbascii.c  
	
${OBJECTDIR}/_ext/772365078/mbfunccoils.o: ../../freemodbus/functions/mbfunccoils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfunccoils.o ../../freemodbus/functions/mbfunccoils.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncdiag.o: ../../freemodbus/functions/mbfuncdiag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o ../../freemodbus/functions/mbfuncdiag.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncdisc.o: ../../freemodbus/functions/mbfuncdisc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o ../../freemodbus/functions/mbfuncdisc.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncholding.o: ../../freemodbus/functions/mbfuncholding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncholding.o ../../freemodbus/functions/mbfuncholding.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncinput.o: ../../freemodbus/functions/mbfuncinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncinput.o ../../freemodbus/functions/mbfuncinput.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncother.o: ../../freemodbus/functions/mbfuncother.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncother.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncother.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncother.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncother.o ../../freemodbus/functions/mbfuncother.c  
	
${OBJECTDIR}/_ext/772365078/mbutils.o: ../../freemodbus/functions/mbutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbutils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbutils.o.d" -o ${OBJECTDIR}/_ext/772365078/mbutils.o ../../freemodbus/functions/mbutils.c  
	
${OBJECTDIR}/_ext/463668782/mbcrc.o: ../../freemodbus/rtu/mbcrc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463668782 
	@${RM} ${OBJECTDIR}/_ext/463668782/mbcrc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463668782/mbcrc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463668782/mbcrc.o.d" -o ${OBJECTDIR}/_ext/463668782/mbcrc.o ../../freemodbus/rtu/mbcrc.c  
	
${OBJECTDIR}/_ext/463668782/mbrtu.o: ../../freemodbus/rtu/mbrtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463668782 
	@${RM} ${OBJECTDIR}/_ext/463668782/mbrtu.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463668782/mbrtu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463668782/mbrtu.o.d" -o ${OBJECTDIR}/_ext/463668782/mbrtu.o ../../freemodbus/rtu/mbrtu.c  
	
${OBJECTDIR}/_ext/463670172/mbtcp.o: ../../freemodbus/tcp/mbtcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463670172 
	@${RM} ${OBJECTDIR}/_ext/463670172/mbtcp.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463670172/mbtcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463670172/mbtcp.o.d" -o ${OBJECTDIR}/_ext/463670172/mbtcp.o ../../freemodbus/tcp/mbtcp.c  
	
${OBJECTDIR}/_ext/1350393014/mb.o: ../../freemodbus/mb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1350393014 
	@${RM} ${OBJECTDIR}/_ext/1350393014/mb.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1350393014/mb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1350393014/mb.o.d" -o ${OBJECTDIR}/_ext/1350393014/mb.o ../../freemodbus/mb.c  
	
${OBJECTDIR}/_ext/385479254/TimeDelay.o: ../../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/385479254 
	@${RM} ${OBJECTDIR}/_ext/385479254/TimeDelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/385479254/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/385479254/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/385479254/TimeDelay.o ../../Microchip/Common/TimeDelay.c  
	
${OBJECTDIR}/_ext/760710288/portevent.o: ../port/portevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/portevent.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/portevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/portevent.o.d" -o ${OBJECTDIR}/_ext/760710288/portevent.o ../port/portevent.c  
	
${OBJECTDIR}/_ext/760710288/portserial.o: ../port/portserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/portserial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/portserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/portserial.o.d" -o ${OBJECTDIR}/_ext/760710288/portserial.o ../port/portserial.c  
	
${OBJECTDIR}/_ext/760710288/porttimer.o: ../port/porttimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/porttimer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/porttimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/porttimer.o.d" -o ${OBJECTDIR}/_ext/760710288/porttimer.o ../port/porttimer.c  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
else
${OBJECTDIR}/_ext/1106642868/mbascii.o: ../../freemodbus/ascii/mbascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1106642868 
	@${RM} ${OBJECTDIR}/_ext/1106642868/mbascii.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1106642868/mbascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1106642868/mbascii.o.d" -o ${OBJECTDIR}/_ext/1106642868/mbascii.o ../../freemodbus/ascii/mbascii.c  
	
${OBJECTDIR}/_ext/772365078/mbfunccoils.o: ../../freemodbus/functions/mbfunccoils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfunccoils.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfunccoils.o ../../freemodbus/functions/mbfunccoils.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncdiag.o: ../../freemodbus/functions/mbfuncdiag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncdiag.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncdiag.o ../../freemodbus/functions/mbfuncdiag.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncdisc.o: ../../freemodbus/functions/mbfuncdisc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncdisc.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncdisc.o ../../freemodbus/functions/mbfuncdisc.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncholding.o: ../../freemodbus/functions/mbfuncholding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncholding.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncholding.o ../../freemodbus/functions/mbfuncholding.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncinput.o: ../../freemodbus/functions/mbfuncinput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncinput.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncinput.o ../../freemodbus/functions/mbfuncinput.c  
	
${OBJECTDIR}/_ext/772365078/mbfuncother.o: ../../freemodbus/functions/mbfuncother.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbfuncother.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbfuncother.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbfuncother.o.d" -o ${OBJECTDIR}/_ext/772365078/mbfuncother.o ../../freemodbus/functions/mbfuncother.c  
	
${OBJECTDIR}/_ext/772365078/mbutils.o: ../../freemodbus/functions/mbutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/772365078 
	@${RM} ${OBJECTDIR}/_ext/772365078/mbutils.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/772365078/mbutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/772365078/mbutils.o.d" -o ${OBJECTDIR}/_ext/772365078/mbutils.o ../../freemodbus/functions/mbutils.c  
	
${OBJECTDIR}/_ext/463668782/mbcrc.o: ../../freemodbus/rtu/mbcrc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463668782 
	@${RM} ${OBJECTDIR}/_ext/463668782/mbcrc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463668782/mbcrc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463668782/mbcrc.o.d" -o ${OBJECTDIR}/_ext/463668782/mbcrc.o ../../freemodbus/rtu/mbcrc.c  
	
${OBJECTDIR}/_ext/463668782/mbrtu.o: ../../freemodbus/rtu/mbrtu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463668782 
	@${RM} ${OBJECTDIR}/_ext/463668782/mbrtu.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463668782/mbrtu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463668782/mbrtu.o.d" -o ${OBJECTDIR}/_ext/463668782/mbrtu.o ../../freemodbus/rtu/mbrtu.c  
	
${OBJECTDIR}/_ext/463670172/mbtcp.o: ../../freemodbus/tcp/mbtcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/463670172 
	@${RM} ${OBJECTDIR}/_ext/463670172/mbtcp.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/463670172/mbtcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/463670172/mbtcp.o.d" -o ${OBJECTDIR}/_ext/463670172/mbtcp.o ../../freemodbus/tcp/mbtcp.c  
	
${OBJECTDIR}/_ext/1350393014/mb.o: ../../freemodbus/mb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1350393014 
	@${RM} ${OBJECTDIR}/_ext/1350393014/mb.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1350393014/mb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1350393014/mb.o.d" -o ${OBJECTDIR}/_ext/1350393014/mb.o ../../freemodbus/mb.c  
	
${OBJECTDIR}/_ext/385479254/TimeDelay.o: ../../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/385479254 
	@${RM} ${OBJECTDIR}/_ext/385479254/TimeDelay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/385479254/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/385479254/TimeDelay.o.d" -o ${OBJECTDIR}/_ext/385479254/TimeDelay.o ../../Microchip/Common/TimeDelay.c  
	
${OBJECTDIR}/_ext/760710288/portevent.o: ../port/portevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/portevent.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/portevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/portevent.o.d" -o ${OBJECTDIR}/_ext/760710288/portevent.o ../port/portevent.c  
	
${OBJECTDIR}/_ext/760710288/portserial.o: ../port/portserial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/portserial.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/portserial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/portserial.o.d" -o ${OBJECTDIR}/_ext/760710288/portserial.o ../port/portserial.c  
	
${OBJECTDIR}/_ext/760710288/porttimer.o: ../port/porttimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/760710288 
	@${RM} ${OBJECTDIR}/_ext/760710288/porttimer.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760710288/porttimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/760710288/porttimer.o.d" -o ${OBJECTDIR}/_ext/760710288/porttimer.o ../port/porttimer.c  
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../port" -I"../../freemodbus/tcp" -I"../../freemodbus/rtu" -I"../../freemodbus/ascii" -I"../../freemodbus/include" -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,-L"..",-Map="${DISTDIR}/TestModbus.X.${IMAGE_TYPE}.map" 
else
dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../app.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,-L"..",-Map="${DISTDIR}/TestModbus.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TestModbus.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
