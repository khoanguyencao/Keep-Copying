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
ifeq "$(wildcard nbproject/Makefile-local-FrameworkWith_u8g2.mk)" "nbproject/Makefile-local-FrameworkWith_u8g2.mk"
include nbproject/Makefile-local-FrameworkWith_u8g2.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=FrameworkWith_u8g2
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=FrameworkSource/ES_Port.c FrameworkSource/ES_Timers.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_Queue.c FrameworkSource/ES_PostList.c FrameworkSource/terminal.c ProjectSource/main.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/dbprintf.c u8g2/spi_master.c u8g2/u8g2_bitmap.c u8g2/u8g2_box.c u8g2/u8g2_buffer.c u8g2/u8g2_circle.c u8g2/u8g2_cleardisplay.c u8g2/u8g2_d_memory.c u8g2/u8g2_d_setup.c u8g2/u8g2_font.c u8g2/u8g2_fonts.c u8g2/u8g2_hvline.c u8g2/u8g2_input_value.c u8g2/u8g2_intersection.c u8g2/u8g2_kerning.c u8g2/u8g2_line.c u8g2/u8g2_ll_hvline.c u8g2/u8g2_message.c u8g2/u8g2_pic32mz.c u8g2/u8g2_polygon.c u8g2/u8g2_selection_list.c u8g2/u8g2_setup.c u8g2/u8log.c u8g2/u8log_u8g2.c u8g2/u8log_u8x8.c u8g2/u8x8_8x8.c u8g2/u8x8_byte.c u8g2/u8x8_cad.c u8g2/u8x8_d_ssd1306_128x64_noname.c u8g2/u8x8_debounce.c u8g2/u8x8_display.c u8g2/u8x8_fonts.c u8g2/u8x8_gpio.c u8g2/u8x8_input_value.c u8g2/u8x8_message.c u8g2/u8x8_selection_list.c u8g2/u8x8_setup.c u8g2/u8x8_string.c u8g2/u8x8_u16toa.c u8g2/u8x8_u8toa.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/dbprintf.o ${OBJECTDIR}/u8g2/spi_master.o ${OBJECTDIR}/u8g2/u8g2_bitmap.o ${OBJECTDIR}/u8g2/u8g2_box.o ${OBJECTDIR}/u8g2/u8g2_buffer.o ${OBJECTDIR}/u8g2/u8g2_circle.o ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o ${OBJECTDIR}/u8g2/u8g2_d_memory.o ${OBJECTDIR}/u8g2/u8g2_d_setup.o ${OBJECTDIR}/u8g2/u8g2_font.o ${OBJECTDIR}/u8g2/u8g2_fonts.o ${OBJECTDIR}/u8g2/u8g2_hvline.o ${OBJECTDIR}/u8g2/u8g2_input_value.o ${OBJECTDIR}/u8g2/u8g2_intersection.o ${OBJECTDIR}/u8g2/u8g2_kerning.o ${OBJECTDIR}/u8g2/u8g2_line.o ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o ${OBJECTDIR}/u8g2/u8g2_message.o ${OBJECTDIR}/u8g2/u8g2_pic32mz.o ${OBJECTDIR}/u8g2/u8g2_polygon.o ${OBJECTDIR}/u8g2/u8g2_selection_list.o ${OBJECTDIR}/u8g2/u8g2_setup.o ${OBJECTDIR}/u8g2/u8log.o ${OBJECTDIR}/u8g2/u8log_u8g2.o ${OBJECTDIR}/u8g2/u8log_u8x8.o ${OBJECTDIR}/u8g2/u8x8_8x8.o ${OBJECTDIR}/u8g2/u8x8_byte.o ${OBJECTDIR}/u8g2/u8x8_cad.o ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o ${OBJECTDIR}/u8g2/u8x8_debounce.o ${OBJECTDIR}/u8g2/u8x8_display.o ${OBJECTDIR}/u8g2/u8x8_fonts.o ${OBJECTDIR}/u8g2/u8x8_gpio.o ${OBJECTDIR}/u8g2/u8x8_input_value.o ${OBJECTDIR}/u8g2/u8x8_message.o ${OBJECTDIR}/u8g2/u8x8_selection_list.o ${OBJECTDIR}/u8g2/u8x8_setup.o ${OBJECTDIR}/u8g2/u8x8_string.o ${OBJECTDIR}/u8g2/u8x8_u16toa.o ${OBJECTDIR}/u8g2/u8x8_u8toa.o
POSSIBLE_DEPFILES=${OBJECTDIR}/FrameworkSource/ES_Port.o.d ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d ${OBJECTDIR}/FrameworkSource/terminal.o.d ${OBJECTDIR}/ProjectSource/main.o.d ${OBJECTDIR}/ProjectSource/EventCheckers.o.d ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d ${OBJECTDIR}/ProjectSource/dbprintf.o.d ${OBJECTDIR}/u8g2/spi_master.o.d ${OBJECTDIR}/u8g2/u8g2_bitmap.o.d ${OBJECTDIR}/u8g2/u8g2_box.o.d ${OBJECTDIR}/u8g2/u8g2_buffer.o.d ${OBJECTDIR}/u8g2/u8g2_circle.o.d ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d ${OBJECTDIR}/u8g2/u8g2_d_memory.o.d ${OBJECTDIR}/u8g2/u8g2_d_setup.o.d ${OBJECTDIR}/u8g2/u8g2_font.o.d ${OBJECTDIR}/u8g2/u8g2_fonts.o.d ${OBJECTDIR}/u8g2/u8g2_hvline.o.d ${OBJECTDIR}/u8g2/u8g2_input_value.o.d ${OBJECTDIR}/u8g2/u8g2_intersection.o.d ${OBJECTDIR}/u8g2/u8g2_kerning.o.d ${OBJECTDIR}/u8g2/u8g2_line.o.d ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d ${OBJECTDIR}/u8g2/u8g2_message.o.d ${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d ${OBJECTDIR}/u8g2/u8g2_polygon.o.d ${OBJECTDIR}/u8g2/u8g2_selection_list.o.d ${OBJECTDIR}/u8g2/u8g2_setup.o.d ${OBJECTDIR}/u8g2/u8log.o.d ${OBJECTDIR}/u8g2/u8log_u8g2.o.d ${OBJECTDIR}/u8g2/u8log_u8x8.o.d ${OBJECTDIR}/u8g2/u8x8_8x8.o.d ${OBJECTDIR}/u8g2/u8x8_byte.o.d ${OBJECTDIR}/u8g2/u8x8_cad.o.d ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d ${OBJECTDIR}/u8g2/u8x8_debounce.o.d ${OBJECTDIR}/u8g2/u8x8_display.o.d ${OBJECTDIR}/u8g2/u8x8_fonts.o.d ${OBJECTDIR}/u8g2/u8x8_gpio.o.d ${OBJECTDIR}/u8g2/u8x8_input_value.o.d ${OBJECTDIR}/u8g2/u8x8_message.o.d ${OBJECTDIR}/u8g2/u8x8_selection_list.o.d ${OBJECTDIR}/u8g2/u8x8_setup.o.d ${OBJECTDIR}/u8g2/u8x8_string.o.d ${OBJECTDIR}/u8g2/u8x8_u16toa.o.d ${OBJECTDIR}/u8g2/u8x8_u8toa.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/FrameworkSource/ES_Port.o ${OBJECTDIR}/FrameworkSource/ES_Timers.o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o ${OBJECTDIR}/FrameworkSource/ES_Framework.o ${OBJECTDIR}/FrameworkSource/ES_Queue.o ${OBJECTDIR}/FrameworkSource/ES_PostList.o ${OBJECTDIR}/FrameworkSource/terminal.o ${OBJECTDIR}/ProjectSource/main.o ${OBJECTDIR}/ProjectSource/EventCheckers.o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ${OBJECTDIR}/ProjectSource/dbprintf.o ${OBJECTDIR}/u8g2/spi_master.o ${OBJECTDIR}/u8g2/u8g2_bitmap.o ${OBJECTDIR}/u8g2/u8g2_box.o ${OBJECTDIR}/u8g2/u8g2_buffer.o ${OBJECTDIR}/u8g2/u8g2_circle.o ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o ${OBJECTDIR}/u8g2/u8g2_d_memory.o ${OBJECTDIR}/u8g2/u8g2_d_setup.o ${OBJECTDIR}/u8g2/u8g2_font.o ${OBJECTDIR}/u8g2/u8g2_fonts.o ${OBJECTDIR}/u8g2/u8g2_hvline.o ${OBJECTDIR}/u8g2/u8g2_input_value.o ${OBJECTDIR}/u8g2/u8g2_intersection.o ${OBJECTDIR}/u8g2/u8g2_kerning.o ${OBJECTDIR}/u8g2/u8g2_line.o ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o ${OBJECTDIR}/u8g2/u8g2_message.o ${OBJECTDIR}/u8g2/u8g2_pic32mz.o ${OBJECTDIR}/u8g2/u8g2_polygon.o ${OBJECTDIR}/u8g2/u8g2_selection_list.o ${OBJECTDIR}/u8g2/u8g2_setup.o ${OBJECTDIR}/u8g2/u8log.o ${OBJECTDIR}/u8g2/u8log_u8g2.o ${OBJECTDIR}/u8g2/u8log_u8x8.o ${OBJECTDIR}/u8g2/u8x8_8x8.o ${OBJECTDIR}/u8g2/u8x8_byte.o ${OBJECTDIR}/u8g2/u8x8_cad.o ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o ${OBJECTDIR}/u8g2/u8x8_debounce.o ${OBJECTDIR}/u8g2/u8x8_display.o ${OBJECTDIR}/u8g2/u8x8_fonts.o ${OBJECTDIR}/u8g2/u8x8_gpio.o ${OBJECTDIR}/u8g2/u8x8_input_value.o ${OBJECTDIR}/u8g2/u8x8_message.o ${OBJECTDIR}/u8g2/u8x8_selection_list.o ${OBJECTDIR}/u8g2/u8x8_setup.o ${OBJECTDIR}/u8g2/u8x8_string.o ${OBJECTDIR}/u8g2/u8x8_u16toa.o ${OBJECTDIR}/u8g2/u8x8_u8toa.o

# Source Files
SOURCEFILES=FrameworkSource/ES_Port.c FrameworkSource/ES_Timers.c FrameworkSource/ES_LookupTables.c FrameworkSource/ES_CheckEvents.c FrameworkSource/ES_DeferRecall.c FrameworkSource/ES_Framework.c FrameworkSource/ES_Queue.c FrameworkSource/ES_PostList.c FrameworkSource/terminal.c ProjectSource/main.c ProjectSource/EventCheckers.c ProjectSource/TestHarnessService0.c ProjectSource/dbprintf.c u8g2/spi_master.c u8g2/u8g2_bitmap.c u8g2/u8g2_box.c u8g2/u8g2_buffer.c u8g2/u8g2_circle.c u8g2/u8g2_cleardisplay.c u8g2/u8g2_d_memory.c u8g2/u8g2_d_setup.c u8g2/u8g2_font.c u8g2/u8g2_fonts.c u8g2/u8g2_hvline.c u8g2/u8g2_input_value.c u8g2/u8g2_intersection.c u8g2/u8g2_kerning.c u8g2/u8g2_line.c u8g2/u8g2_ll_hvline.c u8g2/u8g2_message.c u8g2/u8g2_pic32mz.c u8g2/u8g2_polygon.c u8g2/u8g2_selection_list.c u8g2/u8g2_setup.c u8g2/u8log.c u8g2/u8log_u8g2.c u8g2/u8log_u8x8.c u8g2/u8x8_8x8.c u8g2/u8x8_byte.c u8g2/u8x8_cad.c u8g2/u8x8_d_ssd1306_128x64_noname.c u8g2/u8x8_debounce.c u8g2/u8x8_display.c u8g2/u8x8_fonts.c u8g2/u8x8_gpio.c u8g2/u8x8_input_value.c u8g2/u8x8_message.c u8g2/u8x8_selection_list.c u8g2/u8x8_setup.c u8g2/u8x8_string.c u8g2/u8x8_u16toa.c u8g2/u8x8_u8toa.c



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-FrameworkWith_u8g2.mk dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX170F256B
MP_LINKER_FILE_OPTION=
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
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/terminal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/dbprintf.o: ProjectSource/dbprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/dbprintf.o.d" -o ${OBJECTDIR}/ProjectSource/dbprintf.o ProjectSource/dbprintf.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/dbprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/spi_master.o: u8g2/spi_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/spi_master.o.d 
	@${RM} ${OBJECTDIR}/u8g2/spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/spi_master.o.d" -o ${OBJECTDIR}/u8g2/spi_master.o u8g2/spi_master.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/spi_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_bitmap.o: u8g2/u8g2_bitmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_bitmap.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_bitmap.o.d" -o ${OBJECTDIR}/u8g2/u8g2_bitmap.o u8g2/u8g2_bitmap.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_bitmap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_box.o: u8g2/u8g2_box.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_box.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_box.o.d" -o ${OBJECTDIR}/u8g2/u8g2_box.o u8g2/u8g2_box.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_box.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_buffer.o: u8g2/u8g2_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_buffer.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_buffer.o.d" -o ${OBJECTDIR}/u8g2/u8g2_buffer.o u8g2/u8g2_buffer.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_circle.o: u8g2/u8g2_circle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_circle.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_circle.o.d" -o ${OBJECTDIR}/u8g2/u8g2_circle.o u8g2/u8g2_circle.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_cleardisplay.o: u8g2/u8g2_cleardisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d" -o ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o u8g2/u8g2_cleardisplay.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_d_memory.o: u8g2/u8g2_d_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_memory.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_memory.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_d_memory.o.d" -o ${OBJECTDIR}/u8g2/u8g2_d_memory.o u8g2/u8g2_d_memory.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_d_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_d_setup.o: u8g2/u8g2_d_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_d_setup.o.d" -o ${OBJECTDIR}/u8g2/u8g2_d_setup.o u8g2/u8g2_d_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_d_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_font.o: u8g2/u8g2_font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_font.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_font.o.d" -o ${OBJECTDIR}/u8g2/u8g2_font.o u8g2/u8g2_font.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_font.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_fonts.o: u8g2/u8g2_fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_fonts.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_fonts.o.d" -o ${OBJECTDIR}/u8g2/u8g2_fonts.o u8g2/u8g2_fonts.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_hvline.o: u8g2/u8g2_hvline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_hvline.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_hvline.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_hvline.o.d" -o ${OBJECTDIR}/u8g2/u8g2_hvline.o u8g2/u8g2_hvline.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_hvline.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_input_value.o: u8g2/u8g2_input_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_input_value.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_input_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_input_value.o.d" -o ${OBJECTDIR}/u8g2/u8g2_input_value.o u8g2/u8g2_input_value.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_input_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_intersection.o: u8g2/u8g2_intersection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_intersection.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_intersection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_intersection.o.d" -o ${OBJECTDIR}/u8g2/u8g2_intersection.o u8g2/u8g2_intersection.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_intersection.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_kerning.o: u8g2/u8g2_kerning.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_kerning.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_kerning.o.d" -o ${OBJECTDIR}/u8g2/u8g2_kerning.o u8g2/u8g2_kerning.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_kerning.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_line.o: u8g2/u8g2_line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_line.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_line.o.d" -o ${OBJECTDIR}/u8g2/u8g2_line.o u8g2/u8g2_line.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_ll_hvline.o: u8g2/u8g2_ll_hvline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d" -o ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o u8g2/u8g2_ll_hvline.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_message.o: u8g2/u8g2_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_message.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_message.o.d" -o ${OBJECTDIR}/u8g2/u8g2_message.o u8g2/u8g2_message.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_pic32mz.o: u8g2/u8g2_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d" -o ${OBJECTDIR}/u8g2/u8g2_pic32mz.o u8g2/u8g2_pic32mz.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_polygon.o: u8g2/u8g2_polygon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_polygon.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_polygon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_polygon.o.d" -o ${OBJECTDIR}/u8g2/u8g2_polygon.o u8g2/u8g2_polygon.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_polygon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_selection_list.o: u8g2/u8g2_selection_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_selection_list.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_selection_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_selection_list.o.d" -o ${OBJECTDIR}/u8g2/u8g2_selection_list.o u8g2/u8g2_selection_list.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_selection_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_setup.o: u8g2/u8g2_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_setup.o.d" -o ${OBJECTDIR}/u8g2/u8g2_setup.o u8g2/u8g2_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log.o: u8g2/u8log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log.o.d" -o ${OBJECTDIR}/u8g2/u8log.o u8g2/u8log.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log_u8g2.o: u8g2/u8log_u8g2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8g2.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8g2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log_u8g2.o.d" -o ${OBJECTDIR}/u8g2/u8log_u8g2.o u8g2/u8log_u8g2.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log_u8g2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log_u8x8.o: u8g2/u8log_u8x8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8x8.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8x8.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log_u8x8.o.d" -o ${OBJECTDIR}/u8g2/u8log_u8x8.o u8g2/u8log_u8x8.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log_u8x8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_8x8.o: u8g2/u8x8_8x8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_8x8.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_8x8.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_8x8.o.d" -o ${OBJECTDIR}/u8g2/u8x8_8x8.o u8g2/u8x8_8x8.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_8x8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_byte.o: u8g2/u8x8_byte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_byte.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_byte.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_byte.o.d" -o ${OBJECTDIR}/u8g2/u8x8_byte.o u8g2/u8x8_byte.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_byte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_cad.o: u8g2/u8x8_cad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_cad.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_cad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_cad.o.d" -o ${OBJECTDIR}/u8g2/u8x8_cad.o u8g2/u8x8_cad.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_cad.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o: u8g2/u8x8_d_ssd1306_128x64_noname.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d" -o ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o u8g2/u8x8_d_ssd1306_128x64_noname.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_debounce.o: u8g2/u8x8_debounce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_debounce.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_debounce.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_debounce.o.d" -o ${OBJECTDIR}/u8g2/u8x8_debounce.o u8g2/u8x8_debounce.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_debounce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_display.o: u8g2/u8x8_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_display.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_display.o.d" -o ${OBJECTDIR}/u8g2/u8x8_display.o u8g2/u8x8_display.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_fonts.o: u8g2/u8x8_fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_fonts.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_fonts.o.d" -o ${OBJECTDIR}/u8g2/u8x8_fonts.o u8g2/u8x8_fonts.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_gpio.o: u8g2/u8x8_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_gpio.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_gpio.o.d" -o ${OBJECTDIR}/u8g2/u8x8_gpio.o u8g2/u8x8_gpio.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_input_value.o: u8g2/u8x8_input_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_input_value.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_input_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_input_value.o.d" -o ${OBJECTDIR}/u8g2/u8x8_input_value.o u8g2/u8x8_input_value.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_input_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_message.o: u8g2/u8x8_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_message.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_message.o.d" -o ${OBJECTDIR}/u8g2/u8x8_message.o u8g2/u8x8_message.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_selection_list.o: u8g2/u8x8_selection_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_selection_list.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_selection_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_selection_list.o.d" -o ${OBJECTDIR}/u8g2/u8x8_selection_list.o u8g2/u8x8_selection_list.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_selection_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_setup.o: u8g2/u8x8_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_setup.o.d" -o ${OBJECTDIR}/u8g2/u8x8_setup.o u8g2/u8x8_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_string.o: u8g2/u8x8_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_string.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_string.o.d" -o ${OBJECTDIR}/u8g2/u8x8_string.o u8g2/u8x8_string.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_string.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_u16toa.o: u8g2/u8x8_u16toa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u16toa.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u16toa.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_u16toa.o.d" -o ${OBJECTDIR}/u8g2/u8x8_u16toa.o u8g2/u8x8_u16toa.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_u16toa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_u8toa.o: u8g2/u8x8_u8toa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u8toa.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u8toa.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_u8toa.o.d" -o ${OBJECTDIR}/u8g2/u8x8_u8toa.o u8g2/u8x8_u8toa.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_u8toa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/FrameworkSource/ES_Port.o: FrameworkSource/ES_Port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Port.o FrameworkSource/ES_Port.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Timers.o: FrameworkSource/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Timers.o FrameworkSource/ES_Timers.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_LookupTables.o: FrameworkSource/ES_LookupTables.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_LookupTables.o FrameworkSource/ES_LookupTables.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_LookupTables.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o: FrameworkSource/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o FrameworkSource/ES_CheckEvents.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o: FrameworkSource/ES_DeferRecall.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o FrameworkSource/ES_DeferRecall.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_DeferRecall.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Framework.o: FrameworkSource/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Framework.o FrameworkSource/ES_Framework.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_Queue.o: FrameworkSource/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_Queue.o FrameworkSource/ES_Queue.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/ES_PostList.o: FrameworkSource/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" -o ${OBJECTDIR}/FrameworkSource/ES_PostList.o FrameworkSource/ES_PostList.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/FrameworkSource/terminal.o: FrameworkSource/terminal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/FrameworkSource" 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o.d 
	@${RM} ${OBJECTDIR}/FrameworkSource/terminal.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/FrameworkSource/terminal.o.d" -o ${OBJECTDIR}/FrameworkSource/terminal.o FrameworkSource/terminal.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/FrameworkSource/terminal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/main.o: ProjectSource/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/main.o.d" -o ${OBJECTDIR}/ProjectSource/main.o ProjectSource/main.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/EventCheckers.o: ProjectSource/EventCheckers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" -o ${OBJECTDIR}/ProjectSource/EventCheckers.o ProjectSource/EventCheckers.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/EventCheckers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/TestHarnessService0.o: ProjectSource/TestHarnessService0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/TestHarnessService0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" -o ${OBJECTDIR}/ProjectSource/TestHarnessService0.o ProjectSource/TestHarnessService0.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/TestHarnessService0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/ProjectSource/dbprintf.o: ProjectSource/dbprintf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ProjectSource" 
	@${RM} ${OBJECTDIR}/ProjectSource/dbprintf.o.d 
	@${RM} ${OBJECTDIR}/ProjectSource/dbprintf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/ProjectSource/dbprintf.o.d" -o ${OBJECTDIR}/ProjectSource/dbprintf.o ProjectSource/dbprintf.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/ProjectSource/dbprintf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/spi_master.o: u8g2/spi_master.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/spi_master.o.d 
	@${RM} ${OBJECTDIR}/u8g2/spi_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/spi_master.o.d" -o ${OBJECTDIR}/u8g2/spi_master.o u8g2/spi_master.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/spi_master.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_bitmap.o: u8g2/u8g2_bitmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_bitmap.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_bitmap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_bitmap.o.d" -o ${OBJECTDIR}/u8g2/u8g2_bitmap.o u8g2/u8g2_bitmap.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_bitmap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_box.o: u8g2/u8g2_box.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_box.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_box.o.d" -o ${OBJECTDIR}/u8g2/u8g2_box.o u8g2/u8g2_box.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_box.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_buffer.o: u8g2/u8g2_buffer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_buffer.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_buffer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_buffer.o.d" -o ${OBJECTDIR}/u8g2/u8g2_buffer.o u8g2/u8g2_buffer.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_circle.o: u8g2/u8g2_circle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_circle.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_circle.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_circle.o.d" -o ${OBJECTDIR}/u8g2/u8g2_circle.o u8g2/u8g2_circle.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_circle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_cleardisplay.o: u8g2/u8g2_cleardisplay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d" -o ${OBJECTDIR}/u8g2/u8g2_cleardisplay.o u8g2/u8g2_cleardisplay.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_cleardisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_d_memory.o: u8g2/u8g2_d_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_memory.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_memory.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_d_memory.o.d" -o ${OBJECTDIR}/u8g2/u8g2_d_memory.o u8g2/u8g2_d_memory.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_d_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_d_setup.o: u8g2/u8g2_d_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_d_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_d_setup.o.d" -o ${OBJECTDIR}/u8g2/u8g2_d_setup.o u8g2/u8g2_d_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_d_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_font.o: u8g2/u8g2_font.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_font.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_font.o.d" -o ${OBJECTDIR}/u8g2/u8g2_font.o u8g2/u8g2_font.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_font.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_fonts.o: u8g2/u8g2_fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_fonts.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_fonts.o.d" -o ${OBJECTDIR}/u8g2/u8g2_fonts.o u8g2/u8g2_fonts.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_hvline.o: u8g2/u8g2_hvline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_hvline.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_hvline.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_hvline.o.d" -o ${OBJECTDIR}/u8g2/u8g2_hvline.o u8g2/u8g2_hvline.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_hvline.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_input_value.o: u8g2/u8g2_input_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_input_value.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_input_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_input_value.o.d" -o ${OBJECTDIR}/u8g2/u8g2_input_value.o u8g2/u8g2_input_value.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_input_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_intersection.o: u8g2/u8g2_intersection.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_intersection.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_intersection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_intersection.o.d" -o ${OBJECTDIR}/u8g2/u8g2_intersection.o u8g2/u8g2_intersection.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_intersection.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_kerning.o: u8g2/u8g2_kerning.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_kerning.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_kerning.o.d" -o ${OBJECTDIR}/u8g2/u8g2_kerning.o u8g2/u8g2_kerning.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_kerning.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_line.o: u8g2/u8g2_line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_line.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_line.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_line.o.d" -o ${OBJECTDIR}/u8g2/u8g2_line.o u8g2/u8g2_line.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_ll_hvline.o: u8g2/u8g2_ll_hvline.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d" -o ${OBJECTDIR}/u8g2/u8g2_ll_hvline.o u8g2/u8g2_ll_hvline.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_ll_hvline.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_message.o: u8g2/u8g2_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_message.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_message.o.d" -o ${OBJECTDIR}/u8g2/u8g2_message.o u8g2/u8g2_message.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_pic32mz.o: u8g2/u8g2_pic32mz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d" -o ${OBJECTDIR}/u8g2/u8g2_pic32mz.o u8g2/u8g2_pic32mz.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_pic32mz.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_polygon.o: u8g2/u8g2_polygon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_polygon.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_polygon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_polygon.o.d" -o ${OBJECTDIR}/u8g2/u8g2_polygon.o u8g2/u8g2_polygon.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_polygon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_selection_list.o: u8g2/u8g2_selection_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_selection_list.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_selection_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_selection_list.o.d" -o ${OBJECTDIR}/u8g2/u8g2_selection_list.o u8g2/u8g2_selection_list.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_selection_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8g2_setup.o: u8g2/u8g2_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8g2_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8g2_setup.o.d" -o ${OBJECTDIR}/u8g2/u8g2_setup.o u8g2/u8g2_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8g2_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log.o: u8g2/u8log.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log.o.d" -o ${OBJECTDIR}/u8g2/u8log.o u8g2/u8log.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log_u8g2.o: u8g2/u8log_u8g2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8g2.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8g2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log_u8g2.o.d" -o ${OBJECTDIR}/u8g2/u8log_u8g2.o u8g2/u8log_u8g2.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log_u8g2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8log_u8x8.o: u8g2/u8log_u8x8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8x8.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8log_u8x8.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8log_u8x8.o.d" -o ${OBJECTDIR}/u8g2/u8log_u8x8.o u8g2/u8log_u8x8.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8log_u8x8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_8x8.o: u8g2/u8x8_8x8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_8x8.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_8x8.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_8x8.o.d" -o ${OBJECTDIR}/u8g2/u8x8_8x8.o u8g2/u8x8_8x8.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_8x8.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_byte.o: u8g2/u8x8_byte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_byte.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_byte.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_byte.o.d" -o ${OBJECTDIR}/u8g2/u8x8_byte.o u8g2/u8x8_byte.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_byte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_cad.o: u8g2/u8x8_cad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_cad.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_cad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_cad.o.d" -o ${OBJECTDIR}/u8g2/u8x8_cad.o u8g2/u8x8_cad.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_cad.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o: u8g2/u8x8_d_ssd1306_128x64_noname.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d" -o ${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o u8g2/u8x8_d_ssd1306_128x64_noname.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_d_ssd1306_128x64_noname.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_debounce.o: u8g2/u8x8_debounce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_debounce.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_debounce.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_debounce.o.d" -o ${OBJECTDIR}/u8g2/u8x8_debounce.o u8g2/u8x8_debounce.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_debounce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_display.o: u8g2/u8x8_display.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_display.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_display.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_display.o.d" -o ${OBJECTDIR}/u8g2/u8x8_display.o u8g2/u8x8_display.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_display.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_fonts.o: u8g2/u8x8_fonts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_fonts.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_fonts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_fonts.o.d" -o ${OBJECTDIR}/u8g2/u8x8_fonts.o u8g2/u8x8_fonts.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_fonts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_gpio.o: u8g2/u8x8_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_gpio.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_gpio.o.d" -o ${OBJECTDIR}/u8g2/u8x8_gpio.o u8g2/u8x8_gpio.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_input_value.o: u8g2/u8x8_input_value.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_input_value.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_input_value.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_input_value.o.d" -o ${OBJECTDIR}/u8g2/u8x8_input_value.o u8g2/u8x8_input_value.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_input_value.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_message.o: u8g2/u8x8_message.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_message.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_message.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_message.o.d" -o ${OBJECTDIR}/u8g2/u8x8_message.o u8g2/u8x8_message.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_message.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_selection_list.o: u8g2/u8x8_selection_list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_selection_list.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_selection_list.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_selection_list.o.d" -o ${OBJECTDIR}/u8g2/u8x8_selection_list.o u8g2/u8x8_selection_list.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_selection_list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_setup.o: u8g2/u8x8_setup.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_setup.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_setup.o.d" -o ${OBJECTDIR}/u8g2/u8x8_setup.o u8g2/u8x8_setup.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_setup.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_string.o: u8g2/u8x8_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_string.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_string.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_string.o.d" -o ${OBJECTDIR}/u8g2/u8x8_string.o u8g2/u8x8_string.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_string.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_u16toa.o: u8g2/u8x8_u16toa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u16toa.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u16toa.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_u16toa.o.d" -o ${OBJECTDIR}/u8g2/u8x8_u16toa.o u8g2/u8x8_u16toa.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_u16toa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/u8g2/u8x8_u8toa.o: u8g2/u8x8_u8toa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/u8g2" 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u8toa.o.d 
	@${RM} ${OBJECTDIR}/u8g2/u8x8_u8toa.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"FrameworkHeaders" -I"ProjectHeaders" -I"u8g2Headers" -MMD -MF "${OBJECTDIR}/u8g2/u8x8_u8toa.o.d" -o ${OBJECTDIR}/u8g2/u8x8_u8toa.o u8g2/u8x8_u8toa.c    -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -std=gnu99 -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/u8g2/u8x8_u8toa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_FrameworkWith_u8g2=$(CND_CONF)  -legacy-libc  -std=gnu99 $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Framework4PIC32_with_u8g2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/FrameworkWith_u8g2
	${RM} -r dist/FrameworkWith_u8g2

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
