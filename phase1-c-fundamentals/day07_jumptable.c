//#include <stdio.h>
#include <stddef.h>

typedef void (*command_type)(void);

void cmd_led_on(void);
void cmd_led_off(void);
void cmd_reset(void);
void dispatch(unsigned int);

static const command_type command_table[] = {cmd_led_on, cmd_led_off, cmd_reset, NULL};
enum { COMMAND_TABLE_SIZE = sizeof(command_table) / sizeof(command_table[0]) };

void cmd_led_on(void)
{
  //printf("Command call: cmd_led_on\n");
}

void cmd_led_off(void)
{
  //printf("Command call: cmd_led_off\n");
}

void cmd_reset(void)
{
  //printf("Command call: cmd_reset\n");
}

void dispatch(unsigned int command_number)
{
  //printf("Function call: dispatch\n");

  if (command_number < COMMAND_TABLE_SIZE)
  {
    command_type command_pointer = command_table[command_number];
    if (command_pointer != NULL)
    {
      command_pointer();
    }
    else
    {
      //printf("Undefined command: %d, execution skipped.\n", command_number);
    }
  }
  else
  {
    //printf("Out of range command number: %d, execution skipped.\n", command_number);
  }
}

int main(void)
{
  dispatch(0);
  dispatch(1);
  dispatch(2);
  dispatch(3);
  dispatch(4);
}

// > gcc -c ./phase1-c-fundamentals/day07_jumptable.c -o jt.o
// > nm jt.o | grep -E 'cmd|table'        # find the table and command symbols
// >
//  000000000000001a T cmd_led_off        -> T (man): The symbol is in the text (code) section,
//  0000000000000000 T cmd_led_on
//  0000000000000034 T cmd_reset
//  0000000000000000 d command_table      -> D (man): The symbol is in the initialized data section.
//  0000000000000000 d command_table_size

// objdump -d jt.o                       # disassemble — find the indexed call
// objdump -s -j .data -j .rodata jt.o   # dump the table's raw bytes
