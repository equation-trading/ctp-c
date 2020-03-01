#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>

#include "ThostFtdcUserApiDataType.h"

#include "ChunkMessage.hpp"
#include "ConcurrentQueuePublisher.hpp"
#include "CTPTradeHandler.hpp"

bool g_quit = false;


using CQChunkMessageCTPHandler = CTPTradeHandler<ConcurrentQueuePublisher<ChunkMessage>, ChunkMessage>;
using CQChunkMessage = tbb::concurrent_queue<ChunkMessage*>;

std::shared_ptr<CQChunkMessageCTPHandler> spawnCTPTradeHandlers(AccountInfo& acct, CQChunkMessage& queue) {
  std::cout << "Spawning CTP handler for account: " << acct.investor << std::endl;
  // TODO move it inside handler.
  CThostFtdcTraderApi *pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();
  auto publisher = std::make_shared<ConcurrentQueuePublisher<ChunkMessage>>(queue);
  return std::make_shared<CQChunkMessageCTPHandler>(pUserApi, acct, publisher);
}

int main(int argc, char** argv) {
  signal(SIGINT, sigint);

  std::string config_file;
  std::string publisher_addr;

  int opt;
  std::cout << "Parsing arg" << std::endl;
  while ((opt = getopt(argc, argv, "c:p:")) != -1) {
    switch(opt) {
    case 'c':
    std::cout << optarg << std::endl;
      config_file.append(optarg);
      break;
    case 'p':
    std::cout << optarg << std::endl;
      publisher_addr.append(optarg);
      break;
    default:
      break;
    }
  }

  if (config_file.empty()) {
    std::cerr << "Usage: ctpd -c config.json [-p tcp://*:1234]" << std::endl;;
    return -1;
  }

  std::cout << "Reading config file " << config_file << std::endl;
  // Read config file
  std::ifstream config_stream(config_file);
  std::string configStr((std::istreambuf_iterator<char>(config_stream)),
                        std::istreambuf_iterator<char>());
  std::cout << "Read config: " << configStr << std::endl;
  auto config = parseConfig(configStr);
  // Init zmq publisher
  zmq::context_t context;
  zmq::socket_t publisher(context, ZMQ_PUSH);
  publisher.bind(publisher_addr);
  std::cout << "ZMQ bind to " << publisher_addr << std::endl;

  // Spawn CTPs
  std::vector<std::shared_ptr<CQChunkMessageCTPHandler>> handlers;
  CQChunkMessage queue;
  for (auto& iter : config.accounts) {
    auto& accountInfo = iter.second;
    auto handler = spawnCTPTradeHandlers(accountInfo, queue);
    handlers.push_back(handler);
  }

  
  while (!g_quit) {
    ChunkMessage* message;
    int i = 0;
    while (queue.try_pop(message)) {
      // send the message out to zmq.
      zmq::message_t msg(message->size());
      memcpy(msg.data(), static_cast<const char*>(message->bytes()), message->size());
      publisher.send(msg, zmq::send_flags::none); // block
      delete message; // Hmmmmmm
    }
  }

  for (auto handler : handlers) {
    handler->ReqUserLogout();
  }

  // TODO: Then delete these handlers
  sleep(3);

  return 0;
}
