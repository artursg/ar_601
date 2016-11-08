#include <stdint.h>

#include <boost/array.hpp>

const short PACKET_SIZE = 1472;
const int N_DEVICES = 72;

typedef boost::array<uint8_t, PACKET_SIZE> ARPacketT;

int16_t as_int16_t(uint8_t first, uint8_t second);
void as_2uint8_t(int16_t in, uint8_t & out1, uint8_t & out2);

