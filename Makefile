# File:   Makefile
# Author: Yeni Choi, Mukhriz Khairudin
# Date:   14 October 2023
# Descr:  Makefile for funkit game(Dodgy Bird)

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/navswitch.h ../../fonts/font3x5_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../fonts/font5x7_1.h ../../drivers/ledmat.h ../../drivers/led.h ../../drivers/avr/ir_uart.h ../../drivers/avr/timer0.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h move.h start.h ball.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

move.o: ../../assignment/group_416/move.c ../../drivers/navswitch.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/ledmat.h ../../assignment/group_416/move.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/system.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/system.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

start.o: ../../assignment/group_416/start.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../utils/pacer.h ../../drivers/ledmat.h ../../assignment/group_416/move.h ../../assignment/group_416/start.h ../../utils/tinygl.h ../../drivers/navswitch.h ../../drivers/avr/usart1.h ../../fonts/font3x5_1.h ../../fonts/font5x7_1.h
	$(CC) -c $(CFLAGS) $< -o $@

ball.o: ../../assignment/group_416/ball.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h ../../drivers/avr/ir_uart.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h ../../assignment/group_416/start.h ../../assignment/group_416/ball.h 
	$(CC) -c $(CFLAGS) $< -o $@
	
# Link: create ELF output file from object files.
game.out: game.o pio.o system.o timer.o display.o navswitch.o ledmat.o font.o pacer.o tinygl.o led.o ir_uart.o usart1.o timer0.o prescale.o move.o start.o ball.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
