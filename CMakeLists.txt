cmake_minimum_required(VERSION 3.20)
project(KormilitsynaTestTask C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(MCU "STM32F405VGT6")
set(CMSIS_MCU "STM32F405Vx")

add_compile_options(-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_compile_options(-O2 -g -Wall -Wextra)
add_compile_options(-ffunction-sections -fdata-sections -fno-exceptions)
add_compile_options(-DSTM32F405xx)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F405VGTx_FLASH.ld)

if(NOT EXISTS ${LINKER_SCRIPT})
    message(WARNING "Linker script not found: ${LINKER_SCRIPT}")
    message(WARNING "Expected one of: STM32F405VGTx_FLASH.ld, STM32F405VG_FLASH.ld")
endif()

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_NAME}.map)
add_link_options(-nostdlib -nostartfiles)
add_link_options(-Wl,--undefined=Reset_Handler)
add_link_options(-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-T ${LINKER_SCRIPT})

set(CORE_DIR "Core")
set(DRIVERS_DIR "Drivers")
set(MIDDLEWARES_DIR "Middlewares/Third_Party")
set(FREERTOS_DIR "${MIDDLEWARES_DIR}/FreeRTOS")

list(APPEND SOURCES
    "${CORE_DIR}/Startup/startup_stm32f405vgtx.s"
	"${CORE_DIR}/Src/empty_init.c"
    "${CORE_DIR}/Src/main.c"
    "${CORE_DIR}/Src/system_stm32f4xx.c"
    "${CORE_DIR}/Src/syscalls.c"
    "${CORE_DIR}/Src/sysmem.c"
	"${CORE_DIR}/Src/globals.c"
	"${CORE_DIR}/Src/adcDataProcessing.c"
	"${CORE_DIR}/Src/canDataProcessing.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c"
	"${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c"
    "${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c"
	"${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c"
	"${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c"
    "${CORE_DIR}/Src/stm32f4xx_it.c"
    "${CORE_DIR}/Src/stm32f4xx_hal_msp.c"
    "${CORE_DIR}/Src/stm32f4xx_hal_timebase_tim.c"
)

list(APPEND SOURCES
    "${FREERTOS_DIR}/Source/croutine.c"
    "${FREERTOS_DIR}/Source/event_groups.c"
    "${FREERTOS_DIR}/Source/list.c"
    "${FREERTOS_DIR}/Source/queue.c"
    "${FREERTOS_DIR}/Source/stream_buffer.c"
    "${FREERTOS_DIR}/Source/tasks.c"
    "${FREERTOS_DIR}/Source/timers.c"
	"${FREERTOS_DIR}/Source/CMSIS_RTOS_V2/cmsis_os2.c"
    "${FREERTOS_DIR}/Source/portable/GCC/ARM_CM4F/port.c"
    "${FREERTOS_DIR}/Source/portable/MemMang/heap_4.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CORE_DIR}/Inc
    ${DRIVERS_DIR}/CMSIS/Include
    ${DRIVERS_DIR}/CMSIS/Device/ST/STM32F4xx/Include
    ${DRIVERS_DIR}/STM32F4xx_HAL_Driver/Inc
    ${FREERTOS_DIR}/Source/include
	${FREERTOS_DIR}/Source/CMSIS_RTOS_V2
    ${FREERTOS_DIR}/Source/portable/GCC/ARM_CM4F
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    STM32F405xx
    USE_FULL_LL_DRIVER
    HAL_INIT_TICK_NOT_USED=1
)

set(FREERTOS_CONFIG_H "${CORE_DIR}/Inc/FreeRTOSConfig.h")
if(EXISTS ${FREERTOS_CONFIG_H})
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:C>:__FREERTOS__>
    )
endif()