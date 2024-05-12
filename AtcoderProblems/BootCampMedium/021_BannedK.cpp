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

ll nC2(int n) {
  ll m = n;
  if (m <= 1) return 0;
  if (m == 2) return 1;
  if (m % 2 == 0)
    return m / 2 * (m - 1);
  else
    return (m - 1) / 2 * m;
}

int main() {
  /* input */
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) cin >> A[i];
  /* solve */
  // 全部求めておいて、あとで減らす
  ll count = 0;
  // mapに入れる
  map<int, int> myMap;
  rep(i, N) myMap[A[i]]++;
  // 全部計算
  for (auto p : myMap) count += nC2(p.second);
  /* output */
  rep(i, N) {
    int num = myMap[A[i]];
    ll temp = count;
    temp -= nC2(num);
    temp += nC2(num - 1);
    cout << temp << endl;
  }

  return 0;
}