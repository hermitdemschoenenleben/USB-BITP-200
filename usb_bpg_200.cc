#include <algorithm>
#include <iostream>
#include "usb_bpg_200.hh"
#include "orig.hh"

usb_bpg_200::usb_bpg_200 (int nr): cfg_reg_(0) {
  io_ = new orig (USB_BITP_200, nr);
}

void usb_bpg_200::set_cfg_bit (int bit) {
  cfg_reg_ |= (1 << bit);
  io_->write (delib::d4, 0, cfg_reg_);
}

void usb_bpg_200::clear_cfg_bit (int bit) {
  cfg_reg_ &= ~(1 << bit);
  io_->write (delib::d4, 0, cfg_reg_);
}

void usb_bpg_200::flip_10_cfg_bit (int bit) {
  set_cfg_bit (bit);
  clear_cfg_bit (bit);
}


delib::value_t usb_bpg_200::ping (delib::value_t count) { return io_->ping (count); }

void usb_bpg_200::start () { flip_10_cfg_bit (0); }

void usb_bpg_200::stop () { flip_10_cfg_bit (1); }

void usb_bpg_200::pc_mode () { flip_10_cfg_bit (2); }

void usb_bpg_200::reset_counter () { flip_10_cfg_bit (5); }

void usb_bpg_200::counter (delib::value_t nr) {
  if (!nr) set_cfg_bit (3);
  else {
    io_->write (delib::d4, 0x18, nr);
    clear_cfg_bit (3);
  }
}

void usb_bpg_200::clock_divider (delib::value_t nr) {
  if (!nr) set_cfg_bit (4);
  else {
    clear_cfg_bit (4);
    io_->write (delib::d4, 0x1C, nr << 1);
  }
}  

void usb_bpg_200::mapping (delib::address_t start, delib::address_t stop) {
  io_->write (delib::d4, 0x10, start >> 1);
  io_->write (delib::d4, 0x14, stop >> 1); // + 1 ?
}

delib::value_t usb_bpg_200::status () { return 0xf & io_->read (delib::d4, 0xe8); }

delib::value_t usb_bpg_200::address () { return 0xf0 & io_->read (delib::d4, 0xf0); }

delib::value_t usb_bpg_200::ram_sm () { return 0xff & io_->read (delib::d4, 0xe9); }

delib::value_t usb_bpg_200::counter () { return io_->read (delib::d4, 0xd8); }

void usb_bpg_200::write_ram (void *buff, size_t buffer_length) {
  stop ();

  reset_counter ();

  io_->write (0x60, 10, buffer_length / 10, buff, buffer_length);
}



void usb_bpg_200::read_ram (void *buff, size_t buffer_length) {
  reset_counter ();

  io_->read (delib::d4, 0x68);

  io_->read (0x60, 10, buffer_length / 10, buff, buffer_length);
}

void usb_bpg_200::memory_test (size_t memory_lines) {
  stop ();
  uint8_t *buff = 0, *buff2 = 0;

  try {
    // 512*1024 = Speicher vom USB-BITP-200
    //ULONG memory_lines = 8*1024;		// Muss geradzahlig sein !!!!!!!!!!!!

    buff = new uint8_t[memory_lines * 5];
    buff2 = new uint8_t[memory_lines * 5];

    for (size_t i = 0; i < memory_lines; i++) {
      for (size_t j = 0; j < 5; j++) buff[i * 5 + j] = (i & 0xff) + 1 + j;
      buff [i * 5 + 4] &= 0xf;
    }

    write_ram (buff, memory_lines * 5);

    read_ram (buff2, memory_lines * 5);

    if (!std::equal (buff, buff + memory_lines * 5, buff2)) {
      auto x = std::mismatch (buff, buff + memory_lines * 5, buff2);
      std::cout << "memory mismatch at position " << x.first - buff << " values " << int(*x.first) << "!=" << int(*x.second) << std::endl;
    }
    delete [] buff;
    delete [] buff2;
  } catch (...) {
    delete [] buff;
    delete [] buff2;
    throw;
  }
}
