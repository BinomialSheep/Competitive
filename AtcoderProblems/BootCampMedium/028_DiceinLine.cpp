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

ll sum(ll n) {
  if (n == 1) return 1;
  return n + sum(n - 1);
}

double expected(ll n) { return (double)(sum(n)) / (double)n; }

int main() {
  /* input */
  int N, K;
  cin >> N >> K;
  vector<int> p(N);
  rep(i, N) cin >> p[i];

  /* solve */
  ll sum = 0;
  rep(i, K) sum += p[i];
  ll maxSum = 0;
  int start = 0;

  for (int i = K; i < N; i++) {
    sum = sum + p[i] - p[i - K];
    if (sum > maxSum) {
      maxSum = sum;
      start = i - K + 1;
    }
  }

  double ans = 0;
  rep(i, K) { ans += expected(p[start + i]); }
  /* output */
  cout.precision(10);
  cout << fixed << ans << endl;

  return 0;
}