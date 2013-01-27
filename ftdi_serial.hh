#ifndef FTDI_SERIAL_H
#define FTDI_SERIAL_H

#include <map>
#include "ftdi_base.hh"

class ftdi_serial: public ftdi_base {
  public:
    ftdi_serial (int id, int nr = 0);

  private:
    value_t ping_ (value_t count) override;
    void write_ (data_width dw, address_t address, value_t value) override;
    void write_ (address_t address, void *matrix, address_t columns, address_t rows) override;
    value_t read_ (data_width dw, address_t address) override;
    void read_ (address_t address, void *matrix, address_t columns, address_t rows) override;

    std::string cmd_ (opcode cmd, address_t address, const std::string &data, int read_cnt);
    void cmd_ (opcode cmd, address_t address, uint8_t *matrix, address_t columns, address_t rows);
    std::map<data_width, uint8_t> dw_codes_;
};

#endif
