#include <iostream>

#include "YahooAPIWrapper.h"

int main()
{
    const char* stock = "GOOG";
    YahooAPIWrapper yahoo;
    
    double bid = yahoo.GetBid(stock);
    double ask = yahoo.GetAsk(stock);
    const char* capi = yahoo.GetCapitalization(stock);
    
    const char** bidAskCapi = yahoo.GetValues(stock, "b3b2j1");
    
    std::cout << "Bid: " << bid << std::endl;
    std::cout << "Ask: " << ask << std::endl;
    std::cout << "Capi: " << capi << std::endl;
    
    std::cout << "BidAskCapi[0]: " << bidAskCapi[0] << std::endl;
    std::cout << "BidAskCapi[1]: " << bidAskCapi[1] << std::endl;
    std::cout << "BidAskCapi[2]: " << bidAskCapi[2] << std::endl;
}