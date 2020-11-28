/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ffrpc_msg_TYPES_H
#define ffrpc_msg_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace ffrpc_msg {

typedef struct _session_offline_in_t__isset {
  _session_offline_in_t__isset() : session_id(true) {}
  bool session_id;
} _session_offline_in_t__isset;

class session_offline_in_t {
 public:

  static const char* ascii_fingerprint; // = "7CBAC864381682B525334E49955F454B";
  static const uint8_t binary_fingerprint[16]; // = {0x7C,0xBA,0xC8,0x64,0x38,0x16,0x82,0xB5,0x25,0x33,0x4E,0x49,0x95,0x5F,0x45,0x4B};

  session_offline_in_t() : session_id(0LL) {
  }

  virtual ~session_offline_in_t() throw() {}

  int64_t session_id;

  _session_offline_in_t__isset __isset;

  void __set_session_id(const int64_t val) {
    session_id = val;
  }

  bool operator == (const session_offline_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    return true;
  }
  bool operator != (const session_offline_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const session_offline_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(session_offline_in_t &a, session_offline_in_t &b);


class session_offline_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  session_offline_out_t() {
  }

  virtual ~session_offline_out_t() throw() {}


  bool operator == (const session_offline_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const session_offline_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const session_offline_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(session_offline_out_t &a, session_offline_out_t &b);

typedef struct _routeLogicMsg_in_t__isset {
  _routeLogicMsg_in_t__isset() : session_id(true), cmd(true), body(false), session_ip(false) {}
  bool session_id;
  bool cmd;
  bool body;
  bool session_ip;
} _routeLogicMsg_in_t__isset;

class routeLogicMsg_in_t {
 public:

  static const char* ascii_fingerprint; // = "EADC45C9A213F80E462BAA7CE9FA080F";
  static const uint8_t binary_fingerprint[16]; // = {0xEA,0xDC,0x45,0xC9,0xA2,0x13,0xF8,0x0E,0x46,0x2B,0xAA,0x7C,0xE9,0xFA,0x08,0x0F};

  routeLogicMsg_in_t() : session_id(0LL), cmd(0), body(), session_ip() {
  }

  virtual ~routeLogicMsg_in_t() throw() {}

  int64_t session_id;
  int16_t cmd;
  std::string body;
  std::string session_ip;

  _routeLogicMsg_in_t__isset __isset;

  void __set_session_id(const int64_t val) {
    session_id = val;
  }

  void __set_cmd(const int16_t val) {
    cmd = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  void __set_session_ip(const std::string& val) {
    session_ip = val;
  }

  bool operator == (const routeLogicMsg_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    if (!(cmd == rhs.cmd))
      return false;
    if (!(body == rhs.body))
      return false;
    if (!(session_ip == rhs.session_ip))
      return false;
    return true;
  }
  bool operator != (const routeLogicMsg_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const routeLogicMsg_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(routeLogicMsg_in_t &a, routeLogicMsg_in_t &b);


class routeLogicMsg_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  routeLogicMsg_out_t() {
  }

  virtual ~routeLogicMsg_out_t() throw() {}


  bool operator == (const routeLogicMsg_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const routeLogicMsg_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const routeLogicMsg_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(routeLogicMsg_out_t &a, routeLogicMsg_out_t &b);

typedef struct _gate_change_logic_node_in_t__isset {
  _gate_change_logic_node_in_t__isset() : session_id(true), alloc_worker(false), cur_group_name(false), dest_group_name(false), extra_data(false) {}
  bool session_id;
  bool alloc_worker;
  bool cur_group_name;
  bool dest_group_name;
  bool extra_data;
} _gate_change_logic_node_in_t__isset;

class gate_change_logic_node_in_t {
 public:

  static const char* ascii_fingerprint; // = "3CC2C885F5B9D03E96907F8376BF80E9";
  static const uint8_t binary_fingerprint[16]; // = {0x3C,0xC2,0xC8,0x85,0xF5,0xB9,0xD0,0x3E,0x96,0x90,0x7F,0x83,0x76,0xBF,0x80,0xE9};

  gate_change_logic_node_in_t() : session_id(0LL), alloc_worker(), cur_group_name(), dest_group_name(), extra_data() {
  }

  virtual ~gate_change_logic_node_in_t() throw() {}

  int64_t session_id;
  std::string alloc_worker;
  std::string cur_group_name;
  std::string dest_group_name;
  std::string extra_data;

  _gate_change_logic_node_in_t__isset __isset;

  void __set_session_id(const int64_t val) {
    session_id = val;
  }

  void __set_alloc_worker(const std::string& val) {
    alloc_worker = val;
  }

  void __set_cur_group_name(const std::string& val) {
    cur_group_name = val;
  }

  void __set_dest_group_name(const std::string& val) {
    dest_group_name = val;
  }

  void __set_extra_data(const std::string& val) {
    extra_data = val;
  }

  bool operator == (const gate_change_logic_node_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    if (!(alloc_worker == rhs.alloc_worker))
      return false;
    if (!(cur_group_name == rhs.cur_group_name))
      return false;
    if (!(dest_group_name == rhs.dest_group_name))
      return false;
    if (!(extra_data == rhs.extra_data))
      return false;
    return true;
  }
  bool operator != (const gate_change_logic_node_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_change_logic_node_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_change_logic_node_in_t &a, gate_change_logic_node_in_t &b);


class gate_change_logic_node_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  gate_change_logic_node_out_t() {
  }

  virtual ~gate_change_logic_node_out_t() throw() {}


  bool operator == (const gate_change_logic_node_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const gate_change_logic_node_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_change_logic_node_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_change_logic_node_out_t &a, gate_change_logic_node_out_t &b);

typedef struct _gate_closeSession_in_t__isset {
  _gate_closeSession_in_t__isset() : session_id(true) {}
  bool session_id;
} _gate_closeSession_in_t__isset;

class gate_closeSession_in_t {
 public:

  static const char* ascii_fingerprint; // = "56A59CE7FFAF82BCA8A19FAACDE4FB75";
  static const uint8_t binary_fingerprint[16]; // = {0x56,0xA5,0x9C,0xE7,0xFF,0xAF,0x82,0xBC,0xA8,0xA1,0x9F,0xAA,0xCD,0xE4,0xFB,0x75};

  gate_closeSession_in_t() : session_id(0LL) {
  }

  virtual ~gate_closeSession_in_t() throw() {}

  int64_t session_id;

  _gate_closeSession_in_t__isset __isset;

  void __set_session_id(const int64_t val) {
    session_id = val;
  }

  bool operator == (const gate_closeSession_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    return true;
  }
  bool operator != (const gate_closeSession_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_closeSession_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_closeSession_in_t &a, gate_closeSession_in_t &b);


class gate_closeSession_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  gate_closeSession_out_t() {
  }

  virtual ~gate_closeSession_out_t() throw() {}


  bool operator == (const gate_closeSession_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const gate_closeSession_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_closeSession_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_closeSession_out_t &a, gate_closeSession_out_t &b);

typedef struct _gate_routeMmsgToSession_in_t__isset {
  _gate_routeMmsgToSession_in_t__isset() : session_id(true), cmd(true), body(false) {}
  bool session_id;
  bool cmd;
  bool body;
} _gate_routeMmsgToSession_in_t__isset;

class gate_routeMmsgToSession_in_t {
 public:

  static const char* ascii_fingerprint; // = "0F4880829CCE5EA99C09EDF6EED29938";
  static const uint8_t binary_fingerprint[16]; // = {0x0F,0x48,0x80,0x82,0x9C,0xCE,0x5E,0xA9,0x9C,0x09,0xED,0xF6,0xEE,0xD2,0x99,0x38};

  gate_routeMmsgToSession_in_t() : cmd(0), body() {

  }

  virtual ~gate_routeMmsgToSession_in_t() throw() {}

  std::vector<int64_t>  session_id;
  int16_t cmd;
  std::string body;

  _gate_routeMmsgToSession_in_t__isset __isset;

  void __set_session_id(const std::vector<int64_t> & val) {
    session_id = val;
  }

  void __set_cmd(const int16_t val) {
    cmd = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const gate_routeMmsgToSession_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    if (!(cmd == rhs.cmd))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const gate_routeMmsgToSession_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_routeMmsgToSession_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_routeMmsgToSession_in_t &a, gate_routeMmsgToSession_in_t &b);


class gate_routeMmsgToSession_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  gate_routeMmsgToSession_out_t() {
  }

  virtual ~gate_routeMmsgToSession_out_t() throw() {}


  bool operator == (const gate_routeMmsgToSession_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const gate_routeMmsgToSession_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_routeMmsgToSession_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_routeMmsgToSession_out_t &a, gate_routeMmsgToSession_out_t &b);

typedef struct _gate_broadcastMsgToSession_in_t__isset {
  _gate_broadcastMsgToSession_in_t__isset() : cmd(true), body(false) {}
  bool cmd;
  bool body;
} _gate_broadcastMsgToSession_in_t__isset;

class gate_broadcastMsgToSession_in_t {
 public:

  static const char* ascii_fingerprint; // = "15896F1A4438B1ECBB80CEA66AD0C4C5";
  static const uint8_t binary_fingerprint[16]; // = {0x15,0x89,0x6F,0x1A,0x44,0x38,0xB1,0xEC,0xBB,0x80,0xCE,0xA6,0x6A,0xD0,0xC4,0xC5};

  gate_broadcastMsgToSession_in_t() : cmd(0), body() {
  }

  virtual ~gate_broadcastMsgToSession_in_t() throw() {}

  int16_t cmd;
  std::string body;

  _gate_broadcastMsgToSession_in_t__isset __isset;

  void __set_cmd(const int16_t val) {
    cmd = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const gate_broadcastMsgToSession_in_t & rhs) const
  {
    if (!(cmd == rhs.cmd))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const gate_broadcastMsgToSession_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_broadcastMsgToSession_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_broadcastMsgToSession_in_t &a, gate_broadcastMsgToSession_in_t &b);


class gate_broadcastMsgToSession_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  gate_broadcastMsgToSession_out_t() {
  }

  virtual ~gate_broadcastMsgToSession_out_t() throw() {}


  bool operator == (const gate_broadcastMsgToSession_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const gate_broadcastMsgToSession_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const gate_broadcastMsgToSession_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(gate_broadcastMsgToSession_out_t &a, gate_broadcastMsgToSession_out_t &b);

typedef struct _worker_call_msg_in_t__isset {
  _worker_call_msg_in_t__isset() : cmd(true), body(false) {}
  bool cmd;
  bool body;
} _worker_call_msg_in_t__isset;

class worker_call_msg_in_t {
 public:

  static const char* ascii_fingerprint; // = "15896F1A4438B1ECBB80CEA66AD0C4C5";
  static const uint8_t binary_fingerprint[16]; // = {0x15,0x89,0x6F,0x1A,0x44,0x38,0xB1,0xEC,0xBB,0x80,0xCE,0xA6,0x6A,0xD0,0xC4,0xC5};

  worker_call_msg_in_t() : cmd(0), body() {
  }

  virtual ~worker_call_msg_in_t() throw() {}

  int16_t cmd;
  std::string body;

  _worker_call_msg_in_t__isset __isset;

  void __set_cmd(const int16_t val) {
    cmd = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const worker_call_msg_in_t & rhs) const
  {
    if (!(cmd == rhs.cmd))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const worker_call_msg_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const worker_call_msg_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(worker_call_msg_in_t &a, worker_call_msg_in_t &b);

typedef struct _worker_call_msg_out_t__isset {
  _worker_call_msg_out_t__isset() : err(false), msg_type(false), body(false) {}
  bool err;
  bool msg_type;
  bool body;
} _worker_call_msg_out_t__isset;

class worker_call_msg_out_t {
 public:

  static const char* ascii_fingerprint; // = "AB879940BD15B6B25691265F7384B271";
  static const uint8_t binary_fingerprint[16]; // = {0xAB,0x87,0x99,0x40,0xBD,0x15,0xB6,0xB2,0x56,0x91,0x26,0x5F,0x73,0x84,0xB2,0x71};

  worker_call_msg_out_t() : err(), msg_type(), body() {
  }

  virtual ~worker_call_msg_out_t() throw() {}

  std::string err;
  std::string msg_type;
  std::string body;

  _worker_call_msg_out_t__isset __isset;

  void __set_err(const std::string& val) {
    err = val;
  }

  void __set_msg_type(const std::string& val) {
    msg_type = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  bool operator == (const worker_call_msg_out_t & rhs) const
  {
    if (!(err == rhs.err))
      return false;
    if (!(msg_type == rhs.msg_type))
      return false;
    if (!(body == rhs.body))
      return false;
    return true;
  }
  bool operator != (const worker_call_msg_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const worker_call_msg_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(worker_call_msg_out_t &a, worker_call_msg_out_t &b);

typedef struct _broker_route_msg_in_t__isset {
  _broker_route_msg_in_t__isset() : dest_namespace(false), dest_service_name(false), dest_msg_name(false), dest_node_id(false), from_namespace(false), from_node_id(false), callback_id(false), body(false), err_info(false) {}
  bool dest_namespace;
  bool dest_service_name;
  bool dest_msg_name;
  bool dest_node_id;
  bool from_namespace;
  bool from_node_id;
  bool callback_id;
  bool body;
  bool err_info;
} _broker_route_msg_in_t__isset;

class broker_route_msg_in_t {
 public:

  static const char* ascii_fingerprint; // = "CBC652E4B6DDB69E997A960033ECD9B9";
  static const uint8_t binary_fingerprint[16]; // = {0xCB,0xC6,0x52,0xE4,0xB6,0xDD,0xB6,0x9E,0x99,0x7A,0x96,0x00,0x33,0xEC,0xD9,0xB9};

  broker_route_msg_in_t() : dest_namespace(), dest_service_name(), dest_msg_name(), dest_node_id(0), from_namespace(), from_node_id(0), callback_id(0), body(), err_info() {
  }

  virtual ~broker_route_msg_in_t() throw() {}

  std::string dest_namespace;
  std::string dest_service_name;
  std::string dest_msg_name;
  int64_t dest_node_id;
  std::string from_namespace;
  int64_t from_node_id;
  int64_t callback_id;
  std::string body;
  std::string err_info;

  _broker_route_msg_in_t__isset __isset;

  void __set_dest_namespace(const std::string& val) {
    dest_namespace = val;
  }

  void __set_dest_service_name(const std::string& val) {
    dest_service_name = val;
  }

  void __set_dest_msg_name(const std::string& val) {
    dest_msg_name = val;
  }

  void __set_dest_node_id(const int64_t val) {
    dest_node_id = val;
  }

  void __set_from_namespace(const std::string& val) {
    from_namespace = val;
  }

  void __set_from_node_id(const int64_t val) {
    from_node_id = val;
  }

  void __set_callback_id(const int64_t val) {
    callback_id = val;
  }

  void __set_body(const std::string& val) {
    body = val;
  }

  void __set_err_info(const std::string& val) {
    err_info = val;
  }

  bool operator == (const broker_route_msg_in_t & rhs) const
  {
    if (!(dest_namespace == rhs.dest_namespace))
      return false;
    if (!(dest_service_name == rhs.dest_service_name))
      return false;
    if (!(dest_msg_name == rhs.dest_msg_name))
      return false;
    if (!(dest_node_id == rhs.dest_node_id))
      return false;
    if (!(from_namespace == rhs.from_namespace))
      return false;
    if (!(from_node_id == rhs.from_node_id))
      return false;
    if (!(callback_id == rhs.callback_id))
      return false;
    if (!(body == rhs.body))
      return false;
    if (!(err_info == rhs.err_info))
      return false;
    return true;
  }
  bool operator != (const broker_route_msg_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const broker_route_msg_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(broker_route_msg_in_t &a, broker_route_msg_in_t &b);

typedef struct _register_to_broker_in_t__isset {
  _register_to_broker_in_t__isset() : node_type(false), host(false), service_name(false), node_id(false), reg_namespace(false), bind_broker_id(false) {}
  bool node_type;
  bool host;
  bool service_name;
  bool node_id;
  bool reg_namespace;
  bool bind_broker_id;
} _register_to_broker_in_t__isset;

class register_to_broker_in_t {
 public:

  static const char* ascii_fingerprint; // = "60E86BD78EA7B6197FFB17BCD59525EC";
  static const uint8_t binary_fingerprint[16]; // = {0x60,0xE8,0x6B,0xD7,0x8E,0xA7,0xB6,0x19,0x7F,0xFB,0x17,0xBC,0xD5,0x95,0x25,0xEC};

  register_to_broker_in_t() : node_type(0), host(), service_name(), node_id(0), reg_namespace(), bind_broker_id(0) {
  }

  virtual ~register_to_broker_in_t() throw() {}

  int32_t node_type;
  std::string host;
  std::string service_name;
  int64_t node_id;
  std::string reg_namespace;
  int64_t bind_broker_id;

  _register_to_broker_in_t__isset __isset;

  void __set_node_type(const int32_t val) {
    node_type = val;
  }

  void __set_host(const std::string& val) {
    host = val;
  }

  void __set_service_name(const std::string& val) {
    service_name = val;
  }

  void __set_node_id(const int64_t val) {
    node_id = val;
  }

  void __set_reg_namespace(const std::string& val) {
    reg_namespace = val;
  }

  void __set_bind_broker_id(const int64_t val) {
    bind_broker_id = val;
  }

  bool operator == (const register_to_broker_in_t & rhs) const
  {
    if (!(node_type == rhs.node_type))
      return false;
    if (!(host == rhs.host))
      return false;
    if (!(service_name == rhs.service_name))
      return false;
    if (!(node_id == rhs.node_id))
      return false;
    if (!(reg_namespace == rhs.reg_namespace))
      return false;
    if (!(bind_broker_id == rhs.bind_broker_id))
      return false;
    return true;
  }
  bool operator != (const register_to_broker_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const register_to_broker_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(register_to_broker_in_t &a, register_to_broker_in_t &b);

typedef struct _register_to_broker_out_t__isset {
  _register_to_broker_out_t__isset() : register_flag(false), node_id(false), service2node_id(false), slave_broker_data(false), rpc_bind_broker_info(false), reg_namespace_list(false) {}
  bool register_flag;
  bool node_id;
  bool service2node_id;
  bool slave_broker_data;
  bool rpc_bind_broker_info;
  bool reg_namespace_list;
} _register_to_broker_out_t__isset;

class register_to_broker_out_t {
 public:

  static const char* ascii_fingerprint; // = "08FF3A9C5042F50B54A30CA9AEF4E748";
  static const uint8_t binary_fingerprint[16]; // = {0x08,0xFF,0x3A,0x9C,0x50,0x42,0xF5,0x0B,0x54,0xA3,0x0C,0xA9,0xAE,0xF4,0xE7,0x48};

  register_to_broker_out_t() : register_flag(0), node_id(0) {
  }

  virtual ~register_to_broker_out_t() throw() {}

  int16_t register_flag;
  int64_t node_id;
  std::map<std::string, int64_t>  service2node_id;
  std::map<std::string, int64_t>  slave_broker_data;
  std::map<int64_t, int64_t>  rpc_bind_broker_info;
  std::vector<std::string>  reg_namespace_list;

  _register_to_broker_out_t__isset __isset;

  void __set_register_flag(const int16_t val) {
    register_flag = val;
  }

  void __set_node_id(const int64_t val) {
    node_id = val;
  }

  void __set_service2node_id(const std::map<std::string, int64_t> & val) {
    service2node_id = val;
  }

  void __set_slave_broker_data(const std::map<std::string, int64_t> & val) {
    slave_broker_data = val;
  }

  void __set_rpc_bind_broker_info(const std::map<int64_t, int64_t> & val) {
    rpc_bind_broker_info = val;
  }

  void __set_reg_namespace_list(const std::vector<std::string> & val) {
    reg_namespace_list = val;
  }

  bool operator == (const register_to_broker_out_t & rhs) const
  {
    if (!(register_flag == rhs.register_flag))
      return false;
    if (!(node_id == rhs.node_id))
      return false;
    if (!(service2node_id == rhs.service2node_id))
      return false;
    if (!(slave_broker_data == rhs.slave_broker_data))
      return false;
    if (!(rpc_bind_broker_info == rhs.rpc_bind_broker_info))
      return false;
    if (!(reg_namespace_list == rhs.reg_namespace_list))
      return false;
    return true;
  }
  bool operator != (const register_to_broker_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const register_to_broker_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(register_to_broker_out_t &a, register_to_broker_out_t &b);


class empty_ret_msg {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  empty_ret_msg() {
  }

  virtual ~empty_ret_msg() throw() {}


  bool operator == (const empty_ret_msg & /* rhs */) const
  {
    return true;
  }
  bool operator != (const empty_ret_msg &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const empty_ret_msg & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(empty_ret_msg &a, empty_ret_msg &b);

typedef struct _session_enter_worker_in_t__isset {
  _session_enter_worker_in_t__isset() : session_id(false), session_ip(false), from_gate(false), from_worker(false), to_worker(false), extra_data(false) {}
  bool session_id;
  bool session_ip;
  bool from_gate;
  bool from_worker;
  bool to_worker;
  bool extra_data;
} _session_enter_worker_in_t__isset;

class session_enter_worker_in_t {
 public:

  static const char* ascii_fingerprint; // = "1F10F993631B3ABD721D79EE58C2056E";
  static const uint8_t binary_fingerprint[16]; // = {0x1F,0x10,0xF9,0x93,0x63,0x1B,0x3A,0xBD,0x72,0x1D,0x79,0xEE,0x58,0xC2,0x05,0x6E};

  session_enter_worker_in_t() : session_id(0), session_ip(), from_gate(), from_worker(), to_worker(), extra_data() {
  }

  virtual ~session_enter_worker_in_t() throw() {}

  int64_t session_id;
  std::string session_ip;
  std::string from_gate;
  std::string from_worker;
  std::string to_worker;
  std::string extra_data;

  _session_enter_worker_in_t__isset __isset;

  void __set_session_id(const int64_t val) {
    session_id = val;
  }

  void __set_session_ip(const std::string& val) {
    session_ip = val;
  }

  void __set_from_gate(const std::string& val) {
    from_gate = val;
  }

  void __set_from_worker(const std::string& val) {
    from_worker = val;
  }

  void __set_to_worker(const std::string& val) {
    to_worker = val;
  }

  void __set_extra_data(const std::string& val) {
    extra_data = val;
  }

  bool operator == (const session_enter_worker_in_t & rhs) const
  {
    if (!(session_id == rhs.session_id))
      return false;
    if (!(session_ip == rhs.session_ip))
      return false;
    if (!(from_gate == rhs.from_gate))
      return false;
    if (!(from_worker == rhs.from_worker))
      return false;
    if (!(to_worker == rhs.to_worker))
      return false;
    if (!(extra_data == rhs.extra_data))
      return false;
    return true;
  }
  bool operator != (const session_enter_worker_in_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const session_enter_worker_in_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(session_enter_worker_in_t &a, session_enter_worker_in_t &b);


class session_enter_worker_out_t {
 public:

  static const char* ascii_fingerprint; // = "99914B932BD37A50B983C5E7C90AE93B";
  static const uint8_t binary_fingerprint[16]; // = {0x99,0x91,0x4B,0x93,0x2B,0xD3,0x7A,0x50,0xB9,0x83,0xC5,0xE7,0xC9,0x0A,0xE9,0x3B};

  session_enter_worker_out_t() {
  }

  virtual ~session_enter_worker_out_t() throw() {}


  bool operator == (const session_enter_worker_out_t & /* rhs */) const
  {
    return true;
  }
  bool operator != (const session_enter_worker_out_t &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const session_enter_worker_out_t & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(session_enter_worker_out_t &a, session_enter_worker_out_t &b);

} // namespace

#endif
