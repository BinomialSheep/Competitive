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

static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

struct Solver {
  void best(int N, int M, double eps) {
    cout << N << endl;
    int sz = N * (N - 1) / 2;

    vi sizeList;
    for (int i = 0; i <= sz; i += sz / (M - 1)) {
      sizeList.push_back(i);
      if ((int)sizeList.size() == M) break;
    }
    while ((int)sizeList.size() < M) sizeList.push_back(0);
    while ((int)sizeList.size() > M) sizeList.pop_back();
    assert((int)sizeList.size() == M);

    vs G(M);
    rep(i, M) {
      int v = sizeList[i];
      rep(j, v) G[i].push_back('1');
      rep(j, sz - v) G[i].push_back('0');
      assert((int)G[i].size() == sz);
      cout << G[i] << "\n";
      // debug(str.size());
    }
    cout << flush;
    /* interactive */
    rep(qi, 100) {
      string S;
      cin >> S;
      int cnt = 0;
      string H = S;
      // 実験の場合
      H = G[stoi(S)];
      rep(i, (int)H.size()) {
        if (randXor() % 100 < eps * 100) {
          H[i] = (H[i] == '0' ? '1' : '0');
        }
      }
      // ここまで
      for (auto c : H)
        if (c == '1') cnt++;
      //
      int ans = 0;
      int diff = INFTY;
      rep(i, sizeList.size()) {
        if (chmin(diff, abs(sizeList[i] - cnt))) ans = i;
      }
      // デバッグ用
      int realCnt = 0;
      for (auto c : G[stoi(S)])
        if (c == '1') realCnt++;
      debug(cnt, ans, realCnt, S);

      cout << ans << endl;
    }
  }

  // (i, j)が文字列の何文字目か求める
  int calcIdx(int N, int i, int j) {
    int ret = 0;
    int d = N;
    rep(k, i) ret += --d;
    ret += j - i;
    return ret - 1;
  }

  //
  int search(int N, int csz, string &S) {
    // 今は数だけ
    int ret = 0;
    vvi G(N);
    rep(i, N - 1) for (int j = i + 1; j < N; j++) {
      if (S[calcIdx(N, i, j)] == '1') {
        G[i].push_back(j);
        G[j].push_back(i);
      }
    }
    // debug(G);

    unordered_set<int> seen;

    rep(i, N) {
      if (seen.count(i)) continue;
      if ((int)G[i].size() < (csz - 1) * 0.8) continue;
      seen.insert(i);
      map<int, int> mp;
      for (auto v : G[i]) {
        mp[v]++;
        for (auto u : G[v]) {
          if (u != i) mp[u]++;
        }
      }
      set<int> comb;
      int sum = 0;
      for (auto [k, v] : mp) {
        if (v >= (csz - 1) * 0.8) {
          sum += v;
          comb.insert(k);
        }
      }
      // debug(i, comb);

      if (sum < (csz - 1) * 0.8) continue;
      if ((int)comb.size() < csz - 1) continue;
      if ((int)comb.size() > csz + 1) continue;
      for (auto v : comb) seen.insert(v);
      ret++;
    }

    return ret;
  }

  void solve() {
    /* input */
    int M;
    double eps;
    cin >> M >> eps;

    /* solve */
    int N = 100;
    cout << N << endl;
    int sz = N * (N - 1) / 2;
    vs G(N);
    // cluster Size
    int csz = 10;

    int cnt = 0;
    rep(i, M) {
      string s = string(sz, '0');
      rep(j, cnt) {
        rep(k, csz) rep(l, k) {
          int idx1 = j * csz + l;
          int idx2 = j * csz + k;
          // debug(idx1, idx2);
          s[calcIdx(N, idx1, idx2)] = '1';
        }
      }
      // debug(s);
      assert(s.size() == sz);
      G[i] = s;
      cout << G[i] << endl;
      cnt++;
    }

    int correct = 0;
    rep(qi, 100) {
      string S;
      cin >> S;
      string H = S;
      // 実験の場合
      H = G[stoi(S)];
      rep(i, (int)H.size()) {
        if (randXor() % 100 < eps * 100) {
          H[i] = (H[i] == '0' ? '1' : '0');
        }
      }
      // ここまで
      //
      // debug(G[stoi(S)]);
      // debug(H);
      int count = search(N, csz, H);
      int ans = count;
      debug(count, stoi(S));
      if (stoi(S) == ans) correct++;

      cout << min(ans, M - 1) << endl;
    }
    debug(correct);

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