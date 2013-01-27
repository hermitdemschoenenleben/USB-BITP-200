#ifndef DELIB_H
#define DELIB_H
#include <stdint.h>
#include <stddef.h>
#include <mutex>

class delib {
  public:
    typedef uint32_t address_t;
    typedef uint64_t value_t;

    delib (): job_id_(1) {}
    virtual ~delib () {}

    value_t ping (value_t count);

    enum data_width { d1 = sizeof (uint8_t), d2 = sizeof (uint16_t), d4 = sizeof (uint32_t), d8 = sizeof (uint64_t) };

    void write (data_width dw, address_t address, value_t value);
    void write (address_t address, void *matrix, address_t columns, address_t rows);

    value_t read (data_width dw, address_t address);
    void read (address_t address, void *matrix, address_t columns, address_t rows);

    int job_id () const { return job_id_; }
  private:
    virtual value_t ping_ (value_t count) = 0;
    virtual void write_ (data_width dw, address_t address, value_t value) = 0;
    virtual void write_ (address_t address, void *matrix, address_t columns, address_t rows) = 0;
    virtual value_t read_ (data_width dw, address_t address) = 0;
    virtual void read_ (address_t address, void *matrix, address_t columns, address_t rows) = 0;

    int job_id_;
    std::mutex mutex_;

  protected:
    int job_id_inc () { return job_id_++; }

    enum opcode {
      oc_ping = 0x12,
      oc_send = 0x23,
      oc_recv = 0x34,
      oc_send_block = 0x45,
      oc_recv_block = 0x56,
    };
};

#endif
