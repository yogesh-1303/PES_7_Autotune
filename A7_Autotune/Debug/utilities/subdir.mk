################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\board" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\source" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\drivers" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\CMSIS" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\utilities" -I"C:\CU_Files\MCUXpressoIDE_11.2.1_4149\workspace\A7_Autotune\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


