#include "backtester.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

// percent sizing backtester: buys floor((capital*percent)/price) shares
StrategyResult run_backtest_percent(const string& strategyName,
                                   const vector<Price>& prices,
                                   const vector<TradeSignal>& plan,
                                   double initialCapital,
                                   double percentPerTrade,
                                   double slippagePct,
                                   double txnFee,
                                   double stopLossPct,
                                   double takeProfitPct)
{
    StrategyResult res;
    res.strategyName = strategyName;
    res.totalPnL = 0.0;
    res.trades = 0;
    res.finalCapital = initialCapital;
    double cash = initialCapital;

    for(auto &t : plan){
        int b = t.buyDay; int s = t.sellDay;
        if(b<0 || s<=b || b>=prices.size() || s>=prices.size()) continue;

        double entryPrice = prices[b] * (1.0 + slippagePct);
        int qty = max(0, (int)floor((cash * percentPerTrade) / entryPrice));
        if(qty == 0) continue;

        // simulate holding day by day to allow stop/take checks
        double buyPrice = entryPrice;
        double sellPrice = prices[s] * (1.0 - slippagePct);
        bool closed=false;
        for(int d=b+1; d<=s; ++d){
            double midPrice = prices[d];
            if(stopLossPct>0){
                if((midPrice - buyPrice)/buyPrice <= -stopLossPct){
                    sellPrice = midPrice * (1.0 - slippagePct);
                    closed=true; break;
                }
            }
            if(takeProfitPct>0){
                if((midPrice - buyPrice)/buyPrice >= takeProfitPct){
                    sellPrice = midPrice * (1.0 - slippagePct);
                    closed=true; break;
                }
            }
        }
        double pnl = (sellPrice - buyPrice) * qty - txnFee;
        cash += pnl; // add PnL to cash
        res.totalPnL += pnl;
        res.executedTrades.push_back({b,s,buyPrice,sellPrice,qty,pnl});
        res.trades++;
    }
    res.finalCapital = cash;
    return res;
}
