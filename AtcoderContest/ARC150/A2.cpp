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
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    /* solve */
    int cnt1 = 0;
    rep(i, N) if (S[i] == '1') cnt1++;
    if (cnt1 > K) {
      cout << "No" << endl;
      return;
    }
    if (cnt1 == K) {
      int now = 0;
      rep(i, N) {
        if (S[i] == '1') {
          now++;
          if (now == K) {
            cout << "Yes" << endl;
            return;
          }
        } else {
          if (now != 0) {
            cout << "No" << endl;
            return;
          }
        }
      }
      assert(false);
    }
    if (cnt1 == 0) {
      int now = 0;
      int ok = 0;
      rep(i, N) {
        if (S[i] == '?') {
          now++;
          if (now > K) {
            cout << "No" << endl;
            return;
          }
        } else {
          if (now != 0) {
            if (now == K) ok++;
            now = 0;
          }
        }
      }
      if (now == K) ok++;
      if (ok == 1) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
      return;
    }

    int left = INFTY;
    int right = -1;
    rep(i, N) {
      if (S[i] == '1') {
        chmin(left, i);
        chmax(right, i);
      }
    }
    for (int i = left; i < right; i++) {
      if (S[i] == '0') {
        cout << "No" << endl;
        return;
      }
    }
    if (right - left + 1 > K) {
      cout << "No" << endl;
      return;
    }
    if (right - left + 1 == K) {
      cout << "Yes" << endl;
      return;
    }
    // assert(false);

    bool l = false;
    if (left != 0 && S[left - 1] == '?') l = true;
    bool r = false;
    if (right != N - 1 && S[right + 1] == '?') r = true;

    int lidx = left - 1;
    int ridx = right + 1;
    if (l) {
      while (lidx >= 0) {
        if (S[lidx] == '?') {
          lidx--;
        } else {
          break;
        }
      }
      lidx++;
    }
    if (r) {
      while (ridx < N) {
        if (S[ridx] == '?') {
          ridx++;
        } else {
          break;
        }
      }
      ridx--;
    }
    if (l && r) {
      if (ridx - lidx + 1 == K) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else if (l) {
      if (right - lidx + 1 >= K) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else if (r) {
      if (ridx - left + 1 >= K) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else {
      cout << "No" << endl;
    }

    /* output */
  }
};

int main() {
  int T;
  cin >> T;
  rep(ti, T) {
    Solver solver;
    solver.solve();
  }
  return 0;
}