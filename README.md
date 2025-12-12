Quant Trends Simulator is a high-performance quantitative trading research engine , designed to simulate and evaluate multiple technical trading strategies across multiple assets.
It includes a complete research workflow: strategy generation → backtesting → PnL summary → visualization → insights.

This project was built with a focus on:

modular architecture

realistic trading constraints

clean and efficient C++ code

extensible strategy framework

clear, visual outputs for analysis

🚀 Features
🧠 Trading Strategies Implemented

SMA Crossover Strategy (5/20)

EMA Crossover Strategy (12/26)

RSI Momentum Strategy

📊 Backtesting Engine


Percent-based capital allocation per trade

Slippage modeling

Trade-by-trade PnL calculation

Equity curve reconstruction

Automatic summary CSV generation

Multi-asset execution (AAPL, MSFT, META, NIFTY)

🖥️ Visualization (Python)

Total PnL comparison chart

Equity curves per asset & strategy

Auto-generated PNG outputs

📁 Project Structure
quanttrendssim/
│
├── src/                    # C++ source code
│   ├── indicators.cpp/.hpp
│   ├── strategies.cpp/.hpp
│   ├── backtester.cpp/.hpp
│   └── main.cpp
│
├── data/                   # Historical price data (CSV)
│   ├── AAPL.csv
│   ├── MSFT.csv
│   ├── META.csv
│   └── NIFTY.csv
│
├── results/                # Generated results
│   ├── results_summary.csv
│   ├── pnl_by_strategy.png
│   ├── equity_AAPL_sma.png
│   ├── equity_MSFT_sma.png
│   ├── equity_META_sma.png
│   └── equity_NIFTY_sma.png
│
├── plotting/               # Python visualization scripts
│   └── plot_results.py
│
└── README.md
🔧 Build & Run Instructions
Compile (Windows/Linux/macOS)

From the project root:

g++ -std=gnu++17 src/*.cpp -O2 -o quant_sim

Run Backtests
./quant_sim


This will produce:

results_summary.csv

Trade logs per strategy

Final PnL & capital

Recommended best strategy per asset

📊 Visualization

To generate all plots:

cd plotting
python plot_results.py


Requires:

pip install pandas matplotlib


Generated outputs appear in:

results/

📉 Sample Results (From This Project)
Total PnL by Strategy & Asset

Generated PNG:
results/pnl_by_strategy.png

Equity Curves

Examples:

results/equity_AAPL_sma.png

results/equity_MSFT_sma.png

These show how strategy PnL evolves through time.

Insights from Backtests

AAPL → RSI strategy performed best (mean-reverting periods)

MSFT → EMA strategy outperformed (strong trend)

META → SMA strategy captured long-term momentum

NIFTY → Highly choppy; all trend-followers struggled

The results reflect realistic market behavior, validating the engine.

Strategy Logic Overview
SMA Crossover

Buy when:

SMA5 crosses above SMA20


Sell when:

SMA5 crosses below SMA20

EMA Crossover

Buy when:

EMA12 > EMA26


Sell when:

EMA12 < EMA26

RSI Strategy

Buy when:

RSI < 30


Sell when:

RSI > 70
