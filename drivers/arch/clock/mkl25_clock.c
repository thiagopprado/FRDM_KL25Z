#include "mkl25_clock.h"
#include "mkl25_registers.h"

void board_clock_init(void) {
    SIM->CLKDIV1 = 0x10030000u; // Clock 1 divided by 2, Clock 4 divided by 8

    OSC0->CR = 0;
    OSC0->CR = 0x80; // External reference clock enabled
    MCG->C2 = 0x94; // High frequency crystal oscillator, OSC external reference
    while (!(MCG->S & 0x02)); // Waits OSCINIT0

    MCG->C1 = (MCG->C1 & ~(7 << 3)); // frdiv 0 (divided by 1)
    MCG->C2 &= ~(0x02); // Disable lowpower
    MCG->C1 = ((MCG->C1 & ~(0xC4)) | (0x80)); // Change to use external clock first
    while ((MCG->S & (0x1C)) != 0x08); // Wait for CLKST clock status bits to show clock source is ext ref clk

    MCG->C6 &= ~0x40; // Select FLL
    while (MCG->S & 0x20); // Waits PLL clock be FLL clock

    MCG->C5 = 1; // Disable the PLL first
    MCG->C6 = 0;
    MCG->C5 |= 0x40; // Enable PLL
    while (!(MCG->S & 0x40)); // Wait PLL unlock

    MCG->C6 |= 0x40; // Change to PLL mode
    while (!(MCG->S & 0x20)); // Wait for PLL mode changed

    MCG->C1 = (MCG->C1 & ~0xC0); // Change to use PLL output clock
    while ((MCG->S & 0x0C) != 0x0C); // Wait PLL output  

    MCG->SC = (MCG->SC & ~(0x2F)); // Update FCRDIV 
    MCG->C2 = (MCG->C2 & ~1); // Set internal reference clock selection
    MCG->C1 = (MCG->C1 & ~(0x03)) | 0x02;
    while((MCG->S & 0x01) != 0); // Wait for MCG_S_IRCST
    
    SIM->CLKDIV1 = 0x10010000;
    SIM->SOPT2 = (SIM->SOPT2 | 0x00010000); // Set PLLFLLSEL clock source
    SIM->SOPT1 = (SIM->SOPT1 | 0x000C0000); // Set ERCLK32K source
}
