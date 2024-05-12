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
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    /* solve */
    set<char> st;
    rep(i, s1.size()) { st.insert(s1[i]); }
    rep(i, s2.size()) { st.insert(s2[i]); }
    rep(i, s3.size()) { st.insert(s3[i]); }

    if (st.size() > 10) {
      cout << "UNSOLVABLE" << endl;
      return;
    }

    vector<int> perm(10);
    rep(i, 10) perm[i] = i;
    do {
      map<char, int> mp;
      int idx = 0;
      for (auto c : st) {
        mp[c] = perm[idx];
        idx++;
      }
      string n1 = s1, n2 = s2, n3 = s3;
      rep(i, s1.size()) n1[i] = (char)('0' + mp[s1[i]]);
      rep(i, s2.size()) n2[i] = (char)('0' + mp[s2[i]]);
      rep(i, s3.size()) n3[i] = (char)('0' + mp[s3[i]]);

      if (n1[0] == '0' || n2[0] == '0' || n3[0] == '0') {
        //　ダメ
      } else {
        ll nn1 = stoll(n1);
        ll nn2 = stoll(n2);
        ll nn3 = stoll(n3);
        if (nn1 + nn2 == nn3) {
          cout << n1 << endl;
          cout << n2 << endl;
          cout << n3 << endl;
          return;
        }
      }

    } while (next_permutation(perm.begin(), perm.end()));

    /* output */
    cout << "UNSOLVABLE" << endl;
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