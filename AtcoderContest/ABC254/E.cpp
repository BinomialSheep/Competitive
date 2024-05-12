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
    int N, M;
    cin >> N >> M;
    vvi G(N);

    rep(i, M) {
      int a, b;
      cin >> a >> b;
      --a;
      --b;
      G[a].push_back(b);
      G[b].push_back(a);
    }

    /* solve */
    vector<set<int>> d1(N);
    vector<set<int>> d2(N);
    vector<set<int>> d3(N);

    rep(i, N) {
      for (auto v : G[i]) {
        d1[i].insert(v);
      }
    }
    rep(i, N) {
      for (auto v : d1[i]) {
        for (auto v2 : G[v]) {
          if (v2 != i && d1[i].count(v2) == 0) {
            d2[i].insert(v2);
          }
        }
      }
    }
    rep(i, N) {
      for (auto v2 : d2[i]) {
        for (auto v3 : G[v2]) {
          if (v3 != i && d1[i].count(v3) == 0 && d2[i].count(v3) == 0) {
            d3[i].insert(v3);
          }
        }
      }
    }

    vector<int> ans1(N);
    vector<int> ans2(N);
    vector<int> ans3(N);

    rep(i, N) {
      ans1[i] += i + 1;
      for (auto v : d1[i]) {
        ans1[i] += v + 1;
      }
    }
    rep(i, N) {
      ans2[i] += ans1[i];
      for (auto v : d2[i]) {
        ans2[i] += v + 1;
      }
    }
    rep(i, N) {
      ans3[i] += ans2[i];
      for (auto v : d3[i]) {
        ans3[i] += v + 1;
      }
    }

    // クエリ
    int Q;
    cin >> Q;
    vector<pii> qs(Q);
    rep(i, Q) {
      int x, k;
      cin >> x >> k;
      --x;
      if (k == 0) {
        cout << x + 1 << endl;
      } else if (k == 1) {
        cout << ans1[x] << endl;
      } else if (k == 2) {
        cout << ans2[x] << endl;
      } else {
        cout << ans3[x] << endl;
      }
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