#include <algorithm>
#include <sstream>
#include <iomanip>
#include "ftdi_serial.hh"
#include <iostream>

ftdi_serial::ftdi_serial (int id, int nr): ftdi_base(id, nr, A), dw_codes_{{d1, 'B'}, {d2, 'W'}, {d4, 'L'}, {d8, 'X'}} {
}

delib::value_t ftdi_serial::ping_ (value_t count) { 
  write (d1, 0xFFFF, count);
  return read (d1, 0xFFFF);
}

void ftdi_serial::write_ (data_width dw, address_t address, value_t value) { 
  std::ostringstream tx;
  tx << "W" << dw_codes_[dw] << std::hex << std::setw (4) << std::setfill ('0') << address << std::setw (int(dw) * 2) << std::setfill ('0');

  cmd_ (oc_send, address, tx.str (), 0);
}

delib::value_t ftdi_serial::read_ (data_width dw, address_t address) { 
  std::ostringstream tx;
  tx << "R" << dw_codes_[dw] << std::hex << std::setw (4) << std::setfill ('0') << address;

  std::istringstream rx(cmd_ (oc_send, address, tx.str (), int(dw) * 2));
  value_t ret;
  rx >> ret;

  return ret;
}

#if 0
void ftdi_serial::write_ (address_t address, void *matrix, address_t columns, address_t rows) {
  cmd (oc_send_block, address, reinterpret_cast<uint8_t *>(matrix), columns, rows);
}


void ftdi_serial::read_ (address_t address, void *matrix, address_t columns, address_t rows) {
  cmd (oc_recv_block, address, reinterpret_cast<uint8_t *>(matrix), columns, rows);
}

delib::value_t ftdi_serial::cmd (opcode cmd, address_t address, address_t modifier, value_t data) {
  uint8_t job_id = job_id_inc ();

  if (cmd != oc_send) data = 0;
  uint8_t payload[24];

  std::fill_n (payload, 8, 0xfe);
  payload[8] = 0xff;
  payload[9] = job_id;
  payload[10] = cmd;
  std::copy (reinterpret_cast<uint8_t *>(&address), reinterpret_cast<uint8_t *>(&address) + 4, payload + 11);
  payload[15] = modifier;
  std::copy (reinterpret_cast<uint8_t *>(&data), reinterpret_cast<uint8_t *>(&data) + 8, payload + 16);
  address_t send_cnt = ((cmd == oc_send) ? 24 : 16);

  address_t ret = ftdi_write_data (&handle_, payload, send_cnt);
  if (ret < 0) throw std::runtime_error ("ftdi_write_data");

  address_t read_cnt = 3;
  if (cmd == oc_ping) read_cnt = 7;
  else if (cmd == oc_recv) read_cnt = 11;

  address_t done_cnt = 0;
  for (int i = 0; i < 20; i++) {
    ret = ftdi_read_data (&handle_, payload + done_cnt, read_cnt - done_cnt);
    if (ret < 0) throw std::runtime_error ("ftdi_read_data");

    if (ret == 0) continue;
    done_cnt += ret;

    if (done_cnt >= read_cnt) break;
  }
  if (done_cnt != read_cnt) throw std::runtime_error ("comunication error");

  if (payload[0] != 0x1A || payload[1] != job_id || payload[read_cnt - 1] != 0x4f) throw std::runtime_error ("malformed payload");

  std::copy (payload + 2, payload + 2 + sizeof (value_t), reinterpret_cast<uint8_t *>(&data));

  return data;
}


void ftdi_serial::cmd (opcode cmd, address_t address, uint8_t *matrix, address_t columns, address_t rows) {
  uint8_t job_id = job_id_inc ();

  std::vector<uint8_t> payload(2 * (columns + 1) * rows + 20, 0);
  
  std::fill_n (payload.begin (), 8, 0xfe);
  payload[8] = 0xff;
  payload[9] = job_id;
  payload[10] = cmd;
  std::copy (reinterpret_cast<uint8_t *>(&address), reinterpret_cast<uint8_t *>(&address) + 4, payload.begin () + 11);
  payload[15] = 0;
  std::copy (reinterpret_cast<uint8_t *>(&columns), reinterpret_cast<uint8_t *>(&columns) + 2, payload.begin () + 16);
  std::copy (reinterpret_cast<uint8_t *>(&rows), reinterpret_cast<uint8_t *>(&rows) + 2, payload.begin () + 18);
  address_t send_cnt = 20;

  if (cmd == oc_send_block) {
    std::copy (matrix, matrix + columns * rows, payload.begin () + send_cnt);
    send_cnt += columns * rows;
  }

  address_t ret = ftdi_write_data (&handle_, &payload[0], send_cnt);
  if (ret < 0) throw std::runtime_error ("ftdi_write_data");

  address_t read_cnt = (cmd == oc_send_block) ? 5 : ((columns + 1) * rows) + 3;

  address_t done_cnt = 0;
  for (int i = 0; i < 20; i++) {
    ret = ftdi_read_data (&handle_, &payload[0] + done_cnt, read_cnt - done_cnt);
    if (ret < 0) throw std::runtime_error ("ftdi_read_data");

    if (ret == 0) continue;
    done_cnt += ret;

    if (done_cnt >= read_cnt) break;
  }
  if (done_cnt != read_cnt) throw std::runtime_error ("comunication error");

  if (payload[0] != 0x1A || payload[1] != job_id || payload[read_cnt - 1] != 0x4f) throw std::runtime_error ("malformed payload");

  if (cmd == oc_send_block && (address_t(payload[3]) << 8 | payload[2]) != rows) throw std::runtime_error ("malformed answer");

  for (address_t i = 0; i < rows && cmd == oc_recv_block; i++) {
    if (payload[i * (columns + 1) + 2] != (i & 0xff)) throw std::runtime_error ("malformed answer");
    std::copy (payload.begin () + i * (columns + 1) + 3 , payload.begin () + (i + 1) * (columns + 1) + 3 - 1, matrix + i * columns);
  }
}
#endif
