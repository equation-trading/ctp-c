#pragma once

#include <unistd.h>
#include <iostream>

#include "ThostFtdcTraderApi.h"

/*
template <class PublisherT, class MessageT>
class CTPTradeHandler : public CThostFtdcTraderSpi {
public:
  CTPTradeHandler(CThostFtdcTraderApi *api,
                  AccountInfo& acct,
                  std::shared_ptr<PublisherT> publisher) :
    _api(api),
    _acct(acct),
    _publisher(publisher),
    _requestID(0) {
    api->RegisterSpi(this);
    // Transmit messages from start of day. Be aware this could cause some issue
    // TODO think a better idea like if crash restart use restart or else quick
    api->SubscribePrivateTopic(THOST_TERT_RESTART);
    api->SubscribePublicTopic(THOST_TERT_RESTART);
    api->RegisterFront(const_cast<char *>(acct.front.c_str()));
    api->Init();
  }

  bool loggedout() { return _loggedout; }

  void OnFrontConnected() {
    if (!loggedout()) {
      std::cout << "Connected to frontend: " << _acct.front << std::endl;
      ReqAuthenticate();
    }
  }

  void ReqAuthenticate()
  {
    CThostFtdcReqAuthenticateField a = { 0 };
    strcpy(a.BrokerID, _acct.broker.c_str());
    strcpy(a.UserID, _acct.investor.c_str());
    strcpy(a.AuthCode, _acct.authcode.c_str()); // "96MCMFMJA84Z86WL");
    strcpy(a.AppID, _acct.appid.c_str()); // "client_cts_1.0.0");
    std::cout << "ReqAuthenticate " << _api->ReqAuthenticate(&a, _requestID++) << std::endl;
  }

  void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo,
    int nRequestID, bool bIsLast) {
    std::cout << "OnRspAuthenticate " << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << std::endl;

    ReqUserLogin();
  }

  void ReqUserLogin() {
    CThostFtdcReqUserLoginField reqUserLogin = { 0 };
    strcpy(reqUserLogin.BrokerID, _acct.broker.c_str());
    strcpy(reqUserLogin.UserID, _acct.investor.c_str());
    strcpy(reqUserLogin.Password, _acct.password.c_str());
    std::cout << "ReqUserLogin[" << reqUserLogin.BrokerID << ", "
              << reqUserLogin.UserID << ", "
              << reqUserLogin.Password << ", "
              << _acct.exchange <<"] " << _api->ReqUserLogin(&reqUserLogin, _requestID++) << std::endl;
  }

  void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                      CThostFtdcRspInfoField *pRspInfo,
                      int nRequestID,
                      bool bIsLast) {
    if (pRspInfo->ErrorID != 0) {
      std::cout << "\tFailed to login, ErrorID=[" << pRspInfo->ErrorID << "]\n"
                << " \tErrorMsg=[" << pRspInfo->ErrorMsg << "]\n \tRequestID = ["
                << nRequestID << "]\n \tchain = [" << bIsLast << "]\n";
      exit(-1);
    }
  }

  void ReqUserLogout() {
    std::cout << "Logging out..." << std::endl;

    _loggedout = true;

    CThostFtdcUserLogoutField a = { 0 };
    strcpy(a.BrokerID, _acct.broker.c_str());
    strcpy(a.UserID, _acct.investor.c_str());
    _api->ReqUserLogout(&a, _requestID++);
  }

  void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                       CThostFtdcRspInfoField *pRspInfo,
                       int nRequestID,
                       bool bIsLast) {

    if (pUserLogout) {
      std::cout << "Logged out" << std::endl;
    }
  }

  void ReqQryOrder(const std::string& startDate = {}, const std::string& endDate = {}) {
    CThostFtdcQryOrderField a = { 0 };
    strcpy(a.BrokerID, _acct.broker.c_str());
    strcpy(a.InvestorID, _acct.investor.c_str());
    strcpy(a.ExchangeID, _acct.exchange.c_str());

    if (!startDate.empty()) {
      strcpy(a.InsertTimeStart, startDate.c_str());
    }

    if (!endDate.empty()) {
      strcpy(a.InsertTimeEnd, endDate.c_str());
    }

    int ab = _api->ReqQryOrder(&a, _requestID++);
    std::cout << ((ab == 0) ? "ReqQryOrder sent code: " : "ReqQryOrder failed error code: ") << ab << std::endl;
  }

  void ReqQryTrade(const std::string& startDate = {}, const std::string& endDate = {}) {
    CThostFtdcQryTradeField a = { 0 };
    strcpy(a.BrokerID, _acct.broker.c_str());
    strcpy(a.InvestorID, _acct.investor.c_str());
    strcpy(a.ExchangeID, _acct.exchange.c_str());

    if (!startDate.empty()) {
      strcpy(a.TradeTimeStart, startDate.c_str());
    }

    if (!endDate.empty()) {
      strcpy(a.TradeTimeEnd, endDate.c_str());
    }

    int b = _api->ReqQryTrade(&a, _requestID++);
    std::cout << ((b == 0) ? "ReqQryTrade sent code:" : "ReqQryTrade failed error code: ") << b << std::endl;
  }

  void OnRtnOrder(CThostFtdcOrderField *pOrder) {
    if (pOrder) {
      if (strcmp(pOrder->InvestorID, _acct.investor.c_str()) != 0) {
        return;
      }

      std::cout << "OnRtnOrder: " << "InstrumentID[" << pOrder->InstrumentID << "], "
                << "VolumeTotalOriginal[" << pOrder->VolumeTotalOriginal << "], "
                << "VolumeTraded[" << pOrder->VolumeTraded << "], "
                << "VolumeTotal[" << pOrder->VolumeTotal << "], "
                << "OrderLocalID[" << pOrder->OrderLocalID << "], "
                << "OrderSysID[" << pOrder->OrderSysID << "]"
                << "OrderStatus[" << pOrder->OrderStatus << "]" << std::endl;

      auto message = new MessageT(MessageTypeOnRtnOrder, reinterpret_cast<char*>(pOrder), sizeof(CThostFtdcOrderField));
      _publisher->publish(message);
    }

    // std::cout << "OnRtnOrder: " << pOrder->OrderStatus << std::endl;
    // if (pOrder->OrderStatus == THOST_FTDC_OST_AllTraded) { // 全部成交
    // if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedQueueing)///部分成交还在队列中
    // if (pOrder->OrderStatus == THOST_FTDC_OST_PartTradedNotQueueing)///部分成交不在队列中
    // if (pOrder->OrderStatus == THOST_FTDC_OST_NoTradeQueueing)///未成交还在队列中
    // if (pOrder->OrderStatus == THOST_FTDC_OST_NoTradeNotQueueing)///未成交不在队列中
    // if (pOrder->OrderStatus == THOST_FTDC_OST_Canceled)///撤单
    // if (pOrder->OrderStatus == THOST_FTDC_OST_Unknown)///未知
    // if (pOrder->OrderStatus == THOST_FTDC_OST_NotTouched)///尚未触发
    // if (pOrder->OrderStatus == THOST_FTDC_OST_Touched)///已触发
  }

  void OnRtnTrade(CThostFtdcTradeField *pTrade) {
    if (pTrade) {
      if (strcmp(pTrade->InvestorID, _acct.investor.c_str()) != 0) {
        return;
      }

      std::cout << "OnRtnTrade: " << "InstrumentID[" << pTrade->InstrumentID << "], "
                << "OrderLocalID[" << pTrade->OrderLocalID << "], "
                << "OrderSysID[" << pTrade->OrderSysID << "], "
                << "Direction[" << pTrade->Direction << "], "
                << "Volume[" << pTrade->Volume << "], "
                << "Price[" << pTrade->Price << "]" << std::endl;

      auto message = new MessageT(MessageTypeOnRtnTrade, reinterpret_cast<char*>(pTrade), sizeof(CThostFtdcTradeField));
      _publisher->publish(message);
    }
  }

  void OnRspQryOrder(CThostFtdcOrderField *pOrder,
                     CThostFtdcRspInfoField *pRspInfo,
                     int nRequestID,
                     bool bIsLast) {

    if (pOrder) {
      std::cout << "OnRspQryOrder: " << "InstrumentID[" << pOrder->InstrumentID << "], "
                << "VolumeTotalOriginal[" << pOrder->VolumeTotalOriginal << "], "
                << "VolumeTraded[" << pOrder->VolumeTraded << "], "
                << "VolumeTotal[" << pOrder->VolumeTotal << "], "
                << "OrderLocalID[" << pOrder->OrderLocalID << "], "
                << "OrderSysID[" << pOrder->OrderSysID << "]" << std::endl;

      auto message = new MessageT(MessageTypeOnRspQryOrder, reinterpret_cast<char*>(pOrder), sizeof(CThostFtdcOrderField));
      _publisher->publish(message);
    } else {
      std::cout << "OnRspQryOrder: Empty order." << std::endl;
    }

    if (pRspInfo) {
      std::cout << "OnRspQryOrder: " << "ErrorMsg[" << pRspInfo->ErrorMsg << "], "
                << "ErrorID[" << pRspInfo->ErrorID << "]" << std::endl;
    }

    if (bIsLast) {
      std::cout << "OnRspQryOrder done." << std::endl;
    }
  }

  void OnRspQryTrade(CThostFtdcTradeField *pTrade,
                     CThostFtdcRspInfoField *pRspInfo,
                     int nRequestID,
                     bool bIsLast) {
    if (pTrade) {
      std::cout << "OnRspQryTrade: " << "InstrumentID[" << pTrade->InstrumentID << "], "
                << "OrderLocalID[" << pTrade->OrderLocalID << "], "
                << "OrderSysID[" << pTrade->OrderSysID << "], "
                << "Direction[" << pTrade->Direction << "], "
                << "Volume[" << pTrade->Volume << "], "
                << "Price[" << pTrade->Price << "]" << std::endl;
      auto message = new MessageT(MessageTypeOnRspQryTrade, reinterpret_cast<char*>(pTrade), sizeof(CThostFtdcTradeField));
      _publisher->publish(message);

    } else {
      std::cout << "OnRspQryTrade: Empty trade." << std::endl;
    }

    if (pRspInfo) {
      std::cout << "OnRspQryTrade: " << "ErrorMsg[" << pRspInfo->ErrorMsg << "], "
                << "ErrorID[" << pRspInfo->ErrorID << "]" << std::endl;
    }

    if (bIsLast) {
      std::cout << "OnRspQryTrade done." << std::endl;
    }
  }


private:
  bool _loggedout;
  int _requestID;
  AccountInfo _acct;
  CThostFtdcTraderApi* _api;
  std::shared_ptr<PublisherT> _publisher;
};

*/