#include "ctp-c.h"

#include <stdio.h>

int main() {
  void* traderApi = CTP_TraderApi_CreateFtdcTraderApi("./flow");

  printf("CTP API version: %s.\n", CTP_TraderApi_GetApiVersion(traderApi));
  
  void* traderSpi = CTP_TraderSpi_CreateFtdcTraderSpi(traderApi);

  return 0;
}