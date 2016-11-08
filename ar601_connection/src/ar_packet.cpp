#include "ar_packet.h"

int16_t as_int16_t(uint8_t first, uint8_t second){
  return (int16_t)(((uint16_t)second << 8) | first);
}

void as_2uint8_t(int16_t in_, uint8_t & out1, uint8_t & out2){
  uint16_t in = static_cast<uint16_t>(in_);

  uint8_t *value1;
  uint8_t *value2;

  // set the pointers to the correct buffer location
  
  value1 = (uint8_t *)(&in_);
  
  out1 = *value1;
  out2 = *++value1;
}

