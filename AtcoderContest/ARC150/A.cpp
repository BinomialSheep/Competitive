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
            ok = 0;
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

    deque<pair<int, int>> dq;
    rep(i, N) {
      if (dq.empty()) {
        if (S[i] == '0') {
          dq.emplace_back(0, 1);
        } else {
          dq.emplace_back(1, 1);
        }
        continue;
      }
      if (dq.back().first == 0 && S[i] == '0') {
        dq.back().second++;
      } else if (dq.back().first == 0) {
        dq.emplace_back(1, 1);
      } else if (dq.back().first == 1 && S[i] == '0') {
        dq.emplace_back(0, 1);
      } else {
        dq.back().second++;
      }
    }
    debug(dq);

    int idx = 0;
    int start = -1;
    int sz = -1;
    for (auto p : dq) {
      if (p.first == 1) {
        int flag = 0;
        for (int j = idx; j < idx + p.second; j++) {
          if (S[j] == '1') {
            flag = 1;
            break;
          }
        }
        if (flag) {
          if (p.second < K) {
            cout << "No" << endl;
            return;
          } else {
            if (start != -1) {
              cout << "No" << endl;
              return;
            } else {
              start = idx;
              sz = p.second;
              // debug(p, start, sz);
            }
          }
        }
      }
      idx += p.second;
    }
    // 1?????111????
    deque<pair<char, int>> dq2;
    for (int j = start; j < start + sz; j++) {
      if (dq2.empty()) {
        dq2.emplace_back(S[j], 1);
        continue;
      }
      if (dq2.back().first == S[j]) {
        dq2.back().second++;
      } else {
        dq2.emplace_back(S[j], 1);
      }
    }
    int left = INFTY;
    int right = -1;
    rep(i, dq2.size()) {
      if (dq2[i].first == '1') {
        chmin(left, i);
        chmax(right, i);
      }
    }
    for (int i = left; i < right; i++) {
      if (dq2[i].first == '?') dq2[i].first = '1';
    }
    deque<pair<char, int>> dq3;
    rep(i, dq2.size()) {
      if (dq3.empty()) {
        dq3.push_back(dq2[i]);
        continue;
      }
      if (dq3.back().first == dq2[i].first) {
        dq3.back().second += dq2[i].second;
      } else {
        dq3.push_back(dq2[i]);
      }
    }
    debug(dq2);
    debug(dq3);
    rep(i, dq3.size()) {
      if (dq3[i].first == '1') {
        if (dq3[i].second > K) {
          cout << "No" << endl;
          return;
        }
        if (i == 0 || i == dq3.size() - 1) {
          cout << "Yes" << endl;
          return;
        } else {
          cout << "No" << endl;
          return;
        }
      }
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