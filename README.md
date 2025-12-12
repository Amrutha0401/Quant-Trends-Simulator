# Quant Trends Simulator

**Quant Trends Simulator** is a high-performance C++ research engine for
simulating and evaluating multiple technical trading strategies across
multiple assets. It supports the workflow: **strategy generation →
backtesting → PnL summary → visualization → insights**.

## Features

### Trading Strategies

-   SMA Crossover (5/20)
-   EMA Crossover (12/26)
-   RSI Momentum Strategy

### Backtesting Engine

-   Percent-based capital allocation
-   Slippage modeling
-   Trade-by-trade PnL calculation
-   Equity curve reconstruction
-   Summary CSV output
-   Multi-asset support (AAPL, MSFT, META, NIFTY)

### Visualization (Python)

-   Total PnL comparison
-   Equity curves per asset & strategy
-   Auto-generated PNGs

## Datasets

Datasets are stored in `data/` and contain daily OHLCV price data in CSV
format.

Each file includes: - Date, Open, High, Low, Close, Volume

Assets included: - **AAPL.csv** -- Apple Inc. - **MSFT.csv** --
Microsoft Corp. - **META.csv** -- Meta Platforms - **NIFTY.csv** -- NSE
NIFTY 50 Index

Any OHLCV dataset following this format can be used as a drop‑in
replacement.

## Project Structure

    quanttrendssim/
    ├── src/
    │   ├── indicators.cpp/.hpp
    │   ├── strategies.cpp/.hpp
    │   ├── backtester.cpp/.hpp
    │   └── main.cpp
    ├── data/
    │   ├── AAPL.csv
    │   ├── MSFT.csv
    │   ├── META.csv
    │   └── NIFTY.csv
    ├── results/
    │   ├── results_summary.csv
    │   ├── pnl_by_strategy.png
    │   └── equity_*.png
    ├── plotting/
    │   └── plot_results.py
    └── README.md

## Build & Run

### Compile

    g++ -std=gnu++17 src/*.cpp -O2 -o quant_sim

### Run

    ./quant_sim

## Visualization

    cd plotting
    python plot_results.py

## Strategy Logic

**SMA (5/20)**\
Buy: SMA5 \> SMA20\
Sell: SMA5 \< SMA20

**EMA (12/26)**\
Buy: EMA12 \> EMA26\
Sell: EMA12 \< EMA26

**RSI**\
Buy: RSI \< 30\
Sell: RSI \> 70
