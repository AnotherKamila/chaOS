#include "bit_manip.h"

//These were copied from http://graphics.stanford.edu/~seander/bithacks.html#InterleaveBMN
static const unsigned int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
static const unsigned int S[] = {1, 2, 4, 8};

uint32_t bits_stretch(uint32_t x) {
	x = (x | (x << S[3])) & B[3];
	x = (x | (x << S[2])) & B[2];
	x = (x | (x << S[1])) & B[1];
	x = (x | (x << S[0])) & B[0];
	return x;
}

uint32_t bits_expand(uint32_t x) {
	uint32_t res = bits_stretch(x);
	return res | (res << 1);
}