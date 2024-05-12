#include <bits/stdc++.h>
using namespace std;

// 普通の素因数分解 O(√N)
template <typename T>
vector<pair<T, T>> calcPrimeFactorSimple(T n) {
  vector<pair<T, T>> ret;
  for (T i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;
    T tmp = 0;
    while (n % i == 0) {
      tmp++;
      n /= i;
    }
    ret.emplace_back(i, tmp);
  }
  if (n != 1) ret.emplace_back(n, 1);
  return ret;
}

// https://yukicoder.me/problems/18
// No.2 素因数ゲーム
// やるだけ
int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> vec = calcPrimeFactorSimple(N);

  int grundy = 0;

  for (auto [_, scd] : vec) {
    grundy ^= scd;
  }
  cout << (grundy ? "Alice" : "Bob") << endl;

  return 0;
}
