################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 2
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Lib_Sources/_hcs08/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIBRARY += \
MC_Library.lib \

LIBRARY_QUOTED += \
"MC_Library.lib" \

LIBRARY_OS_FORMAT += \
MC_Library.lib \


# All Target
all: warning-messages explicit-dependencies MC_Library.lib

# Tool invocations
MC_Library.lib: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #3 $@'
	@echo 'Invoking: S08 Libmaker'
	"$(HC08ToolsEnv)/libmaker" -ArgFile"MC_Library.args"  -cmd( $(OBJS_QUOTED) $(USER_OBJS_QUOTED) $(LIBS_QUOTED) = "MC_Library.lib")
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*/*.obj"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(S_UPPER_DEPS_QUOTED) $(LIBRARY_QUOTED) $(CXX_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) "./*/*/*.d"  $(ProjDirPath)/Debug/MC_Library.lib $(ProjDirPath)/Debug/MC_Library.args $(ProjDirPath)/Debug/MC_Library.lib $(ProjDirPath)/Debug/MC_Library.lst
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

