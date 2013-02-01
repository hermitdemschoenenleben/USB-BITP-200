#include <stdexcept>
#include <iostream>
#include "usb_bpg_200.hh"

int main() try {
  usb_bpg_200 bpg(0);

  std::cout << "PING" << std::endl;
  for (delib::value_t i = 0; i < 100; i++) std::cout << ((bpg.ping (i) == i) ? "." : "E");
  std::cout << std::endl;

  std::cout << "Memory test" << std::endl;
  bpg.memory_test (1024);


  std::cout << "Write pattern" << std::endl;
  int memory_lines = 100;
  delib::matrix_t buff(memory_lines * 5);

  for (int i = 0; i < memory_lines; i++)
    for (int j = 0; j < 5; j++) buff[i * 5 + j] = (i & 0xff) + j;

  bpg.write_ram (buff, memory_lines * 5);

  std::cout << "Configuring" << std::endl;
  bpg.stop ();
  bpg.counter (10);
  bpg.mapping (2, 22);
  bpg.clock_divider (76);


  std::cout << "Start" << std::endl;
  bpg.start ();
  

  std::cout << "Status: " << bpg.status () << std::endl;
} catch (std::exception& ex) {
  std::cout << "exception: " << ex.what() << std::endl;
}


