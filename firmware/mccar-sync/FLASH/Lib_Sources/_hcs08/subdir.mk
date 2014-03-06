################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"$(_HCS08)/mc9s08jm60.c" \
"$(_HCS08)/start08.c" \

C_SRCS += \
$(_HCS08)/mc9s08jm60.c \
$(_HCS08)/start08.c \

OBJS += \
./Lib_Sources/_hcs08/mc9s08jm60_c.obj \
./Lib_Sources/_hcs08/start08_c.obj \

OBJS_QUOTED += \
"./Lib_Sources/_hcs08/mc9s08jm60_c.obj" \
"./Lib_Sources/_hcs08/start08_c.obj" \

C_DEPS += \
./Lib_Sources/_hcs08/mc9s08jm60_c.d \
./Lib_Sources/_hcs08/start08_c.d \

C_DEPS_QUOTED += \
"./Lib_Sources/_hcs08/mc9s08jm60_c.d" \
"./Lib_Sources/_hcs08/start08_c.d" \

OBJS_OS_FORMAT += \
./Lib_Sources/_hcs08/mc9s08jm60_c.obj \
./Lib_Sources/_hcs08/start08_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Lib_Sources/_hcs08/mc9s08jm60_c.obj: $(_HCS08)/mc9s08jm60.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Lib_Sources/_hcs08/mc9s08jm60.args" -ObjN="Lib_Sources/_hcs08/mc9s08jm60_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Lib_Sources/_hcs08/mc9s08jm60_c.d: $(_HCS08)/mc9s08jm60.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Lib_Sources/_hcs08/start08_c.obj: $(_HCS08)/start08.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Lib_Sources/_hcs08/start08.args" -ObjN="Lib_Sources/_hcs08/start08_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Lib_Sources/_hcs08/start08_c.d: $(_HCS08)/start08.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


