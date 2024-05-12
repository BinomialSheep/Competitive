#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int count(int n, int k) {
  int i = 0;
  while (true) {
    if (n * pow(2, i) >= k) return i;
    i++;
  }
}

int main() {
  /* input */
  int N, K;
  cin >> N >> K;

  /* solve */
  double sum = 0;
  // 出た目をiとする
  for (int i = 1; i <= N; i++) {
    // iがK未満なら、iを何回掛けるとK以上になるか求める
    int num = count(i, K);
    sum += pow(0.5, (num));
  }

  /* output */
  cout.precision(10);
  cout << fixed << sum / N << endl;

  return 0;
}