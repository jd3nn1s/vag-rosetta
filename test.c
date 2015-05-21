#include <stdio.h>
#include "vag-rosetta.h"

int test_decode(uint8_t bytes[3]) {
    vag_value val;
    if (decode_value(bytes, &val)) {
        print_value(&val);
    }
    else
        printf("Could not decode %02x %02x %02x\n", bytes[0], bytes[1], bytes[2]);
}

int main(void)
{
    uint8_t bytes[] = {0x01, 0xc8, 0x31};
    test_decode(bytes);
    return 0;
}
