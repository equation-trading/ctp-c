#pragma once

#include "ThostFtdcTraderApi.h"

// Same interface with CThostFtdcTraderApi without requestId in params.
class CTPTraderApi {
public:
  static CThostFtdcTraderApi* CreateFtdcTraderApi(const char *pszFlowPath) {
      return CThostFtdcTraderApi::CreateFtdcTraderApi();
  }

  CTPTraderApi(CThostFtdcTraderApi* api)
    : _api(api),
      _requestId(0) {

  }

  virtual const char* GetApiVersion() {
      return _api->GetApiVersion();
  }

  virtual void Release() { _api->Release(); }
  
  virtual void Init() { _api->Init(); }
  
  virtual int Join() { return _api->Join(); }
  
  virtual const char *GetTradingDay() { return _api->GetTradingDay(); }
  
  virtual void RegisterFront(char *pszFrontAddress) { _api->RegisterFront(pszFrontAddress); }
  
  virtual void RegisterNameServer(char *pszNsAddress) { _api->RegisterNameServer(pszNsAddress); }
  
  virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo) {
    _api->RegisterFensUserInfo(pFensUserInfo);
  }
  
  virtual void RegisterSpi(CThostFtdcTraderSpi *pSpi) {
    _api->RegisterSpi(pSpi);
  }
  
  virtual void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType) {
    _api->SubscribePrivateTopic(nResumeType);
  }
  
  virtual void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType) {
    _api->SubscribePublicTopic(nResumeType);
  }

  virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField) {
    return _api->ReqAuthenticate(pReqAuthenticateField, _requestId++);
  }

  virtual int RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {
    return _api->RegisterUserSystemInfo(pUserSystemInfo);
  }

  virtual int SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo) {
    return _api->SubmitUserSystemInfo(pUserSystemInfo);
  }

  virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField) {
    return _api->ReqUserLogin(pReqUserLoginField, _requestId++);
  }

  virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout) {
    return _api->ReqUserLogout(pUserLogout, _requestId++);
  }

  virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate) {
    return _api->ReqUserPasswordUpdate(pUserPasswordUpdate, _requestId++);
  }

  virtual int ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate) {
    return _api->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, _requestId++);
  }

  virtual int ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField *pReqUserAuthMethod) {
    return _api->ReqUserAuthMethod(pReqUserAuthMethod, _requestId++);
  }

  virtual int ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha) {
    return _api->ReqGenUserCaptcha(pReqGenUserCaptcha, _requestId++);
  }

  virtual int ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText) {
    return _api->ReqGenUserText(pReqGenUserText, _requestId++);
  }

  virtual int ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha) {
    return _api->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, _requestId++);
  }

  virtual int ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText) {
    return _api->ReqUserLoginWithText(pReqUserLoginWithText, _requestId++);
  }

  virtual int ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP) {
    return _api->ReqUserLoginWithOTP(pReqUserLoginWithOTP, _requestId++);
  }

  virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder) {
    return _api->ReqOrderInsert(pInputOrder, _requestId++);
  }

  virtual int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder) {
    return _api->ReqParkedOrderInsert(pParkedOrder, _requestId++);
  }

  virtual int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction) {
    return _api->ReqParkedOrderAction(pParkedOrderAction, _requestId++);
  }

  virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction) {
    return _api->ReqOrderAction(pInputOrderAction, _requestId++);
  }

  virtual int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume) {
    return _api->ReqQueryMaxOrderVolume(pQueryMaxOrderVolume, _requestId++);
  }

  virtual int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm) {
    return _api->ReqSettlementInfoConfirm(pSettlementInfoConfirm, _requestId++);
  }

  virtual int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder) {
    return _api->ReqRemoveParkedOrder(pRemoveParkedOrder, _requestId++);
  }

  virtual int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction) {
    return _api->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, _requestId++);
  }

  virtual int ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder) {
    return _api->ReqExecOrderInsert(pInputExecOrder, _requestId++);
  }

  virtual int ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction) {
    return _api->ReqExecOrderAction(pInputExecOrderAction, _requestId++);
  }

  virtual int ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote) {
    return _api->ReqForQuoteInsert(pInputForQuote, _requestId++);
  }

  virtual int ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote) {
    return _api->ReqQuoteInsert(pInputQuote, _requestId++);
  }

  virtual int ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction) {
    return _api->ReqQuoteAction(pInputQuoteAction, _requestId++);
  }

  virtual int ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction) {
    return _api->ReqBatchOrderAction(pInputBatchOrderAction, _requestId++);
  }

  virtual int ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose) {
    return _api->ReqOptionSelfCloseInsert(pInputOptionSelfClose, _requestId++);
  }

  virtual int ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction) {
    return _api->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, _requestId++);
  }

  virtual int ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction) {
    return _api->ReqCombActionInsert(pInputCombAction, _requestId++);
  }

  virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder) {
    return _api->ReqQryOrder(pQryOrder, _requestId++);
  }

  virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade) {
    return _api->ReqQryTrade(pQryTrade, _requestId++);
  }

  virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition) {
    return _api->ReqQryInvestorPosition(pQryInvestorPosition, _requestId++);
  }

  virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount) {
    return _api->ReqQryTradingAccount(pQryTradingAccount, _requestId++);
  }

  virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor) {
    return _api->ReqQryInvestor(pQryInvestor, _requestId++);
  }

  virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode) {
    return _api->ReqQryTradingCode(pQryTradingCode, _requestId++);
  }

  virtual int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate) {
    return _api->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, _requestId++);
  }

  virtual int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate) {
    return _api->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, _requestId++);
  }

  virtual int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange) {
    return _api->ReqQryExchange(pQryExchange, _requestId++);
  }

  virtual int ReqQryProduct(CThostFtdcQryProductField *pQryProduct) {
    return _api->ReqQryProduct(pQryProduct, _requestId++);
  }

  virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument) {
    return _api->ReqQryInstrument(pQryInstrument, _requestId++);
  }

  virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData) {
    return _api->ReqQryDepthMarketData(pQryDepthMarketData, _requestId++);
  }

  virtual int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo) {
    return _api->ReqQrySettlementInfo(pQrySettlementInfo, _requestId++);
  }

  virtual int ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank) {
    return _api->ReqQryTransferBank(pQryTransferBank, _requestId++);
  }

  virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail) {
    return _api->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, _requestId++);
  }

  virtual int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice) {
    return _api->ReqQryNotice(pQryNotice, _requestId++);
  }

  virtual int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm) {
    return _api->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, _requestId++);
  }

  virtual int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail) {
    return _api->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, _requestId++);
  }

  virtual int ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey) {
    return _api->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, _requestId++);
  }

  virtual int ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset) {
    return _api->ReqQryEWarrantOffset(pQryEWarrantOffset, _requestId++);
  }

  virtual int ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin) {
    return _api->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, _requestId++);
  }

  virtual int ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate) {
    return _api->ReqQryExchangeMarginRate(pQryExchangeMarginRate, _requestId++);
  }

  virtual int ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust) {
    return _api->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, _requestId++);
  }

  virtual int ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate) {
    return _api->ReqQryExchangeRate(pQryExchangeRate, _requestId++);
  }

  virtual int ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap) {
    return _api->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, _requestId++);
  }

  virtual int ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate) {
    return _api->ReqQryProductExchRate(pQryProductExchRate, _requestId++);
  }

  virtual int ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup) {
    return _api->ReqQryProductGroup(pQryProductGroup, _requestId++);
  }

  virtual int ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate) {
    return _api->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, _requestId++);
  }

  virtual int ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate) {
    return _api->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, _requestId++);
  }

  virtual int ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate) {
    return _api->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, _requestId++);
  }

  virtual int ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount) {
    return _api->ReqQrySecAgentTradingAccount(pQryTradingAccount, _requestId++);
  }

  virtual int ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode) {
    return _api->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, _requestId++);
  }

  virtual int ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField *pQrySecAgentTradeInfo) {
    return _api->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, _requestId++);
  }

  virtual int ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost) {
    return _api->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, _requestId++);
  }

  virtual int ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate) {
    return _api->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, _requestId++);
  }

  virtual int ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder) {
    return _api->ReqQryExecOrder(pQryExecOrder, _requestId++);
  }

  virtual int ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote) {
    return _api->ReqQryForQuote(pQryForQuote, _requestId++);
  }

  virtual int ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote) {
    return _api->ReqQryQuote(pQryQuote, _requestId++);
  }

  virtual int ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose) {
    return _api->ReqQryOptionSelfClose(pQryOptionSelfClose, _requestId++);
  }

  virtual int ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit) {
    return _api->ReqQryInvestUnit(pQryInvestUnit, _requestId++);
  }

  virtual int ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard) {
    return _api->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, _requestId++);
  }

  virtual int ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction) {
    return _api->ReqQryCombAction(pQryCombAction, _requestId++);
  }

  virtual int ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial) {
    return _api->ReqQryTransferSerial(pQryTransferSerial, _requestId++);
  }

  virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister) {
    return _api->ReqQryAccountregister(pQryAccountregister, _requestId++);
  }

  virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank) {
    return _api->ReqQryContractBank(pQryContractBank, _requestId++);
  }

  virtual int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder) {
    return _api->ReqQryParkedOrder(pQryParkedOrder, _requestId++);
  }

  virtual int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction) {
    return _api->ReqQryParkedOrderAction(pQryParkedOrderAction, _requestId++);
  }

  virtual int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice) {
    return _api->ReqQryTradingNotice(pQryTradingNotice, _requestId++);
  }

  virtual int ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams) {
    return _api->ReqQryBrokerTradingParams(pQryBrokerTradingParams, _requestId++);
  }

  virtual int ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos) {
    return _api->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, _requestId++);
  }

  virtual int ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken) {
    return _api->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, _requestId++);
  }

  virtual int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer) {
    return _api->ReqFromBankToFutureByFuture(pReqTransfer, _requestId++);
  }

  virtual int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer) {
    return _api->ReqFromFutureToBankByFuture(pReqTransfer, _requestId++);
  }

  virtual int ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount) {
    return _api->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, _requestId++);
  }

protected:
  ~CTPTraderApi() { }

  CThostFtdcTraderApi* _api;
  int _requestId;
};