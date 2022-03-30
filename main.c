// Standard Library Includes
#include <stdio.h>
#include <stdlib.h>

// Target Includes
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

// Project Includes
#include "ws2812.pio.h"

// Constants
#define PIN_DEBUG_UART_TX     0
#define PIN_DEBUG_UART_RX     1
#define PIN_LED_WS2812        2
#define PIN_MIDI_UART_TX      4
#define PIN_MIDI_UART_RX      5

// ---------------------------------------------------------------------------------
// WS2812 Smart LED Utilities
// ---------------------------------------------------------------------------------
// Source:  Pi Pico WS2812 PIO example code
//          https://github.com/raspberrypi/pico-examples/blob/master/pio/ws2812/ws2812.c
// ---------------------------------------------------------------------------------
// License: BSD 3 Clause
// ---------------------------------------------------------------------------------

// Initialize the PIO program for talking to WS2812 LEDs
void ws2812_init(uint8_t pin)
{
    PIO pio = pio0;
    uint sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &ws2812_program);

    pio_sm_set_enabled(pio, sm, true);
    ws2812_program_init(pio, sm, offset, pin, 800000, false);
}

// Set the pixel color of a WS2812
void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

// Convert red, green and blue values into a uint32 value
uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

// ---------------------------------------------------------------------------------
// MIDI Interface Board Test Program
// ---------------------------------------------------------------------------------
// Source: Copyright 2022 David Slik. Own work.
// ---------------------------------------------------------------------------------
// License: BSD 3 Clause
// ---------------------------------------------------------------------------------
int main()
{
    stdio_init_all();

    // Initialize the UART for debug ouput
    uart_init(uart0, 115200);
    gpio_set_function(PIN_DEBUG_UART_TX, GPIO_FUNC_UART);
    gpio_set_function(PIN_DEBUG_UART_RX, GPIO_FUNC_UART);

    // Initialize the intelligent LEDs
    ws2812_init(PIN_LED_WS2812);

    printf("--------------------------------------------------------\n");
    printf("Starting MIDI interface board test...\n");
    printf("TEST1: RGB LEDs should turn Red, Green then Blue.\n");

    put_pixel(0x0000FF00);
    put_pixel(0x0000FF00);
    put_pixel(0x0000FF00);
    put_pixel(0x0000FF00);
    sleep_ms(2000);
    put_pixel(0x00FF0000);
    put_pixel(0x00FF0000);
    put_pixel(0x00FF0000);
    put_pixel(0x00FF0000);
    sleep_ms(2000);
    put_pixel(0x000000FF);
    put_pixel(0x000000FF);
    put_pixel(0x000000FF);
    put_pixel(0x000000FF);
    sleep_ms(2000);
    put_pixel(0x00000000);
    put_pixel(0x00000000);
    put_pixel(0x00000000);
    put_pixel(0x00000000);

    printf("TEST2: Play MIDI Notes\n");
    sleep_ms(2000);

    uart_init(uart1, 31250);
    gpio_set_function(PIN_MIDI_UART_TX, GPIO_FUNC_UART);
    gpio_set_function(PIN_MIDI_UART_RX, GPIO_FUNC_UART);

    sleep_ms(500);

    uart_putc(uart1, 0x90);
    uart_putc(uart1, 0x3C);
    uart_putc(uart1, 0x7F);

    sleep_ms(500);

    uart_putc(uart1, 0x80);
    uart_putc(uart1, 0x3C);
    uart_putc(uart1, 0x00);

    sleep_ms(2000);

    printf("TEST3: Waiting for MIDI Notes\n");

    uint8_t character;

    while(true)
    {
        character = uart_getc(uart1);
        printf("Received Midi Data: %X\n", character);
    }

    // Do nothing
    while (true) {
        sleep_ms(1000);

        put_pixel(rand());
        put_pixel(rand());
        put_pixel(rand());
        put_pixel(rand());
    }
}