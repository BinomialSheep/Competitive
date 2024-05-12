#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  string S, T;
  cin >> S >> T;

  /* solve */
  ll L = lcm((ll)N, (ll)M);

  map<ll, char> smap;
  map<ll, char> tmap;
  rep(i, N) {
    ll idx = i * (L / N);
    // cout << idx << endl;
    smap[idx] = S[i];
  }
  rep(i, M) {
    ll idx = i * (L / M);
    tmap[idx] = T[i];
  }
  // 存在しないのは、smap[idx] != tmap[idx]となる時
  for (auto p : smap) {
    if (!tmap.count(p.first)) continue;
    if (tmap[p.first] != p.second) {
      puts("-1");
      return 0;
    }
  }
  cout << L << endl;

  /* output */

  return 0;
}