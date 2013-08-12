#include <stdexcept>
#include <iostream>
#include "usb_bitp_200.hh"

int main() try {
  usb_bitp_200 bitp(0);

  std::cout << "PING" << std::endl;
  for (delib::value_t i = 0; i < 100; i++) std::cout << ((bitp.ping (i) == i) ? "." : "E");
  std::cout << std::endl;

  std::cout << "Memory test" << std::endl;
  bitp.memory_test (1024);


  std::cout << "Write pattern" << std::endl;
  int memory_lines = 50;
  delib::matrix_t buff(memory_lines * 5, 0);

  uint8_t bits = 0xff;
  for (int i = 0; i < memory_lines; i++) {
    for (int j = 0; j < 5; j++) buff[memory_lines * 5 - 1 - i * 5 + j] = buff[i * 5 + j] = bits;
    bits &= bits - 1;
    if (!bits) break;
  }

  bitp.write_ram (buff, memory_lines * 5);

  std::cout << "Configuring" << std::endl;
  bitp.stop ();
  bitp.counter (0);
  bitp.ram_begin (0);
  bitp.ram_end (memory_lines);
  bitp.clock_divider (76);
  std::cout << "running " << bitp.counter () << " loops from " << bitp.ram_begin () << " to " << bitp.ram_end () << " with divider set to " << bitp.clock_divider () << std::endl;


  std::cout << "Start" << std::endl;
  bitp.start ();
  

  std::cout << "Status: " << bitp.status () << std::endl;
} catch (std::exception& ex) {
  std::cout << "exception: " << ex.what() << std::endl;
}


