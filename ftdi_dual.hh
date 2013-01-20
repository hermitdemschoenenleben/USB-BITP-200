#ifndef FTDI_DUAL_H
#define FTDI_DUAL_H
#include "delib.hh"
#include <memory>
#include <ftdi.h>

class ftdi_dual: public delib {
  public:
    enum link_type { A, B, other };
    ftdi_dual (int id, int nr = 0, link_type link = B);
    virtual ~ftdi_dual ();

    void set_baudrate (int baudrate);
    void set_line_property (ftdi_bits_type bits, ftdi_stopbits_type sbit, ftdi_parity_type parity);
    void set_latency_timer (uint8_t latency);

  private:
    value_t ping_ (value_t count) override;
    void write_ (data_width dw, address_t address, value_t value) override;
    void write_ (address_t address, void *matrix, address_t columns, address_t rows) override;
    value_t read_ (data_width dw, address_t address) override;
    void read_ (address_t address, void *matrix, address_t columns, address_t rows) override;

    value_t cmd (opcode cmd, address_t address, address_t modifier, value_t data);
    void cmd (opcode cmd, address_t address, uint8_t *matrix, address_t columns, address_t rows);

    ftdi_context handle_;
};

#endif
