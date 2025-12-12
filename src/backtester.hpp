#pragma once
#include <vector>
#include <string>      
#include "strategies.hpp"
using namespace std;

struct ExecTrade {
    int buyDay, sellDay;
    double buyPrice, sellPrice;
    int qty;
    double pnl;
};

struct StrategyResult {
    string strategyName;    
    int trades;
    double totalPnL;
    vector<ExecTrade> executedTrades;
    double finalCapital;
};

StrategyResult run_backtest_percent(const string& strategyName,
                                   const vector<double>& prices,
                                   const vector<TradeSignal>& plan,
                                   double initialCapital = 10000.0,
                                   double percentPerTrade = 0.10,
                                   double slippagePct = 0.001,
                                   double txnFee = 0.0,
                                   double stopLossPct = 0.0,
                                   double takeProfitPct = 0.0);
