"""
方針カードの生成を理解するためのやつ
"""
import numpy as np
import random
import matplotlib.pyplot as plt

def clamp(n, smallest, largest):
    return max(smallest, min(n, largest))


# 通常労働
def t0(L=0):
    w = random.uniform(1, 50) * (2 ** L)
    w2 = w / (2 ** L)
    return clamp(random.gauss(w2, w2/3), 1, 10000) * (2 ** L)

# サブプロットの行数と列数を指定
rows = 2
cols = 2

# サブプロットの設定
fig, axes = plt.subplots(rows, cols, figsize=(12, 8))

# 各 L の値に対してプロット
for i in range(rows):
    for j in range(cols):
        L_value = i * cols + j
        values = [t0(L_value) for _ in range(1000)]  # 1000回サンプリング
        axes[i, j].hist(values, bins=30, edgecolor='black')
        axes[i, j].set_title(f't0 Function Distribution for L={L_value}')
        axes[i, j].set_xlabel('Values')
        axes[i, j].set_ylabel('Frequency')
# レイアウトの調整
plt.tight_layout()
# グラフを表示
plt.savefig('histogram0.png')