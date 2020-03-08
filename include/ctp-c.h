#pragma once

#include ""

#ifdef __cplusplus
extern "C" {
#endif

void* CTP_TraderApi_CreateFtdcTraderApi(char*);

char* CTP_TraderApi_GetApiVersion();

void* CTP_TraderSpi_CreateFtdcTraderSpi(void* traderApi);

#ifdef __cplusplus
}
#endif
