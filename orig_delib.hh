#ifndef ORIG_DELIB_H
#define ORIG_DELIB_H
#include "delib.hh"
#include "orig_delib/delib/delib.h"

class orig_delib: public delib {
  public:
    orig_delib (int id, int nr);

  private:
    value_t ping_ (value_t count) override;
    void write_ (data_width dw, address_t address, value_t value) override;
    void write_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) override;
    value_t read_ (data_width dw, address_t address) override;
    void read_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) override;

    unsigned long handle_;
};

#endif
