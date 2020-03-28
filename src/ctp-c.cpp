#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>

#include "ctp-c.h"
#include "ThostFtdcUserApiDataType.h"

#include "ChunkMessage.hpp"
#include "ConcurrentQueuePublisher.hpp"

#include "CTPTraderApi.hpp"
#include "CTPTraderSpi.hpp"
#include "CTPMdApi.hpp"
#include "CTPMdSpi.hpp"

#define SET_MDSPI_CALLBACK(callbacktype)\
void CTP_MdSpi_Set##callbacktype(void* mdSpi, callbacktype##CallBack callback) {\
  static_cast<CTPMdSpi*>(mdSpi)->Set##callbacktype(callback);\
}

// Implement MD SPI callback
SET_MDSPI_CALLBACK(OnFrontConnected)
SET_MDSPI_CALLBACK(OnFrontDisconnected)
SET_MDSPI_CALLBACK(OnHeartBeatWarning)
SET_MDSPI_CALLBACK(OnRspUserLogin)
SET_MDSPI_CALLBACK(OnRspError)
SET_MDSPI_CALLBACK(OnRspSubMarketData)
SET_MDSPI_CALLBACK(OnRspUnSubMarketData)
SET_MDSPI_CALLBACK(OnRspSubForQuoteRsp)
SET_MDSPI_CALLBACK(OnRspUnSubForQuoteRsp)
SET_MDSPI_CALLBACK(OnRtnDepthMarketData)
SET_MDSPI_CALLBACK(OnRtnForQuoteRsp)

void* CTP_MdSpi_CreateMdSpi(void* mdApi) {
  return new CTPMdSpi(static_cast<CTPMdApi*>(mdApi));
}

void* CTP_MdSpi_Release(void* mdSpi) {
  delete static_cast<CTPMdSpi*>(mdSpi);
}

// Implement MD API
void* CTP_MdApi_CreateFtdcMdApi(const char *pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast) {
  return new CTPMdApi(
     CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast)
  );
}

void CTP_MdApi_Release(void* mdApi) {
  static_cast<CTPMdApi*>(mdApi)->Release();
}

void CTP_MdApi_Init(void* mdApi) {
  static_cast<CTPMdApi*>(mdApi)->Init();
}

void CTP_MdApi_Join(void* mdApi) {
  static_cast<CTPMdApi*>(mdApi)->Join();
}

void CTP_MdApi_GetTradingDay(void* mdApi) {
  static_cast<CTPMdApi*>(mdApi)->GetTradingDay();
}

void CTP_MdApi_RegisterFront(void* mdApi, char* pszFrontAddress) {
  static_cast<CTPMdApi*>(mdApi)->RegisterFront(pszFrontAddress);
}

void CTP_MdApi_RegisterNameServer(void* mdApi, char* pszNsAddress) {
  static_cast<CTPMdApi*>(mdApi)->RegisterNameServer(pszNsAddress);
}

void CTP_MdApi_RegisterFensUserInfo(void* mdApi, CThostFtdcFensUserInfoField * pFensUserInfo) {
  static_cast<CTPMdApi*>(mdApi)->RegisterFensUserInfo(pFensUserInfo);
}

void CTP_MdApi_RegisterSpi(void* mdApi, void* mdSpi) {
  static_cast<CTPMdApi*>(mdApi)->RegisterSpi(
    static_cast<CTPMdSpi*>(mdSpi)
  );
}

void CTP_MdApi_SubscribeMarketData(void* mdApi, char *ppInstrumentID[], int nCount) {
  static_cast<CTPMdApi*>(mdApi)->SubscribeMarketData(ppInstrumentID, nCount);
}

void CTP_MdApi_UnSubscribeMarketData(void* mdApi, char *ppInstrumentID[], int nCount) {
  static_cast<CTPMdApi*>(mdApi)->UnSubscribeMarketData(ppInstrumentID, nCount);
}

void CTP_MdApi_SubscribeForQuoteRsp(void* mdApi, char *ppInstrumentID[], int nCount) {
  static_cast<CTPMdApi*>(mdApi)->SubscribeForQuoteRsp(ppInstrumentID, nCount);
}

void CTP_MdApi_UnSubscribeForQuoteRsp(void* mdApi, char *ppInstrumentID[], int nCount) {
  static_cast<CTPMdApi*>(mdApi)->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
}

void CTP_MdApi_ReqUserLogin(void* mdApi, CThostFtdcReqUserLoginField *pReqUserLoginField) {
  static_cast<CTPMdApi*>(mdApi)->ReqUserLogin(pReqUserLoginField);
}

void CTP_MdApi_ReqUserLogout(void* mdApi, CThostFtdcUserLogoutField *pUserLogout) {
  static_cast<CTPMdApi*>(mdApi)->ReqUserLogout(pUserLogout);
}

// Implement Trader API related functions
void* CTP_TraderApi_CreateFtdcTraderApi(char* flowPath) {
  return CThostFtdcTraderApi::CreateFtdcTraderApi(flowPath);
}

const char* CTP_TraderApi_GetApiVersion(void* traderApi) {
  return static_cast<CTPTraderApi*>(traderApi)->GetApiVersion();
}

void CTP_TraderApi_RegisterSpi(void* traderApi, void* spi) {
  static_cast<CTPTraderApi*>(traderApi)->RegisterSpi(static_cast<CThostFtdcTraderSpi*>(spi));
}

void CTP_TraderApi_SubscribePrivateTopic(void* traderApi, enum THOST_TE_RESUME_TYPE resumeType) {
  static_cast<CTPTraderApi*>(traderApi)->SubscribePrivateTopic(resumeType);
}

void CTP_TraderApi_SubscribePublicTopic(void* traderApi, enum THOST_TE_RESUME_TYPE resumeType) {
  static_cast<CTPTraderApi*>(traderApi)->SubscribePublicTopic(resumeType);
}

void CTP_TraderApi_RegisterFront(void* traderApi, char* frontAddress) {
  static_cast<CTPTraderApi*>(traderApi)->RegisterFront(frontAddress);
}

void CTP_TraderApi_Init(void* traderApi) {
  static_cast<CTPTraderApi*>(traderApi)->Init();
}

void CTP_TraderApi_ReqAuthenticate(void* traderApi, CThostFtdcReqAuthenticateField* req) {
  static_cast<CTPTraderApi*>(traderApi)->ReqAuthenticate(req);
}

// Implement Trader spi realted functions.
void* CTP_TraderSpi_CreateFtdcTraderSpi(void* traderApi) {
  return new CTPTraderSpi(static_cast<CThostFtdcTraderApi*>(traderApi));
}

void* CTP_TraderSpi_OnFrontConnected(void* traderSpi, OnFrontConnectedCallBack callback) {
  static_cast<CTPTraderSpi*>(traderSpi)->SetOnFrontConnectedCallBack(callback);
}

/*
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
*/