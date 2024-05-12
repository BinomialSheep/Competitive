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

int main() {
  /* input */
  string S;
  cin >> S;

  /* solve */
  // 次がない
  if (S == "zyxwvutsrqponmlkjihgfedcba") {
    cout << -1 << endl;
    return 0;
  }

  // 25文字以下
  if ((int)S.size() <= 25) {
    vi used(26);
    rep(i, (int)S.size()) used[S[i] - 'a'] = 1;

    rep(i, 26) {
      if (!used[i]) {
        char c = (char)('a' + i);
        S.push_back(c);
        cout << S << endl;
        return 0;
      }
    }
  }

  // 26文字
  if ((int)S.size() == 26) {
    // どこを変えるか
    int idx;
    for (int i = 25; i >= 1; i--) {
      if (S[i - 1] < S[i]) {
        idx = i - 1;
        break;
      }
    }
    // 何に変えるか（S[idx]を超える最小のC
    char c = S[idx + 1];
    for (int i = idx + 1; i < (int)S.size(); i++) {
      if (S[idx] < S[i] && S[i] < c) {
        c = S[i];
      }
    }
    //
    string ans = S.substr(0, idx);
    ans.push_back(c);
    cout << ans << endl;
    return 0;
  }
  /* output */
  assert(false);

  return 0;
}