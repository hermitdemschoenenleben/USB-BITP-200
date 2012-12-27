#include "delib.hh"

#ifdef DEBUG_DELIB
#include <iostream>
#include <iomanip>
#endif


delib::value_t delib::ping (value_t count) {
  auto x = ping_ (count);
#ifdef DEBUG_DELIB
  std::cout << "delib::ping(" << std::hex << count << "): " << x << std::endl;
#endif
  return x;
}

void delib::write (data_width dw, address_t address, value_t value) {
  write_ (dw, address, value); 
#ifdef DEBUG_DELIB
  std::cout << "delib::write(" << dw << "," << std::hex << address << "," << std::hex << value << ")" << std::endl;
#endif
}

void delib::write (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) {
  write_ (address, adress_depth, increments, buff, buff_len);
#ifdef DEBUG_DELIB
  std::cout << "delib::write(" << std::hex << address << "," << std::hex << "," adress_depth << "," << increments << ")" << std::endl;
  for (int i = 0; i < buff_len; i++) std::cout << std::hex << int((char*(buff))[i]) << " ";
  std::cout << std::endl;
#endif
}

delib::value_t delib::read (data_width dw, address_t address) { 
  auto x = read_ (dw, address); 
#ifdef DEBUG_DELIB
  std::cout << "delib::read(" << dw << "," << std::hex << address << "): " << x << std::endl;
#endif
  return x;
}

void delib::read (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) {
  read_ (address, adress_depth, increments, buff, buff_len);
#ifdef DEBUG_DELIB
  std::cout << "delib::read(" << std::hex << address << "," << std::hex << "," adress_depth << "," << increments << ")" << std::endl;
  for (int i = 0; i < buff_len; i++) std::cout << std::hex << int((char*(buff))[i]) << " ";
  std::cout << std::endl;
#endif
}
