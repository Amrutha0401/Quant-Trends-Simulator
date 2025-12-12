#pragma once
#include <vector>
using namespace std;


struct TradePlan {
vector<int> buyDays;
vector<int> sellDays;
double theoreticalProfit = 0;
};


TradePlan runDPStrategy(const vector<double>& prices,
const vector<double>& sma5,
const vector<double>& sma20);