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
using pii = pair<int, int>;
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
    int N;
    cin >> N;
    vi X(N);
    rep(i, N) {
      cin >> X[i];
      X[i]--;
    }

    vi C(N);
    rep(i, N) cin >> C[i];

    /* solve */
    vb color(N);
    vb color2(N);

    ll ans = 0;
    rep(i, N) {
      if (color[i]) continue;
      int nex = i;
      color[nex] = true;
      // int loop = -1;
      while (true) {
        if (nex == X[nex]) {
          // そんなことないはずだが
          nex = -1;
          break;
        }
        nex = X[nex];
        if (nex < i) break;
        if (color2[nex]) break;
        if (color[nex]) {
          // nexからnexでループ検出
          // loop = nex;
          break;
        } else {
          color[nex] = true;
        }
      }
      if (nex < i) continue;
      if (nex == -1) continue;
      if (color2[nex]) {
        color2[i] = true;
        continue;
      }
      int value = INFTY;
      int start = nex;
      while (true) {
        color2[nex] = true;
        chmin(value, C[nex]);
        nex = X[nex];
        if (start == nex) break;
      }
      ans += value;
      // cout << start << " " << value << endl;
    }

    /* output */
    cout << ans << endl;
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