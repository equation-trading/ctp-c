#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void* CTP_TraderApi_CreateFtdcTraderApi(char* flow);

const char* CTP_TraderApi_GetApiVersion(void* traderApi);

void* CTP_TraderSpi_CreateFtdcTraderSpi(void* traderApi);

#ifdef __cplusplus
}
#endif
