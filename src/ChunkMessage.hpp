#pragma once

#include <cstdint>
#include <cstring>

enum CTPMessageType {
  MessageTypeOnRtnOrder,
  MessageTypeOnRtnTrade,
  MessageTypeOnRspQryOrder,
  MessageTypeOnRspQryTrade,
  MessageTypeUnknown
};

// Chunk message is a message type consits of:
// - 4 bytes message type
// - 4 bytes message body size
// - body data
// - 4 bytes checksum
class ChunkMessage {
public:
  ChunkMessage(uint32_t message_type, const char* data, size_t n) :
    _message_type(message_type),
    _body_length(n),
    _checksum(0),
    _buf(::operator new(size())) {
    char* dst = reinterpret_cast<char*>(_buf);
    memcpy(dst, &_message_type, sizeof(_message_type));
    memcpy(dst + sizeof(_message_type), _body_length, sizeof(_body_length));
    memcpy(dst + sizeof(_message_type) + sizeof(_body_length), data, _body_length);
    memcpy(dst + sizeof(_message_type) + _body_length, &_checksum, sizeof(_checksum));
  }

  const void* bytes() { return _buf; }
  size_t size() { return sizeof(_message_type) + sizeof(body_length) + _body_length + sizeof(_checksum);  }

  ~ChunkMessage() { delete _buf;  }

private:
  uint32_t _message_type;
  size_t _body_length;
  const void* _data;
  uint32_t _checksum;

  void* _buf;
};
