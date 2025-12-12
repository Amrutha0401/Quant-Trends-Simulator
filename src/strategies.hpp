#pragma once
#include <vector>
using namespace std;
using Price = double;

struct TradeSignal {
    int buyDay;
    int sellDay;
};

vector<TradeSignal> sma_strategy(const vector<Price>& prices, const vector<double>& sma_short, const vector<double>& sma_long);
vector<TradeSignal> ema_strategy(const vector<Price>& prices, const vector<double>& ema_short, const vector<double>& ema_long);
vector<TradeSignal> rsi_strategy(const vector<Price>& prices, const vector<double>& sma_short, const vector<double>& rsi14);
