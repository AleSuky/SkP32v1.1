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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/713068069/usb_host.o ${OBJECTDIR}/_ext/65885567/FSIO.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/1472/usb_config.o.d ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d ${OBJECTDIR}/_ext/713068069/usb_host.o.d ${OBJECTDIR}/_ext/65885567/FSIO.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/1472/usb_config.o ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o ${OBJECTDIR}/_ext/713068069/usb_host.o ${OBJECTDIR}/_ext/65885567/FSIO.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d" -o ${OBJECTDIR}/_ext/1472/usb_config.o ../usb_config.c  
	
${OBJECTDIR}/_ext/1726182412/usb_host_msd.o: ../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1726182412 
	@${RM} ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o "../../Microchip/USB/MSD Host Driver/usb_host_msd.c"  
	
${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o: ../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1726182412 
	@${RM} ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o "../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"  
	
${OBJECTDIR}/_ext/713068069/usb_host.o: ../../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/713068069 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_host.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_host.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_host.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_host.o ../../Microchip/USB/usb_host.c  
	
${OBJECTDIR}/_ext/65885567/FSIO.o: ../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65885567 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/65885567/FSIO.o.d" -o ${OBJECTDIR}/_ext/65885567/FSIO.o "../../Microchip/MDD File System/FSIO.c"  
	
else
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1472/main.o.d" -o ${OBJECTDIR}/_ext/1472/main.o ../main.c  
	
${OBJECTDIR}/_ext/1472/usb_config.o: ../usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/usb_config.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/usb_config.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1472/usb_config.o.d" -o ${OBJECTDIR}/_ext/1472/usb_config.o ../usb_config.c  
	
${OBJECTDIR}/_ext/1726182412/usb_host_msd.o: ../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1726182412 
	@${RM} ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1726182412/usb_host_msd.o.d" -o ${OBJECTDIR}/_ext/1726182412/usb_host_msd.o "../../Microchip/USB/MSD Host Driver/usb_host_msd.c"  
	
${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o: ../../Microchip/USB/MSD\ Host\ Driver/usb_host_msd_scsi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1726182412 
	@${RM} ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o.d" -o ${OBJECTDIR}/_ext/1726182412/usb_host_msd_scsi.o "../../Microchip/USB/MSD Host Driver/usb_host_msd_scsi.c"  
	
${OBJECTDIR}/_ext/713068069/usb_host.o: ../../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/713068069 
	@${RM} ${OBJECTDIR}/_ext/713068069/usb_host.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/713068069/usb_host.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/713068069/usb_host.o.d" -o ${OBJECTDIR}/_ext/713068069/usb_host.o ../../Microchip/USB/usb_host.c  
	
${OBJECTDIR}/_ext/65885567/FSIO.o: ../../Microchip/MDD\ File\ System/FSIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/65885567 
	@${RM} ${OBJECTDIR}/_ext/65885567/FSIO.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/65885567/FSIO.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I".." -I"../../Microchip/Include" -I"../../Micros-Designs/Include" -I"C:/Proyectos C32/SkP32/Microchip/Include" -I"../../Microchip/Include/MDD File System" -I"../../Microchip/Include/USB" -MMD -MF "${OBJECTDIR}/_ext/65885567/FSIO.o.d" -o ${OBJECTDIR}/_ext/65885567/FSIO.o "../../Microchip/MDD File System/FSIO.c"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,-L"..",-Map="${DISTDIR}/USB-HOST.X.${IMAGE_TYPE}.map" 
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--defsym=_min_stack_size=1024,-L"..",-Map="${DISTDIR}/USB-HOST.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/USB-HOST.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
