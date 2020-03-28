#pragma once

#include "ThostFtdcMdApi.h"
#include "CTPMdApi.hpp"

#define REGISTER_CALLBACK(callback, member)\
void Set##callback(callback##CallBack callback) {\
  member = callback;\
}

class CTPMdSpi : public CThostFtdcMdSpi {
public:
  CTPMdSpi(CTPMdApi* mdApi) : _api(mdApi) {}

  REGISTER_CALLBACK(OnFrontConnected, _onFrontConnected)
  void OnFrontConnected() {
    if (_onFrontConnected) {
      _onFrontConnected(_api, this);
    }
  }

  REGISTER_CALLBACK(OnFrontDisconnected, _onFrontDisconnected)
  void OnFrontDisconnected(int nReason) {
    if (_onFrontDisconnected) {
      _onFrontDisconnected(_api, this, nReason);
    }
  }

  REGISTER_CALLBACK(OnHeartBeatWarning, _onHeartBeatWarning)
  void OnHeartBeatWarning(int nTimeLapse) {
    if (_onHeartBeatWarning) {
      _onHeartBeatWarning(_api, this, nTimeLapse);
    }
  }

  REGISTER_CALLBACK(OnRspUserLogin, _onRspUserLogin)
  void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspUserLogin) {
      _onRspUserLogin(_api, this, pRspUserLogin, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspUserLogout, _onRspUserLogout)
  void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspUserLogout) {
      _onRspUserLogout(_api, this, pUserLogout, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspError, _onRspError)
  void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspError) {
      _onRspError(_api, this, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspSubMarketData, _onRspSubMarketData)
  void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspSubMarketData) {
      _onRspSubMarketData(_api, this, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspUnSubMarketData, _onRspUnSubMarketData)
  void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspUnSubMarketData) {
      _onRspUnSubMarketData(_api, this, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspSubForQuoteRsp, _onRspSubForQuoteRsp)
  void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspSubForQuoteRsp) {
      _onRspSubForQuoteRsp(_api, this, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRspUnSubForQuoteRsp, _onRspUnSubForQuoteRsp)
  void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (_onRspUnSubForQuoteRsp) {
      _onRspUnSubForQuoteRsp(_api, this, pSpecificInstrument, pRspInfo, nRequestID, bIsLast);
    }
  }

  REGISTER_CALLBACK(OnRtnDepthMarketData, _onRtnDepthMarketData)
  void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    if (_onRtnDepthMarketData) {
      _onRtnDepthMarketData(_api, this, pDepthMarketData);
    }
  }

  REGISTER_CALLBACK(OnRtnForQuoteRsp, _onRtnForQuoteRsp)
  void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
    if (_onRtnForQuoteRsp) {
      _onRtnForQuoteRsp(_api, this, pForQuoteRsp);
    }
  }

private:
  CTPMdApi* _api;

  OnFrontConnectedCallBack      _onFrontConnected;
  OnFrontDisconnectedCallBack   _onFrontDisconnected;
  OnHeartBeatWarningCallBack    _onHeartBeatWarning;
  OnRspUserLoginCallBack        _onRspUserLogin;
  OnRspUserLogoutCallBack       _onRspUserLogout;
  OnRspErrorCallBack            _onRspError;
  OnRspSubMarketDataCallBack    _onRspSubMarketData;
  OnRspUnSubMarketDataCallBack  _onRspUnSubMarketData;
  OnRspSubForQuoteRspCallBack   _onRspSubForQuoteRsp;
  OnRspUnSubForQuoteRspCallBack _onRspUnSubForQuoteRsp;
  OnRtnDepthMarketDataCallBack  _onRtnDepthMarketData;
  OnRtnForQuoteRspCallBack      _onRtnForQuoteRsp;
};
