#pragma once

#include <string>
#include "zmq.hpp"

template<class MessageT>
class ZMQPublisher {
public:
  using MessageTPtr = std::shared_ptr<MessageT>;

  ZMQPublisher(const std::string& addr) :
    _addr(addr),
    _zmq_ctx(),
    _zmq_sock(_zmq_ctx, zmq::socket_type::pub) {
    _zmq_sock.bind(_addr.c_str());
  }

  void publish(MessageTPtr message) {
    _zmq_sock.send(message->bytes(), message->size(), ZMQ_DONTWAIT); // , zmq::send_flags::dontwait);
  }

private:
  const std::string _addr;

  zmq::context_t _zmq_ctx;
  zmq::socket_t _zmq_sock;
};
