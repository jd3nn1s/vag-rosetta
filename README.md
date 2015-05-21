# vag-rosetta

Simple library to take a 3 byte sequence from a KWP1281 measuring block and return a value struct with the calculated true value in it.

`bool decode_value(uint8_t*, vag_value*);`

Expects a 3 byte array and fills out vag_value with type and value

`void print_value(vag_value*);`

Given a vag_value print to stdout the value and units
