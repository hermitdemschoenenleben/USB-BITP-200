#ifndef ORIG_H
#define ORIG_H
#include "delib.hh"
#include "orig_delib/delib/delib.h"

class orig: public delib {
  public:
    orig (int id, int nr);
    virtual ~orig ();

  private:
    value_t ping_ (value_t count) override;
    void write_ (data_width dw, address_t address, value_t value) override;
    void write_ (address_t address, void *matrix, address_t columns, address_t rows) override;
    value_t read_ (data_width dw, address_t address) override;
    void read_ (address_t address, void *matrix, address_t columns, address_t rows) override;

    unsigned long handle_;
};

#endif
