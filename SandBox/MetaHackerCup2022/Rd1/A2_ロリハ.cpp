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

// ローリングハッシュ
{
  using ull = unsigned long long;
  bool rollingHash(string const &S, int t_start, int m) {
    int s_start = t_start + m;

    // B^mを用意する
    ull pow_B_m_1 = 1, pow_B_m_2 = 1;
    for (int k = 0; k < m; k++) {
      pow_B_m_1 *= B1, pow_B_m_2 *= B2;
    }

    // sとtの先頭m文字のハッシュ値sh,thを計算
    ull sh1 = 0, sh2 = 0, th1 = 0, th2 = 0;
    for (int k = 0; k < m; k++) {
      th1 = th1 * B1 + S[t_start + k], th2 = th2 * B2 + S[t_start + k];
      sh1 = sh1 * B1 + S[s_start + k], sh2 = sh2 * B2 + S[s_start + k];
    }

    // sをずらしてハッシュ値を更新
    for (int k = 0; s_start + k < S.length(); k++) {
      if (sh1 == th1 && sh2 == th2) return true;
      if (k + s_start < S.length()) {
        sh1 = sh1 * B1 + S[s_start + m + k] - S[s_start + k] * pow_B_m_1;
        sh2 = sh2 * B2 + S[s_start + m + k] - S[s_start + k] * pow_B_m_2;
      }
    }
    return false;
  }
}

struct Solver {
  void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      int N, K;
      cin >> N >> K;
      vi A(N);
      rep(i, N) cin >> A[i];
      vi B(2 * N);
      rep(i, N) cin >> B[i];
      rep(i, N) B[i + N] = B[i];

      /* solve */
      string ans = "YES";

      // MP
      vi C(N + 1);
      {
        C[0] = -1;
        int j = -1;
        rep(i, N) {
          while (j >= 0 && A[i] != A[j]) j = C[j];
          j++;
          C[i + 1] = j;
        }
        // debug(C);
      }
      // 検索
      int ai = 0;
      int bi = 0;
      vi idx;
      while (bi < 2 * N) {
        if (B[bi] == A[ai]) {
          // 最後まで一致
          if (ai == N - 1) {
            if (bi - ai < N) {
              idx.push_back(bi - ai);
            }
            if (C[0] == C[ai]) {
              bi++;
              ai = 0;
            } else {
              ai = C[ai];
            }
          }
          // 途中まで一致
          ai++;
          bi++;
        } else {
          // 不一致ならずらす
          if (C[0] == C[ai]) {
            // 先頭までずらす
            bi++;
            ai = 0;
          } else {
            // 途中までずらす
            ai = C[ai];
          }
        }
      }

      if (idx.empty()) {
        ans = "NO";
      } else {
        sort(all(idx));

        if (K == 0 && idx[0] != 0) ans = "NO";
        if (K == 1 && idx.size() == 1 && idx[0] == 0) ans = "NO";
        if (N == 2) {
          for (auto i : idx) {
            if (i ^ (K & 1)) {
              ans = "NO";
            } else {
              ans = "YES";
              break;
            }
          }
        }
      }
      if (ti == 22 || ti == 23 || ti == 27 || ti == 31) {
        debug(ti, N, K);
        debug(A);
        debug(B);
        debug(idx);
      }

      /* output */
      printf("Case #%d: %s\n", ti + 1, ans.c_str());
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