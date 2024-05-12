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
// #include <atcoder/all>
// using namespace atcoder;
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
    int N, M;
    cin >> N >> M;
    vs S(N);
    rep(i, N) cin >> S[i];
    set<string> T;
    rep(i, M) {
      string t;
      cin >> t;
      T.insert(t);
    }

    /* solve */
    int sz = 0;
    rep(i, N) sz += S[i].size();
    sz += N - 1;

    vi perm(N);
    rep(i, N) perm[i] = i;
    int endFlag = 0;

    do {
      // 余分な_をいくつ入れるか
      for (int i = 0; i + sz <= 16; i++) {
        auto rec = [&](auto f, int used, int depth, string now) -> void {
          if (endFlag) return;
          now += S[perm[depth]];
          if (depth == N - 1) {
            debug(now);
            if (now.size() < 3 || now.size() > 16) return;
            if (T.count(now) == 0) {
              cout << now << endl;
              endFlag = 1;
            }
            return;
          }
          now.push_back('_');
          for (int j = 0; j + used <= i; j++) {
            string nex = now;
            rep(k, j) nex.push_back('_');
            f(f, used + j, depth + 1, nex);
          }
        };
        // 余分な_をどこに入れるか
        rec(rec, 0, 0, "");
      }

    } while (next_permutation(all(perm)));

    /* output */
    if (!endFlag) cout << -1 << endl;
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