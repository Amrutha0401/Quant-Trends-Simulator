#pragma once
#include <vector>
using namespace std;

using Price = double;

vector<double> sma(const vector<Price>& prices, int window);
vector<double> ema(const vector<Price>& prices, int window);
vector<double> rsi(const vector<Price>& prices, int period);
