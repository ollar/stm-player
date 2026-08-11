# Makefile to compile and link code for STM32F411xE

# Compiler and options configuration
CC_SRC = ./xpacks/.bin/
CC = $(CC_SRC)arm-none-eabi-gcc
AS = $(CC_SRC)arm-none-eabi-as
GDB = $(CC_SRC)arm-none-eabi-gdb

CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
DEFS = -DUSE_HAL_DRIVER
DEFS += -DSTM32F411xE
DEFS += -DUSE_LVGL

# Include files
INCS = -I CMSIS/Device/Include \
			-I CMSIS/Core/Include \
			-I HAL/Include \
			-I Middlewares/LVGL \
			-I Middlewares/LVGL/include \
			-I Src/sd_card/FatFs \
			-I Src/sd_card/inc \
			-I Src/audio/inc \
			-I Inc

CFLAGS  = $(CPU) $(DEFS) $(INCS)
CFLAGS += -mthumb 
# CFLAGS += -g 
CFLAGS += -Os
# CFLAGS += -O0
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--no-warn-rwx-segments

ASFLAGS = $(CPU) -mthumb

# Linker flags
LDFLAGS  = -T Linker_script/linker_script.ld -static
LDFLAGS += -Wl,--gc-sections 
# LDFLAGS += -Wl,--print-gc-sections
LDFLAGS += -Wl,-Map=firmware.map
LDFLAGS += -specs=nano.specs -specs=nosys.specs

# Source files
SRCS = Src/main.c 
SRCS += CMSIS/Device/Source/system_stm32f4xx.c 
SRCS += HAL/Src/stm32f4xx_hal.c 
SRCS += HAL/Src/stm32f4xx_hal_gpio.c 
SRCS += HAL/Src/stm32f4xx_hal_rcc.c 
SRCS += HAL/Src/stm32f4xx_hal_rcc_ex.c 
SRCS += HAL/Src/stm32f4xx_hal_spi.c 
SRCS += HAL/Src/stm32f4xx_hal_usart.c 
SRCS += HAL/Src/stm32f4xx_hal_cortex.c 
SRCS += HAL/Src/stm32f4xx_hal_dma.c 
SRCS += HAL/Src/stm32f4xx_hal_dma_ex.c
SRCS += HAL/Src/stm32f4xx_hal_tim.c
SRCS += HAL/Src/stm32f4xx_hal_tim_ex.c
SRCS += HAL/Src/stm32f4xx_hal_i2s.c
SRCS += HAL/Src/stm32f4xx_hal_i2s_ex.c

SRCS += Src/stm32f4xx_it.c 
SRCS += Src/syscalls.c 
SRCS += Src/system.c 
SRCS += Src/usart_init.c 

SRCS += Src/oled_sh1107.c
SRCS += Src/lv_port_disp.c
SRCS += Src/fonts/ubuntu_mono_font.c

SRCS += Src/files_list.c
SRCS += Src/screens/main.c
SRCS += Src/screens/no_card.c

SRCS += Src/encoder.c
SRCS += Src/button.c

SRCS += Src/audio/i2s_init.c
SRCS += Src/audio/i2s_audio.c
SRCS += Src/audio/i2s_utils.c

SRCS += Src/sd_card/sd_spi.c 
SRCS += Src/sd_card/sd_functions.c

LVGL_C_SOURCES := $(shell find Middlewares/LVGL/src -name '*.c')
FatFs_C_SOURCES := $(shell find Src/sd_card/FatFs -name '*.c')

ASRCS = Startup/startup.s

OBJS = $(ASRCS:.s=.o) $(SRCS:.c=.o) $(LVGL_C_SOURCES:.c=.o) $(FatFs_C_SOURCES:.c=.o)

# Executable name
TARGET = blink.elf

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program blink.elf verify reset exit"

openocd-serve:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

gdb:
	$(GDB) $(TARGET)
	# (gdb) target extended-remote localhost:3333
	# (gdb) monitor reset halt
	# (gdb) load
	# (gdb) break main
	# (gdb) continue

ex-flash: clean all flash

compile-nvim-lsp:
	compiledb -n make
