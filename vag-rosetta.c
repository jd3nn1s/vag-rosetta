#include <stdio.h>
#include "vag-rosetta.h"

// translation function prototype
typedef void (*trans_t)(uint8_t a, uint8_t b, vag_value* value);

// Functions that translate bytes a and b based on the translation byte identifier

void trans1(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "RPM";
    value->type = TYPE_INT;
    value->i = a * 0.2 * b;
}

void trans2(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "%";
    value->type = TYPE_FLOAT;
    value->f = (float)a * 0.002 * (float)b;
}

void trans3(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "Deg";
    value->type = TYPE_FLOAT;
    value->f = (float)a * 0.002 * (float)b;
}

void trans4(uint8_t a, uint8_t b, vag_value* value) {
    value->type = TYPE_FLOAT;
    value->f = abs(b - 127) * 0.01 * a;
    if (value->f > 127)
        value->units = "ATDC";
    else
        value->units = "BTDC";
}

void trans5(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "C";
    value->type = TYPE_FLOAT;
    value->f = (0.1 * a * b) - (10 * a);
}

void trans6(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "V";
    value->type = TYPE_FLOAT;
    value->f = 0.001 * a * b;
}

void trans7(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "km/h";
    value->type = TYPE_INT;
    value->i = 0.01 * a * b;
}

void trans8(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "-";
    value->type = TYPE_FLOAT;
    value->f = 0.1 * a * b;
}

void trans9(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "Deg";
    value->type = TYPE_FLOAT;
    value->f = (b - 127) * 0.02 * a; 
}

void trans10(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "";
    value->type = TYPE_STRING;
    if (b == 0)
        value->s = "COLD";
    else
        value->s = "WARM";
}

void trans11(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "-";
    value->type = TYPE_FLOAT;
    value->f = 0.0001 * a * (b - 128) + 1;
}

void trans15(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "ms";
    value->type = TYPE_INT;
    value->i = 0.01 * a * b;
}

void trans16(uint8_t a, uint8_t b, vag_value* value) {
    value->units = "-";
    value->type = TYPE_BITMASK;
    value->bits = a;
    value->bitmask = b;
}

trans_t translations[] = {
    0,
    trans1,
    trans2,
    trans3,
    trans4,
    trans5,
    trans6,
    trans7,
    trans8,
    trans9,
    trans10,
    trans11,
    0,
    0,
    0,
    trans15,
    trans16
};

bool decode_value(uint8_t* bytes, vag_value* value) {
    if (bytes[0] > sizeof(translations) - 1)
        return false;
    if (translations[bytes[0]] == 0)
        return false;
    translations[bytes[0]](bytes[1], bytes[2], value);
    return true;
}

void print_value(vag_value* value) {
    switch(value->type) {
    case TYPE_INT:
        printf("%d %s\n", value->i, value->units);
        break;
    case TYPE_FLOAT:
        printf("%.1f %s\n", value->f, value->units);
        break;
    default:
        printf("unsupported type\n");
        break;
    }
}
