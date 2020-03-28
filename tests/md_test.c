#include "ctp-c.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *g_broker_id;
char *g_front;
char *g_user_id;
char *g_password;

#define CTPD_MD_SPI_SET_CALLBACK(mdSpi, callback_name, callback) CTP_MdSpi_Set##callback_name(mdSpi, callback);

void OnFrontConnected(void* mdApi, void* mdSpi) {
  struct CThostFtdcReqUserLoginField req = { 0 };

  printf("[ctp-c] OnFrontConnected\n");
  strcpy(req.BrokerID, g_broker_id);
  strcpy(req.UserID, g_user_id);
  strcpy(req.Password, g_password);

  CTPC_MD_API(mdApi, ReqUserLogin, &req);
}

void OnRspError(void* mdApi, void* mdSpi, struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  printf("[ctp-c] OnRspError: ");
  if (pRspInfo) {
    printf("request id: %d, is last: %d, error id: %d\n", nRequestID, bIsLast, pRspInfo->ErrorID);
  }
}

void OnRspUserLogin(
  void* mdApi, void* mdSpi,
  struct CThostFtdcRspUserLoginField *pRspUserLogin,
  struct CThostFtdcRspInfoField *pRspInfo,
  int nRequestID, bool bIsLast
) {
  static char* instruments[] = { "IF2004" };

  printf("[ctp-c] OnRspUserLogin: ");
  if (pRspInfo) {
    printf("request id: %d, is last: %d, error id: %d\n", nRequestID, bIsLast, pRspInfo->ErrorID);
  }
  CTPC_MD_API(mdApi, SubscribeMarketData, instruments, 1);
}

void OnRspSubMarketData(
  void* mdApi, void* mdSpi,
  struct CThostFtdcSpecificInstrumentField *pSpecificInstrument,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  printf("[ctp-c] OnRspSubMarketData\n");
}

void OnRtnDepthMarketData(void* mdApi, void* mdSpi, struct CThostFtdcDepthMarketDataField *pDepthMarketData) {
  printf("[ctp-c] OnRtnDepthMarketData\n");
}

int main(int argc, char**argv) {
  if (argc != 5) {
    fprintf(stderr, "Usage: md_test <front> <broker> <user> <pass>\n");
    return -1;
  }

  g_front = argv[1];
  g_broker_id = argv[2];
  g_user_id = argv[3];
  g_password = argv[4];

  // CThostFtdcMdApi  *pUserMdApi =  CThostFtdcMdApi::CreateFtdcMdApi(".\\flow\\md");
  void* mdApi = CTP_MdApi_CreateFtdcMdApi("./flow", 0, 0);

  // CSimpleMdHandler ash(pUserMdApi);
  void* mdSpi = CTP_MdSpi_CreateMdSpi(mdApi);

  // Register callbacks
  CTPD_MD_SPI_SET_CALLBACK(mdSpi, OnFrontConnected, OnFrontConnected);
  CTPD_MD_SPI_SET_CALLBACK(mdSpi, OnRspError, OnRspError);
  CTPD_MD_SPI_SET_CALLBACK(mdSpi, OnRspUserLogin, OnRspUserLogin);
  CTPD_MD_SPI_SET_CALLBACK(mdSpi, OnRspSubMarketData, OnRspSubMarketData);
  CTPD_MD_SPI_SET_CALLBACK(mdSpi, OnRtnDepthMarketData, OnRtnDepthMarketData);

  // pUserMdApi->RegisterSpi(&ash);
  CTPC_MD_API(mdApi, RegisterSpi, mdSpi);

  // pUserMdApi->RegisterFront(const_cast<char *>(g_chFrontMdaddr.c_str()));
  CTPC_MD_API(mdApi, RegisterFront, g_front);

  // pUserMdApi->Init();
  CTPC_MD_API(mdApi, Init);

  // WaitForSingleObject(xinhao, INFINITE);
  // sh.ReqQryInstrument();//查询合约

  // WaitForSingleObject(xinhao, INFINITE);
  // ash.SubscribeMarketData();//订阅行情
  // pUserMdApi->Release();

  sleep(100);

  CTPC_MD_API(mdApi, Release);
  CTPC_MD_SPI(mdSpi, Release);

  return 0;
}