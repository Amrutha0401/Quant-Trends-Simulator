#include "dp_strategy.hpp"
#include <vector>
#include <cmath>
using namespace std;

TradePlan runDPStrategy(const vector<double>& prices,
                        const vector<double>& sma5,
                        const vector<double>& sma20) 
{
    TradePlan plan;
    int n = prices.size();
    bool holding = false;
    int buyIndex = -1;

    for (int i = 0; i < n; i++) {
        if (isnan(sma5[i]) || isnan(sma20[i])) continue;

      
        if (!holding && sma5[i] > sma20[i]) {
            holding = true;
            buyIndex = i;
        }

        else if (holding && sma5[i] < sma20[i]) {
            holding = false;
            plan.buyDays.push_back(buyIndex);
            plan.sellDays.push_back(i);
            buyIndex = -1;
        }
    }

    if (holding) {
        plan.buyDays.push_back(buyIndex);
        plan.sellDays.push_back(n - 1);
    }

    return plan;
}
