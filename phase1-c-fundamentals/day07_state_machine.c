//#include <stdio.h>
#include <stddef.h>

typedef enum
{
  RED,
  GREEN,
  YELLOW,
  FLASHING,
  NUM_STATES
} state_t;
typedef enum
{
  EV_TICK,
  EV_NIGHT_MODE_ON,
  EV_NIGHT_MODE_OFF,
} event_t;

typedef state_t (*state_handler_t)(event_t);
static state_t current_state = RED;

state_t stopping(event_t);
state_t trespassing(event_t);
state_t preparing(event_t);
state_t trespassing_with_care(event_t);
state_t day_mode_setting(event_t);
state_t run_event(event_t);

static const state_handler_t jump_table[NUM_STATES] = {
    [RED] = stopping,
    [GREEN] = trespassing,
    [YELLOW] = preparing,
    [FLASHING] = trespassing_with_care,
};

state_t stopping(event_t e)
{
  //printf("Event: %d, Stopping..\n", e);

  return GREEN;
}

state_t trespassing(event_t e)
{
  //printf("Event: %d, Trespassing..\n", e);

  return YELLOW;
}

state_t preparing(event_t e)
{
  //printf("Event: %d, Preparing..\n", e);

  return RED;
}

state_t trespassing_with_care(event_t e)
{
  //printf("Event: %d, Trespassing with care..\n", e);

  return FLASHING;
}

state_t run_event(event_t e)
{
  if (e == EV_NIGHT_MODE_ON)
  {
    //printf("Event: %d, NIGHT MODE ON setted..\n", e);
    current_state = FLASHING;
  }
  else if (e == EV_NIGHT_MODE_OFF)
  {
    //printf("Event: %d, NIGHT MODE OFF setted..\n", e);
    current_state = RED;
  }
  else
  {
    current_state = jump_table[current_state](e);
  }

  return current_state;
}

int main(void)
{
  //printf("Initial state number: %d\n", current_state);

  for (int i = 0; i < 10; i++)
  {
    if (i == 3)
    {
      run_event(EV_NIGHT_MODE_ON);
    }
    else if (i == 5)
    {
      run_event(EV_NIGHT_MODE_OFF);
    }
    //printf("State set to: %d\n", run_event(EV_TICK));
  }

  //printf("State machine finished.\n");

  return 0;
}

/* commands:
arm-none-eabi-gcc ./phase1-c-fundamentals/day07_state_machine.c -c -o day07_state_machine_comp.o // compile without linking
objdump -z -s ./day07_state_machine_comp.o                                                       // decompress compressed parts (-z),
                                                                                                 // display the full contents of sections (-s) 

objdump -s -j .rodata ./day07_state_machine_comp.o

Contents of section .rodata:
 0000 00000000 00000000 00000000 00000000  ................ // Memory is allocated for the jump_table but not filled with real addresses. -> Linker phase.
*/ 