#pragma once

#include "ThostFtdcUserApiStruct.h"

#define CTPC_TRADER_API(traderApi, apiName, ...) CTP_TraderApi_##apiName(traderApi, ##__VA_ARGS__)
#define CTPC_TRADER_SPI(traderSpi, apiName, ...) CTP_TraderSpi_##apiName(traderSpi, ##__VA_ARGS__)
#define CTPC_MD_API(traderApi, apiName, ...) CTP_MdApi_##apiName(traderApi, ##__VA_ARGS__)
#define CTPC_MD_SPI(traderSpi, apiName, ...) CTP_MdSpi_##apiName(traderSpi, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#else
#define bool int
#endif

// MD APIs
void* CTP_MdSpi_CreateMdSpi(void* mdApi);
void* CTP_MdSpi_Release(void* mdSpi);
void* CTP_MdApi_CreateFtdcMdApi(const char *pszFlowPath, const bool bIsUsingUdp, const bool bIsMulticast);
void CTP_MdApi_Release(void* mdApi);
void CTP_MdApi_Init(void* mdApi);
void CTP_MdApi_Join(void* mdApi);
void CTP_MdApi_GetTradingDay(void* mdApi);
void CTP_MdApi_RegisterFront(void* mdApi, char* pszFrontAddress);
void CTP_MdApi_RegisterNameServer(void* mdApi, char* pszNsAddress);
void CTP_MdApi_RegisterFensUserInfo(void* mdApi, struct CThostFtdcFensUserInfoField * pFensUserInfo);
void CTP_MdApi_RegisterSpi(void* mdApi, void* mdSpi);
void CTP_MdApi_SubscribeMarketData(void* mdApi, char *ppInstrumentID[], int nCount);
void CTP_MdApi_UnSubscribeMarketData(void* mdApi, char *ppInstrumentID[], int nCount);
void CTP_MdApi_SubscribeForQuoteRsp(void* mdApi, char *ppInstrumentID[], int nCount);
void CTP_MdApi_UnSubscribeForQuoteRsp(void* mdApi, char *ppInstrumentID[], int nCount);
void CTP_MdApi_ReqUserLogin(void* mdApi, struct CThostFtdcReqUserLoginField *pReqUserLoginField);
void CTP_MdApi_ReqUserLogout(void* mdApi, struct CThostFtdcUserLogoutField *pUserLogout);

// MD SPIs
typedef void (*OnFrontConnectedCallBack)(void* mdApi, void* mdSpi);
typedef void (*OnFrontDisconnectedCallBack)(void* mdApi, void* mdSpi, int nReason);
typedef void (*OnHeartBeatWarningCallBack)(void* mdApi, void* mdSpi, int nTimeLapse);
typedef void (*OnRspUserLoginCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcRspUserLoginField *pRspUserLogin,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast
);
typedef void (*OnRspUserLogoutCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcUserLogoutField *pUserLogout,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast
);
typedef void (*OnRspErrorCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef void (*OnRspSubMarketDataCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcSpecificInstrumentField *pSpecificInstrument,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef void (*OnRspUnSubMarketDataCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcSpecificInstrumentField *pSpecificInstrument,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef void (*OnRspSubForQuoteRspCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcSpecificInstrumentField *pSpecificInstrument,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef void (*OnRspUnSubForQuoteRspCallBack)(
  void* mdApi, void* mdSpi, struct CThostFtdcSpecificInstrumentField *pSpecificInstrument,
  struct CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
typedef void (*OnRtnDepthMarketDataCallBack)(void* mdApi, void* mdSpi,
  struct CThostFtdcDepthMarketDataField *pDepthMarketData);
typedef void (*OnRtnForQuoteRspCallBack)(void* mdApi, void* mdSpi, struct CThostFtdcForQuoteRspField *pForQuoteRsp);

void CTP_MdSpi_SetOnFrontConnected(void* mdSpi, OnFrontConnectedCallBack callback);
void CTP_MdSpi_SetOnFrontDisconnected(void* mdSpi, OnFrontDisconnectedCallBack callback);
void CTP_MdSpi_SetOnHeartBeatWarning(void* mdSpi, OnHeartBeatWarningCallBack callback);
void CTP_MdSpi_SetOnRspUserLogin(void* mdSpi, OnRspUserLoginCallBack callback);
void CTP_MdSpi_SetOnRspError(void* mdSpi, OnRspErrorCallBack callback);
void CTP_MdSpi_SetOnRspSubMarketData(void* mdSpi, OnRspSubMarketDataCallBack callback);
void CTP_MdSpi_SetOnRspUnSubMarketData(void* mdSpi, OnRspUnSubMarketDataCallBack callback);
void CTP_MdSpi_SetOnRspSubForQuoteRsp(void* mdSpi, OnRspSubForQuoteRspCallBack callback);
void CTP_MdSpi_SetOnRspUnSubForQuoteRsp(void* mdSpi, OnRspUnSubForQuoteRspCallBack callback);
void CTP_MdSpi_SetOnRtnDepthMarketData(void* mdSpi, OnRtnDepthMarketDataCallBack callback);
void CTP_MdSpi_SetOnRtnForQuoteRsp(void* mdSpi, OnRtnForQuoteRspCallBack callback);


// Trader APIs
void* CTP_TraderApi_CreateFtdcTraderApi(char* flow);
const char* CTP_TraderApi_GetApiVersion(void* traderApi);

// Trader SPIs.
void* CTP_TraderSpi_CreateFtdcTraderSpi(void* traderApi);

#ifdef __cplusplus
}
#endif
