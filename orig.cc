#include "orig.hh"

orig::orig (int id, int nr) { handle_ = DapiOpenModule (id, nr); }

delib::value_t orig::ping_ (value_t count) { return DapiPing (handle_, count); }

void orig::write_ (data_width dw, address_t address, value_t value) { 
  switch (dw) {
    case d1:
      DapiWriteByte (handle_, address, value);
      break;
    case d2:
      DapiWriteWord (handle_, address, value);
      break;
    case d4:
      DapiWriteLong (handle_, address, value);
      break;
    case d8:
      DapiWriteLongLong (handle_, address, value);
      break;
  }
}

void orig::write_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) {
  DapiWriteMultipleBytes (handle_, address, adress_depth, increments, (unsigned char*)buff, buff_len);
}

delib::value_t orig::read_ (data_width dw, address_t address) { 
  switch (dw) {
    case d1:
      return DapiReadByte (handle_, address);
      break;
    case d2:
      return DapiReadWord (handle_, address);
      break;
    case d4:
      return DapiReadLong (handle_, address);
      break;
    case d8:
      return DapiReadLongLong (handle_, address);
      break;
  }
  return 0;
}

void orig::read_ (address_t address, address_t adress_depth, address_t increments, void *buff, size_t buff_len) {
  DapiReadMultipleBytes (handle_, address, adress_depth, increments, (unsigned char*)buff, buff_len);
}
