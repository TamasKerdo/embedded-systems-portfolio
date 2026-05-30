#include <stdio.h>
#include <stddef.h>

typedef enum { RED, GREEN, YELLOW, NUM_STATES } state_t; // const -> cannot be changed (.rodata), static -> private
typedef enum { EV_TICK } event_t;

typedef state_t (*state_handler)(event_t); // takes an event, returns the next state
static state_t current_state = RED;

state_t stopping(event_t);
state_t trespassing(event_t);
state_t preparing(event_t);
state_t run_event(event_t);

static const state_handler jump_table[NUM_STATES] = { trespassing, preparing, stopping };

state_t stopping(event_t e)
{
  printf("Event: %d, Stopping..\n", e);

  return RED;
}

state_t trespassing(event_t e)
{
  printf("Event: %d, Trespassing..\n", e);

  return GREEN;
}

state_t preparing(event_t e)
{
  printf("Event: %d, Preparing..\n", e);

  return YELLOW;
}

state_t run_event(event_t e)
{
  current_state = jump_table[current_state](e);
  return current_state;
}

int main(void)
{
  printf("Initial state number: %d\n", current_state);

  for(int i = 0; i < 6; i++)
  {
    printf("State set to: %d\n", run_event(EV_TICK));
  }

  printf("State machine finished.\n");
}
