#include <iostream>
#include <unordered_map>
#include <vector>

const int MOD = 998244353;

// 約数の個数を計算する関数
int countDivisors(int x) {
  int count = 0;
  for (int i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      count += (i * i == x) ? 1 : 2;
    }
  }
  return count;
}

// スコアの総和を計算する関数
long long computeTotalScore(int N, int M) {
  std::unordered_map<int, long long> productCount;

  // 各長さ k の数列に対して積を計算し、その積の個数を記録
  for (int k = 1; k <= N; ++k) {
    std::unordered_map<int, long long> newProductCount;
    for (int m = 1; m <= M; ++m) {
      for (auto &p : productCount) {
        long long newProduct = p.first * m;
        newProductCount[newProduct] =
            (newProductCount[newProduct] + p.second) % MOD;
      }
      newProductCount[m] = (newProductCount[m] + 1) % MOD;
    }
    productCount = newProductCount;
  }

  // 全ての積に対してそのスコアを計算し、総和を求める
  long long totalScore = 0;
  for (auto &p : productCount) {
    int divisors = countDivisors(p.first);
    totalScore = (totalScore + divisors * p.second) % MOD;
  }

  return totalScore;
}

int main() {
  int N, M;
  std::cin >> N >> M;

  long long result = computeTotalScore(N, M);
  std::cout << result << std::endl;

  return 0;
}
