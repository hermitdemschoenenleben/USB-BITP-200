#ifndef USB_BPG_200_H_
#define USB_BPG_200_H_
#include <memory>
#include "delib.hh"

class usb_bpg_200 {
  public:
    usb_bpg_200 (int device_nr);

    delib::value_t ping (delib::value_t count);

    void start ();
    void stop ();
    void pc_mode ();

    void write_ram (const delib::matrix_t &buff, size_t buffer_length);
    void read_ram (delib::matrix_t &buff, size_t buffer_length);
    void memory_test (size_t memory_lines);

    void reset_counter ();
    void counter (delib::value_t nr);
    void clock_divider (delib::value_t nr);
    void mapping (delib::address_t start, delib::address_t stop);

    delib::value_t status ();
    delib::value_t address ();
    delib::value_t ram_sm ();
    delib::value_t counter ();

  private:
    void set_cfg_bit (int bit);
    void clear_cfg_bit (int bit);
    void flip_10_cfg_bit (int bit);

    delib::value_t cfg_reg_;
    std::unique_ptr<delib::base> io_;
};
#endif
