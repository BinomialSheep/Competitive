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
    ll X, A, D, N;
    cin >> X >> A >> D >> N;

    /* solve */
    if (D == 0) {
      // D = 0なら簡単
      cout << abs(A - X) << endl;
      return;
    }

    if (D > 0) {
      // 最大値以上
      ll limMax = A + (N - 1) * D;
      if (X >= limMax) {
        cout << X - limMax << endl;
        return;
      }
      // 最小値以下
      if (X <= A) {
        cout << A - X << endl;
        return;
      }
      // その間
      D = abs(D);
      ll mod = (X - A) % D;
      chmin(mod, D - mod);
      cout << mod << endl;
    } else if (D < 0) {
      ll limMin = A + (N - 1) * D;
      if (X <= limMin) {
        cout << limMin - X << endl;
        return;
      }
      // 最大値以上
      if (A <= X) {
        cout << X - A << endl;
        return;
      }
      // その間
      D = abs(D);
      ll mod = (A - X) % D;
      chmin(mod, D - mod);
      cout << mod << endl;
    }

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