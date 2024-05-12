#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
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

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  void solve() {
    /* input */
    int n;
    cin >> n;
    vi v(n);
    rep(i, n) cin >> v[i];

    /* solve */
    map<int, int> odMp;
    map<int, int> evMp;
    rep(i, n) {
      if (i % 2) {
        evMp[v[i]]++;
      } else {
        odMp[v[i]]++;
      }
    }
    //
    int odFst;
    int evFst;
    int num = 0;
    for (auto p : odMp) {
      if (chmax(num, p.second)) odFst = p.first;
    }
    num = 0;
    for (auto p : evMp) {
      if (chmax(num, p.second)) evFst = p.first;
    }

    // cout << odFst << " " << odMp[odFst] << endl;
    // cout << evFst << " " << evMp[evFst] << endl;

    if (odFst != evFst) {
      cout << n - odMp[odFst] - evMp[evFst] << endl;
      return;
    }
    int odNum = odMp[odFst];
    int evNum = evMp[evFst];

    int odScn;
    int evScn;
    num = 0;
    odMp.erase(odFst);
    for (auto p : odMp) {
      if (chmax(num, p.second)) odScn = p.first;
    }
    evMp.erase(evFst);
    for (auto p : evMp) {
      if (chmax(num, p.second)) evScn = p.first;
    }

    int ans = n - odNum - evMp[evScn];
    chmin(ans, n - odMp[odScn] - evNum);
    cout << ans << endl;

    /* output */
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}