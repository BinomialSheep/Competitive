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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int mod = 1000000007;
    rep(ti, T) {
      /* input */
      int N, K;
      cin >> N >> K;
      map<int, vector<vpii>> mp;
      rep(i, N) {
        int A, B, X, Y;
        cin >> A >> B >> X >> Y;
        --A, --B;
        if (mp.count(A) == 0) mp[A] = vector<vpii>(2);
        if (mp.count(B) == 0) mp[B] = vector<vpii>(2);
        mp[A][0].emplace_back(X, i);
        mp[B][1].emplace_back(Y, i);
      }
      // debug(mp);
      /* solve */

      vector<vpii> G(N);

      for (auto p : mp) {
        if (p.second[0].empty() || p.second[1].empty()) continue;

        sort(all(p.second[0]));
        sort(all(p.second[1]));
        for (auto pb : p.second[1]) {
          int idx = pb.second;
          auto it = upper_bound(all(p.second[0]), pb);
          while (it != p.second[0].end()) {
            int cost = (*it).first - pb.first;
            if (cost > 0) G[idx].emplace_back(cost, (*it).second);
            ++it;
          }
        }
      }
      // debug(G);
      /*

      vi seen(N);
      vvi scores(N);
      vi ans;

      auto fin = [&](int v, int u, int now) {
        for (auto s : scores[u]) {
          int ss = (now + s) % mod;
          scores[v].push_back(ss);
          ans.push_back(ss);
        }
      };

      auto bfs = [&](auto f, int v) -> void {
        for (auto p : G[v]) {
          int u = p.second;
          int c = p.first;
          scores[v].push_back(c);
          ans.push_back(c);
          if (seen[u]) {
            fin(v, u, c);
            continue;
          }
          seen[u] = true;
          if (!G[u].empty()) {
            f(f, u);
            fin(v, u, c);
          }
        }
        seen[v] = true;
      };

      rep(i, N) {
        if (seen[i]) continue;
        if (G[i].empty()) {
          seen[i] = true;
          continue;
        }
        bfs(bfs, i);
      }
      // debug(scores);
      // debug(ans);
      int sum = 0;
      if ((int)ans.size() <= K) {
        rep(i, (int)ans.size()) sum = (sum + ans[i]) % mod;
      } else {
        sort(ans.rbegin(), ans.rend());
        rep(i, K) sum = (sum + ans[i]) % mod;
      }
      */
      int sum = 0;

      /* output */
      printf("Case #%d: %d\n", ti + 1, sum);
    }
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