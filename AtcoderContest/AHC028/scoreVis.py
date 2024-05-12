import matplotlib.pyplot as plt
import numpy as np
# Kの値を範囲で生成
K_values = np.linspace(0, 100, 1000)

# 式の計算
result_values = np.round(1000 * (K_values + 1) / 200)

# プロット
plt.plot(K_values, result_values)
plt.xlabel('K')
plt.ylabel('round(1000 * (K + 1) / 200)')
plt.title('Expression Visualization')
plt.grid(True)
plt.show()
