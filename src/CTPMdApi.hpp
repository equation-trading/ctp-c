#pragma once

#include "ThostFtdcMdApi.h"

// class CTPMdSpi;

class CTPMdApi {
public:
  static CThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false, const bool bIsMulticast=false) {
    return CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath, bIsUsingUdp, bIsMulticast);
  }

  static const char *GetApiVersion() {
    return CThostFtdcMdApi::GetApiVersion();
  }

  CTPMdApi(CThostFtdcMdApi* api)
    : _api(api)
    , _requestId(0) {

    }

  void Release() {
    _api->Release();
  }

  void Init() {
    _api->Init();
  }

  int Join() {
    _api->Join();
  }

  const char *GetTradingDay() {
    return _api->GetTradingDay();
  }

  void RegisterFront(char *pszFrontAddress) {
    _api->RegisterFront(pszFrontAddress);
  }

  void RegisterNameServer(char *pszNsAddress) {
    _api->RegisterNameServer(pszNsAddress);
  }

  void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo) {
    _api->RegisterFensUserInfo(pFensUserInfo);
  }

  void RegisterSpi(CThostFtdcMdSpi *pSpi) {
    _api->RegisterSpi(pSpi);
  }

  int SubscribeMarketData(char *ppInstrumentID[], int nCount) {
    return _api->SubscribeMarketData(ppInstrumentID, nCount);
  }

  int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) {
    return _api->UnSubscribeMarketData(ppInstrumentID, nCount);
  }

  int SubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) {
    return _api->SubscribeForQuoteRsp(ppInstrumentID, nCount);
  }

  int UnSubscribeForQuoteRsp(char *ppInstrumentID[], int nCount) {
    return _api->UnSubscribeForQuoteRsp(ppInstrumentID, nCount);
  }

  int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField) {
    return _api->ReqUserLogin(pReqUserLoginField, _requestId++);
  }

  int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout) {
    return _api->ReqUserLogout(pUserLogout, _requestId++);
  }

protected:
	~CTPMdApi() { 
    // TODO: should I delete _api or not?
  }

  CThostFtdcMdApi* _api;
  int _requestId;
};