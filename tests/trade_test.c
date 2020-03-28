#include "ctp-c.h"

#include <stdio.h>

#define BROKER_ID ""
#define USER_ID ""
#define AUTH_CODE ""
#define APP_ID ""
#define FRONT ""

#define TRADER_API(traderApi, apiName, ...) CTP_TraderApi_##apiName##(traderApi, __VA_ARGS__)
#define TRADER_SPI(traderSpi, apiName, ...) CTP_TraderSpi_##apiName##(traderSpi, __VA_ARGS__)

void OnFrontConnected(void* traderApi, void* traderSpi) {
  CThostFtdcReqAuthenticateField req = { 0 };

  printf("[ctp-c] OnFrontConnected, requesting auth: \n");

  strcpy(req.BrokerID, BROKER_ID);
  strcpy(req.UserID, USER_ID);
  strcpy(req.AuthCode, AUTH_CODE);
  strcpy(req.AppID, APP_ID);

  CTP_TraderApi_ReqAuthenticate(traderApi, &req);
}

int main() {
  void* traderApi = CTP_TraderApi_CreateFtdcTraderApi("./flow");

  printf("CTP API version: %s.\n", CTP_TraderApi_GetApiVersion(traderApi));
  
  void* traderSpi = CTP_TraderSpi_CreateFtdcTraderSpi(traderApi);
  CTP_TraderSpi_SetOnFrontConnectedCallBack(traderSpi, OnFrontConnected);

  CTP_TraderApi_SubscribePrivateTopic(traderApi, THOST_TERT_RESTART);
  CTP_TraderApi_SubscribePublicTopic(traderApi, THOST_TERT_RESTART);
  CTP_TraderApi_RegisterFront(traderApi, FRONT);

  return 0;
}