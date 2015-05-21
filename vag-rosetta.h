#include <stdint.h>
#include <stdbool.h>

struct vag_value {
    int type;
    int i;
    float f;
    char* s;
    uint8_t bits;
    uint8_t bitmask;
    char* units;
} typedef vag_value;

#define TYPE_INT 1
#define TYPE_FLOAT 2
#define TYPE_STRING 4
#define TYPE_BITMASK 8

bool decode_value(uint8_t*, vag_value*);
void print_value(vag_value*);
