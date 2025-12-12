#include "sma.hpp"
#include <cmath>


vector<double> computeSMA(const vector<double>& prices, int window) {
int n = prices.size();
vector<double> sma(n, NAN);
if (window <= 0 || n < window) return sma;


double sum = 0;
for (int i = 0; i < window; i++) sum += prices[i];
sma[window - 1] = sum / window;


for (int i = window; i < n; i++) {
sum += prices[i] - prices[i - window];
sma[i] = sum / window;
}
return sma;
}