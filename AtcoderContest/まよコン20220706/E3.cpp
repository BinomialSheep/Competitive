#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

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
    vi A(N);
    vi B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];

    // Bを座圧のして座標変換
    map<int, int> mp;
    // Aがkeyで、valueは-b
    map<int, vector<int>> d;
    rep(i, N) {
      int a = A[i], b = B[i];
      b = -b;
      d[a].push_back(b);
      mp[b] = 0;
    }
    {
      int i = 0;
      // ユニバーサル参照？
      for (auto &&p : mp) {
        // 後置インクリメントなので0-indexed
        p.second = i++;
      }
    }
    int m = (int)mp.size();
    fenwick_tree<int> t(m);
    ll ans = 0;
    // dを下から（aの値はどうでもいいので捨てる
    for (auto [_, bs] : d) {
      // とりあえず全部追加してから順番に数える（同じ座標対策）
      for (int b : bs) {
        b = mp[b];
        t.add(b, 1);
      }
      for (int b : bs) {
        b = mp[b];
        // 半開区間なのでb+1を指定
        ans += t.sum(0, b + 1);
      }
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