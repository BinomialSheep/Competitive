#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
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
  int N;
  cin >> N;
  vector<string> s(N);
  rep(i, N) cin >> s[i];

  /* solve */
  rep(i, N) sort(s[i].begin(), s[i].end());
  map<string, int> mp;
  rep(i, N) mp[s[i]]++;
  ll ans = 0;
  for (auto p : mp) {
    ll cnt = p.second;
    ans += cnt * (cnt - 1) / 2;
  }

  /* output */
  cout << ans << endl;

  return 0;
}