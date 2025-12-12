#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "indicators.hpp"
#include "strategies.hpp"
#include "backtester.hpp"

using namespace std;
vector<double> loadPrices(const string& path) {
    ifstream file(path);
    vector<double> prices;

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << path << "\n";
        return prices;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.size() == 0) continue;

        if (line.front() == '"' && line.back() == '"' && line.size() > 1)
            line = line.substr(1, line.size() - 2);

        try {
            prices.push_back(stod(line));
        }
        catch (...) {
            continue;
        }
    }
    return prices;
}

string getAssetName(const string& path) {
    string name = path.substr(path.find_last_of("/\\") + 1); 
    if (name.find('.') != string::npos)
        name = name.substr(0, name.find(".")); 
    return name;
}

int main() {

    vector<string> files = {
        "../data/AAPL.csv",
        "../data/MSFT.csv",
        "../data/META.csv",
        "../data/NIFTY.csv"
    };

    double initialCapital = 10000.0;
    double percentPerTrade = 0.10;
    double slippage = 0.001;
    double fee = 0.0;
    double stopLoss = 0.0;
    double takeProfit = 0.0;


    ofstream summary("../results_summary.csv");
    summary << "asset,strategy,trades,total_pnl,final_capital\n";

    for (const auto& f : files) {

        cout << "\n============================================\n";
        cout << " Running strategies for: " << f << "\n";
        cout << "============================================\n";

        auto prices = loadPrices(f);
        if (prices.empty()) {
            cout << "No data found in file: " << f << "\n";
            continue;
        }

        string asset = getAssetName(f);

        auto sma5 = sma(prices, 5);
        auto sma20 = sma(prices, 20);

        auto ema12 = ema(prices, 12);
        auto ema26 = ema(prices, 26);

        auto rsi14 = rsi(prices, 14);

        auto smaPlan = sma_strategy(prices, sma5, sma20);
        auto smaRes = run_backtest_percent("sma_strategy",
                                           prices,
                                           smaPlan,
                                           initialCapital,
                                           percentPerTrade,
                                           slippage,
                                           fee,
                                           stopLoss,
                                           takeProfit);

        cout << "[SMA] trades=" << smaRes.trades
             << " pnl=" << smaRes.totalPnL
             << " final=" << smaRes.finalCapital << "\n";

        summary << asset << ",sma_strategy,"
                << smaRes.trades << ","
                << smaRes.totalPnL << ","
                << smaRes.finalCapital << "\n";

        auto emaPlan = ema_strategy(prices, ema12, ema26);
        auto emaRes = run_backtest_percent("ema_strategy",
                                           prices,
                                           emaPlan,
                                           initialCapital,
                                           percentPerTrade,
                                           slippage,
                                           fee,
                                           stopLoss,
                                           takeProfit);

        cout << "[EMA] trades=" << emaRes.trades
             << " pnl=" << emaRes.totalPnL
             << " final=" << emaRes.finalCapital << "\n";

        summary << asset << ",ema_strategy,"
                << emaRes.trades << ","
                << emaRes.totalPnL << ","
                << emaRes.finalCapital << "\n";


        auto rsiPlan = rsi_strategy(prices, sma5, rsi14);
        auto rsiRes = run_backtest_percent("rsi_strategy",
                                           prices,
                                           rsiPlan,
                                           initialCapital,
                                           percentPerTrade,
                                           slippage,
                                           fee,
                                           stopLoss,
                                           takeProfit);

        cout << "[RSI] trades=" << rsiRes.trades
             << " pnl=" << rsiRes.totalPnL
             << " final=" << rsiRes.finalCapital << "\n";

        summary << asset << ",rsi_strategy,"
                << rsiRes.trades << ","
                << rsiRes.totalPnL << ","
                << rsiRes.finalCapital << "\n";

        string outCsv = "../" + asset + "_sma_trades.csv";
        ofstream out(outCsv);
        out << "buyDay,sellDay,buyPrice,sellPrice,qty,pnl\n";

        for (auto& t : smaRes.executedTrades)
            out << t.buyDay << ","
                << t.sellDay << ","
                << t.buyPrice << ","
                << t.sellPrice << ","
                << t.qty << ","
                << t.pnl << "\n";

        out.close();
    }

    summary.close();
    cout << "\nSummary saved to results_summary.csv\n";

    return 0;
}
