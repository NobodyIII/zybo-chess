#include <stdint.h>
#include <stdio.h>
// #include <xparameters.h>
#include "async_ai.h"
#include "chessControl.h"
#include "config.h"
#include "interrupts.h"
#include "utils.h"
#include "xparameters.h"

// Compute the timer clock freq.
#define TIMER_CLOCK_FREQUENCY (XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ / 2)
// Compute timer load value.
#define TIMER_LOAD_VALUE ((CONFIG_TIMER_PERIOD * TIMER_CLOCK_FREQUENCY) - 1.0)

static volatile int nest_depth = 0;

void tick_all() { chessControl_tick(); }

int main() {
  interrupts_initAll(true);
  interrupts_setPrivateTimerLoadValue(TIMER_LOAD_VALUE);
  interrupts_enableTimerGlobalInts();
  chessControl_init();
  // Start the private ARM timer running.
  interrupts_startArmPrivateTimer();
  // Enable interrupts at the ARM.
  interrupts_enableArmInts();

  async_ai_main();
}

// Interrupt routine
void isr_function() { tick_all(); }