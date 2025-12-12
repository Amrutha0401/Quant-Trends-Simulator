#include "strategies.hpp"
#include <cmath>
using namespace std;

// sma_strategy: buy when sma_short > sma_long, sell when sma_short < sma_long
vector<TradeSignal> sma_strategy(const vector<Price>& prices, const vector<double>& sma_short, const vector<double>& sma_long){
    vector<TradeSignal> trades;
    int n = prices.size();
    bool holding=false; int buyIdx=-1;
    for(int i=0;i<n;i++){
        if(std::isnan(sma_short[i]) || std::isnan(sma_long[i])) continue;
        if(!holding && sma_short[i] > sma_long[i]) { holding=true; buyIdx=i; }
        else if(holding && sma_short[i] < sma_long[i]) { holding=false; trades.push_back({buyIdx,i}); buyIdx=-1; }
    }
    if(holding) trades.push_back({buyIdx,n-1});
    return trades;
}

vector<TradeSignal> ema_strategy(const vector<Price>& prices, const vector<double>& ema_short, const vector<double>& ema_long){
    // identical logic to sma but uses ema arrays
    vector<TradeSignal> trades;
    int n = prices.size();
    bool holding=false; int buyIdx=-1;
    for(int i=0;i<n;i++){
        if(std::isnan(ema_short[i]) || std::isnan(ema_long[i])) continue;
        if(!holding && ema_short[i] > ema_long[i]) { holding=true; buyIdx=i; }
        else if(holding && ema_short[i] < ema_long[i]) { holding=false; trades.push_back({buyIdx,i}); buyIdx=-1; }
    }
    if(holding) trades.push_back({buyIdx,n-1});
    return trades;
}

// rsi_strategy: buy when rsi > 50 AND price > sma_short ; sell when rsi < 50 or price < sma_short
vector<TradeSignal> rsi_strategy(const vector<Price>& prices, const vector<double>& sma_short, const vector<double>& rsi14){
    vector<TradeSignal> trades;
    int n = prices.size();
    bool holding=false; int buyIdx=-1;
    for(int i=0;i<n;i++){
        if(std::isnan(rsi14[i]) || std::isnan(sma_short[i])) continue;
        if(!holding && rsi14[i] > 50.0 && prices[i] > sma_short[i]) { holding=true; buyIdx=i; }
        else if(holding && (rsi14[i] < 50.0 || prices[i] < sma_short[i])) { holding=false; trades.push_back({buyIdx,i}); buyIdx=-1; }
    }
    if(holding) trades.push_back({buyIdx,n-1});
    return trades;
}
