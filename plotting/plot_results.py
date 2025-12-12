import pandas as pd
import matplotlib.pyplot as plt
import os

BASE = r"E:\projects\quanttrendssim"
RESULTS = os.path.join(BASE, "results")
DATA = os.path.join(BASE, "data")
TRADES = BASE  

os.makedirs(RESULTS, exist_ok=True)
summary_path = os.path.join(BASE, "results_summary.csv")
summary = pd.read_csv(summary_path)
pivot = summary.pivot(index="asset", columns="strategy", values="total_pnl")
pivot = pivot.fillna(0)    

pivot.plot(kind="bar", figsize=(9,5), title="Total PnL by Asset & Strategy")
plt.ylabel("Total PnL")
plt.tight_layout()

png1 = os.path.join(RESULTS, "pnl_by_strategy.png")
plt.savefig(png1)
plt.close()

print("✔ Saved:", png1)

def plot_equity_curve(asset):
    tradefile = os.path.join(TRADES, f"{asset}_sma_trades.csv")
    pricefile = os.path.join(DATA, f"{asset}.csv")
    outpng = os.path.join(RESULTS, f"equity_{asset}_sma.png")

    if not os.path.exists(tradefile):
        print(f"✘ Trade file missing for {asset}: {tradefile}")
        return
    if not os.path.exists(pricefile):
        print(f"✘ Price file missing for {asset}: {pricefile}")
        return

    trades = pd.read_csv(tradefile)
    prices = pd.read_csv(pricefile, header=None, names=["close"])

    equity = [10000.0] * len(prices)
    cur = 10000.0

    for _, row in trades.iterrows():
        sell_idx = int(row["sellDay"])
        cur += float(row["pnl"])
        equity[sell_idx:] = [cur] * (len(prices) - sell_idx)

    plt.figure(figsize=(10,4))
    plt.plot(prices["close"], label="Price", color="blue")
    plt.twinx()
    plt.plot(equity, label="Equity", color="orange")
    plt.title(f"Equity Curve — {asset} SMA Strategy")
    plt.tight_layout()
    plt.savefig(outpng)
    plt.close()

    print("✔ Saved:", outpng)


for a in ["AAPL", "MSFT", "META", "NIFTY"]:
    plot_equity_curve(a)

print("\n🎉 ALL PLOTS GENERATED SUCCESSFULLY!")
