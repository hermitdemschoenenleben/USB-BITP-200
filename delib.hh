#ifndef DELIB_H
#define DELIB_H
#include <stdint.h>
#include <stddef.h>

class delib {
  public:
    typedef uint32_t address_t;
    typedef uint64_t value_t;

    delib () {}
    virtual ~delib () {}

    value_t ping (value_t count);

    enum data_width { d1, d2, d4, d8 };

    void write (data_width dw, address_t address, value_t value);
    void write (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len);

    value_t read (data_width dw, address_t address);
    void read (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len);

  private:
    virtual value_t ping_ (value_t count) = 0;
    virtual void write_ (data_width dw, address_t address, value_t value) = 0;
    virtual void write_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) = 0;
    virtual value_t read_ (data_width dw, address_t address) = 0;
    virtual void read_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) = 0;
};

#endif
