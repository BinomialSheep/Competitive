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
  int n;
  cin >> n;
  vector<pair<ll, ll>> AB(n);
  rep(i, n) {
    ll a, b;
    cin >> a >> b;
    AB[i] = make_pair(a, b);
  }

  /* solve */
  ll ans = 1LL << 60;

  rep(i, n) {
    ll inI = AB[i].first;
    rep(j, n) {
      ll outI = AB[j].second;
      ll times = 0;
      rep(k, n) {
        times += abs(AB[k].first - inI);
        times += abs(AB[k].second - AB[k].first);
        times += abs(outI - AB[k].second);
      }
      ans = llMin(ans, times);
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}