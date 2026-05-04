#include <stdint.h>

#define BUFFER_SIZE 32

typedef struct {
    uint16_t buffer[BUFFER_SIZE];                           // 32 * 2 = 64 bytes
    uint8_t newest_location;                                // 1 byte
    uint8_t oldest_location;                                // 1 byte
    uint32_t count;                                         // 4 bytes -> 70 bytes of .bss
} Buffer;

const uint32_t serial = 0xCAFE0001;                         //FLASH .rodata
const uint16_t* const sample = (const uint16_t*)0xCAFE0002; //FLASH .rodata (Address of the sensor register or input)
Buffer buffer = {0};                                        // SRAM .bss

static int log_sample(uint16_t);
int get_stats(uint32_t*, uint16_t*);

static int log_sample(uint16_t last){
    uint8_t newest_location = buffer.newest_location;       // stack frame
    uint8_t oldest_location = buffer.oldest_location;       // stack frame
      
    buffer.buffer[newest_location] = last;                  // push new element
    if(newest_location == (BUFFER_SIZE - 1)){               // step newest location
        buffer.newest_location = 0;
    } else{
        buffer.newest_location += 1;
    }

    if(newest_location == buffer.oldest_location){          // step oldest counter if newest == oldest
        if(oldest_location == (BUFFER_SIZE - 1)){
            buffer.oldest_location = 0;
        } else {
            buffer.oldest_location += 1;
        }
    }

    buffer.count += 1;
    return 0;
}

int get_stats(uint32_t *count, uint16_t *last){
    *last = buffer.buffer[buffer.oldest_location];
    *count = buffer.count;
    return 0;
}

int main(void) {
    uint16_t last = *sample;                                 // stack frame
 
    while(1){
        log_sample(last);
    }
}

/*
arm-none-eabi-size day06_circular_buffer.o

text    data     bss     dec     hex filename
 228       0      72     300     12c day06_circular_buffer.o

arm-none-eabi-nm day06_circular_buffer.o 
00000000 B buffer
0000008c T get_stats
00000000 t log_sample
000000c0 T main
00000004 R sample
00000000 R serial
*/