#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1386115845/heap_2.o ${OBJECTDIR}/_ext/1147412712/list.o ${OBJECTDIR}/_ext/843873358/port.o ${OBJECTDIR}/_ext/843873358/port_asm.o ${OBJECTDIR}/_ext/1147412712/queue.o ${OBJECTDIR}/_ext/1147412712/tasks.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1386115845/heap_2.o.d ${OBJECTDIR}/_ext/1147412712/list.o.d ${OBJECTDIR}/_ext/843873358/port.o.d ${OBJECTDIR}/_ext/843873358/port_asm.o.d ${OBJECTDIR}/_ext/1147412712/queue.o.d ${OBJECTDIR}/_ext/1147412712/tasks.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1386115845/heap_2.o ${OBJECTDIR}/_ext/1147412712/list.o ${OBJECTDIR}/_ext/843873358/port.o ${OBJECTDIR}/_ext/843873358/port_asm.o ${OBJECTDIR}/_ext/1147412712/queue.o ${OBJECTDIR}/_ext/1147412712/tasks.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/843873358/port_asm.o: ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/843873358 
	@${RM} ${OBJECTDIR}/_ext/843873358/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/843873358/port_asm.o.ok ${OBJECTDIR}/_ext/843873358/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/843873358/port_asm.o.d" "${OBJECTDIR}/_ext/843873358/port_asm.o.asm.d" -t $(SILENT) -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/843873358/port_asm.o.d"  -o ${OBJECTDIR}/_ext/843873358/port_asm.o ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/843873358/port_asm.o.asm.d",--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--gdwarf-2,--defsym=__DEBUG=1,--keep-locals,-I"../../../FreeRTOS/Source/portable/MPLAB/PIC32MX",-I"../..",-I".."
	
else
${OBJECTDIR}/_ext/843873358/port_asm.o: ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/843873358 
	@${RM} ${OBJECTDIR}/_ext/843873358/port_asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/843873358/port_asm.o.ok ${OBJECTDIR}/_ext/843873358/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/843873358/port_asm.o.d" "${OBJECTDIR}/_ext/843873358/port_asm.o.asm.d" -t $(SILENT) -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/_ext/843873358/port_asm.o.d"  -o ${OBJECTDIR}/_ext/843873358/port_asm.o ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port_asm.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/843873358/port_asm.o.asm.d",--gdwarf-2,--keep-locals,-I"../../../FreeRTOS/Source/portable/MPLAB/PIC32MX",-I"../..",-I".."
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/1386115845/heap_2.o: ../../FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1386115845 
	@${RM} ${OBJECTDIR}/_ext/1386115845/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1386115845/heap_2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1386115845/heap_2.o.d" -o ${OBJECTDIR}/_ext/1386115845/heap_2.o ../../FreeRTOS/Source/portable/MemMang/heap_2.c  
	
${OBJECTDIR}/_ext/1147412712/list.o: ../../FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/list.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/list.o.d" -o ${OBJECTDIR}/_ext/1147412712/list.o ../../FreeRTOS/Source/list.c  
	
${OBJECTDIR}/_ext/843873358/port.o: ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/843873358 
	@${RM} ${OBJECTDIR}/_ext/843873358/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/843873358/port.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/843873358/port.o.d" -o ${OBJECTDIR}/_ext/843873358/port.o ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  
	
${OBJECTDIR}/_ext/1147412712/queue.o: ../../FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/queue.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/queue.o.d" -o ${OBJECTDIR}/_ext/1147412712/queue.o ../../FreeRTOS/Source/queue.c  
	
${OBJECTDIR}/_ext/1147412712/tasks.o: ../../FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/tasks.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/tasks.o.d" -o ${OBJECTDIR}/_ext/1147412712/tasks.o ../../FreeRTOS/Source/tasks.c  
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/1386115845/heap_2.o: ../../FreeRTOS/Source/portable/MemMang/heap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1386115845 
	@${RM} ${OBJECTDIR}/_ext/1386115845/heap_2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1386115845/heap_2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1386115845/heap_2.o.d" -o ${OBJECTDIR}/_ext/1386115845/heap_2.o ../../FreeRTOS/Source/portable/MemMang/heap_2.c  
	
${OBJECTDIR}/_ext/1147412712/list.o: ../../FreeRTOS/Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/list.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/list.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/list.o.d" -o ${OBJECTDIR}/_ext/1147412712/list.o ../../FreeRTOS/Source/list.c  
	
${OBJECTDIR}/_ext/843873358/port.o: ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/843873358 
	@${RM} ${OBJECTDIR}/_ext/843873358/port.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/843873358/port.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/843873358/port.o.d" -o ${OBJECTDIR}/_ext/843873358/port.o ../../FreeRTOS/Source/portable/MPLAB/PIC32MX/port.c  
	
${OBJECTDIR}/_ext/1147412712/queue.o: ../../FreeRTOS/Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/queue.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/queue.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/queue.o.d" -o ${OBJECTDIR}/_ext/1147412712/queue.o ../../FreeRTOS/Source/queue.c  
	
${OBJECTDIR}/_ext/1147412712/tasks.o: ../../FreeRTOS/Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1147412712 
	@${RM} ${OBJECTDIR}/_ext/1147412712/tasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1147412712/tasks.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -DMPLAB_PIC32MX_PORT -I"../../Drivers FreeRTOS Micros-Designs/include" -I"../../../Microchip/Include" -I"../../Microchip/Include" -I"../../../../include" -I"../../../include" -I"../../include" -I".." -I"../../FreeRTOS/Source/include" -I"../../FreeRTOS/Source/portable/MPLAB/PIC32MX" -fomit-frame-pointer -Wall -MMD -MF "${OBJECTDIR}/_ext/1147412712/tasks.o.d" -o ${OBJECTDIR}/_ext/1147412712/tasks.o ../../FreeRTOS/Source/tasks.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=0,-L"..",-Map="${DISTDIR}/PrimerEjemplo.X.${IMAGE_TYPE}.map",-O3 
else
dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,-L"..",-Map="${DISTDIR}/PrimerEjemplo.X.${IMAGE_TYPE}.map",-O3
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PrimerEjemplo.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
