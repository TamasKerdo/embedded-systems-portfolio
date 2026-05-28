#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

void print_structs(void);
void print_bitfields(void);
void print_mock_register(void);

void print_structs(void)
{
  typedef struct
  {
    uint8_t a;
    uint32_t b;
    uint16_t c;
  } StructA;

  typedef struct
  {
    uint8_t a;
    uint16_t b;
    uint32_t c;
  } StructB;

  printf(
      "ScructA:\n"
      "--> Size: %zu\n"
      "--> Offset of a: %zu\n"
      "--> Offset of b: %zu\n"
      "--> Offset of c: %zu\n\n",
      sizeof(StructA),
      offsetof(StructA, a),
      offsetof(StructA, b),
      offsetof(StructA, c));

  printf(
      "ScructB:\n"
      "--> Size: %zu\n"
      "--> Offset of a: %zu\n"
      "--> Offset of b: %zu\n"
      "--> Offset of c: %zu\n\n",
      sizeof(StructB),
      offsetof(StructB, a),
      offsetof(StructB, b),
      offsetof(StructB, c));
}

void print_bitfields(void)
{
  typedef struct
  {
    uint8_t enabled : 1;
    uint8_t speed : 3;
    uint8_t direction : 1;
    uint8_t reserved : 3;
  } MotorControl;

  printf("Size of MotorControl: %zu\n", sizeof(MotorControl));
  MotorControl a = {.enabled = 0b1, .speed = 0b101, .direction = 0b1, .reserved = 0b001};

  printf(
      "MotorControl:\n"
      "  --> enabled: %d\n"
      "  --> speed: %d\n"
      "  --> direction: %d\n"
      "  --> reserved: %d\n",
      a.enabled,
      a.speed,
      a.direction,
      a.reserved);

  printf("Bits of speed: \n");
  for (int i = 0; i < 3; i++)
  {
    uint8_t mask = 0b00000001 << i;
    uint8_t cleared = (mask & a.speed);
    printf("%c", (mask == cleared ? '1' : '0'));
  }
  printf("\n");
}

// #define USART1 ((USART_TypeDef *) 0x40011000U)

// void print_mock_register(void){
//     typedef struct {
//         volatile uint32_t SR;
//         volatile uint32_t DR;
//         volatile uint32_t BRR;
//         volatile uint32_t CR1;
//     } USART_TypeDef;
//
//     printf("%d", USART1->CR1);
// }

int main(void)
{
  print_structs();
  print_bitfields();
  // print_mock_register();
  return 0;
}