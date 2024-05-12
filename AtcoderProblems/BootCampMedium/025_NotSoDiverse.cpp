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

int main() {
  /* input */
  int N, K;
  cin >> N >> K;
  map<int, int> A;
  rep(i, N) {
    int a;
    cin >> a;
    A[a]++;
  }

  /* solve */
  vector<int> num;
  for (auto p : A) {
    num.push_back(p.second);
  }

  int kind = num.size() - K;
  int ans = 0;
  if (kind > 0) {
    sort(num.begin(), num.end());
    rep(i, kind) { ans += num[i]; }
  }

  /* output */
  cout << ans << endl;

  return 0;
}