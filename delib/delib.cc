#include "delib.hh"

#ifdef DEBUG_DELIB
#include <iostream>
#include <iomanip>
#endif


delib::value_t delib::ping (value_t count) {
  std::lock_guard<std::mutex> lk(mutex_);
  auto x = ping_ (count);
#ifdef DEBUG_DELIB
  std::cout << "delib::ping(" << std::hex << count << "): " << x << std::endl;
#endif
  return x;
}

void delib::write (data_width dw, address_t address, value_t value) {
  std::lock_guard<std::mutex> lk(mutex_);
  write_ (dw, address, value); 
#ifdef DEBUG_DELIB
  std::cout << "delib::write(" << dw << "," << std::hex << address << "," << std::hex << value << ")" << std::endl;
#endif
}

void delib::write (address_t address, void *matrix, address_t columns, address_t rows) {
  std::lock_guard<std::mutex> lk(mutex_);
  write_ (address, matrix, columns, rows); 
#ifdef DEBUG_DELIB
  std::cout << "delib::write(" << std::hex << address << "," << std::hex << "," columns << "," << rows << ")" << std::endl;
  for (int i = 0; i < buff_len; i++) std::cout << std::hex << int((char*(matrix))[i]) << " ";
  std::cout << std::endl;
#endif
}

delib::value_t delib::read (data_width dw, address_t address) { 
  std::lock_guard<std::mutex> lk(mutex_);
  auto x = read_ (dw, address); 
#ifdef DEBUG_DELIB
  std::cout << "delib::read(" << dw << "," << std::hex << address << "): " << x << std::endl;
#endif
  return x;
}

void delib::read (address_t address, void *matrix, address_t columns, address_t rows) {
  std::lock_guard<std::mutex> lk(mutex_);
  read_ (address, matrix, columns, rows);
#ifdef DEBUG_DELIB
  std::cout << "delib::read(" << std::hex << address << "," << std::hex << "," columns << "," << rows << ")" << std::endl;
  for (int i = 0; i < buff_len; i++) std::cout << std::hex << int((char*(matrix))[i]) << " ";
  std::cout << std::endl;
#endif
}
