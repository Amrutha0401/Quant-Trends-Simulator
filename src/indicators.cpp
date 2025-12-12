#include "indicators.hpp"
#include <numeric>
#include <cmath>
using namespace std;

vector<double> sma(const vector<Price>& prices, int window){
    int n = prices.size();
    vector<double> out(n, NAN);
    if(window<=0 || n<window) return out;
    double s=0;
    for(int i=0;i<window;i++) s+=prices[i];
    out[window-1]=s/window;
    for(int i=window;i<n;i++){
        s += prices[i] - prices[i-window];
        out[i] = s/window;
    }
    return out;
}

vector<double> ema(const vector<Price>& prices, int window){
    int n = prices.size();
    vector<double> out(n, NAN);
    if(window<=0 || n==0) return out;
    double alpha = 2.0/(window+1.0);
    out[0]=prices[0];
    for(int i=1;i<n;i++){
        out[i] = alpha*prices[i] + (1-alpha)*out[i-1];
    }
    return out;
}

vector<double> rsi(const vector<Price>& prices, int period){
    int n = prices.size();
    vector<double> out(n, NAN);
    if(period<=0 || n<=period) return out;
    double gain=0, loss=0;
    for(int i=1;i<=period;i++){
        double diff = prices[i]-prices[i-1];
        if(diff>0) gain+=diff; else loss-=diff;
    }
    double avgGain = gain/period, avgLoss = loss/period;
    out[period] = (avgLoss==0) ? 100.0 : (100.0 - (100.0/(1.0 + (avgGain/avgLoss))));
    for(int i=period+1;i<n;i++){
        double diff = prices[i]-prices[i-1];
        double g = diff>0?diff:0;
        double l = diff<0?-diff:0;
        avgGain = (avgGain*(period-1) + g)/period;
        avgLoss = (avgLoss*(period-1) + l)/period;
        out[i] = (avgLoss==0) ? 100.0 : (100.0 - (100.0/(1.0 + (avgGain/avgLoss))));
    }
    return out;
}
