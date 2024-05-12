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
  ll K;
  cin >> S >> K;

  /* solve */
  if ((int)S.size() == 1) {
    cout << K / 2 << endl;
    return 0;
  }
  if (S[0] != S.back()) {
    // 全部バラせる
    vi vec;
    int cnt = 0;
    rep(i, (int)S.size()) {
      if (i == 0 || S[i] != S[i - 1]) {
        if (cnt != 0) vec.push_back(cnt + 1);
        cnt = 0;
      } else {
        cnt++;
      }
    }
    if (cnt != 0) vec.push_back(cnt + 1);
    ll ans = 0;
    for (auto v : vec) {
      ans += v / 2;
    }
    ans *= K;
    cout << ans << endl;
    return 0;
  }

  vi vec;
  int cnt = 0;
  rep(i, (int)S.size()) {
    if (i == 0 || S[i] != S[i - 1]) {
      if (cnt != 0) vec.push_back(cnt + 1);
      cnt = 0;
    } else {
      cnt++;
    }
  }
  if (cnt != 0) vec.push_back(cnt + 1);

  if (K == 1) {
    ll ans = 0;
    for (auto v : vec) {
      ans += v / 2;
    }
    cout << ans << endl;
    return 0;
  }

  // 最初と最後の連続
  ll fstCnt = 1;
  rep(i, (int)S.size()) {
    if (i == 0) continue;
    if (S[i] != S[i - 1])
      break;
    else
      fstCnt++;
  }
  ll lastCnt = 1;
  for (int i = (int)S.size() - 1; i >= 0; i--) {
    if (i == (int)S.size() - 1) continue;
    if (S[i] != S[i + 1])
      break;
    else
      lastCnt++;
  }

  if (fstCnt == (int)S.size()) {
    ll ans = fstCnt * K / 2;
    cout << ans << endl;
    return 0;
  }

  // cout << fstCnt << " " << lastCnt << endl;

  //
  ll ans = 0;

  assert(K != 0);

  if (fstCnt == 1 && lastCnt == 1) {
    for (auto v : vec) {
      ans += (ll)K * (v / 2);
    }
    ans += K - 1;
  }

  if (fstCnt != 1 && lastCnt == 1) {
    rep(i, (int)vec.size()) {
      if (i == 0) {
        ans += (ll)(K - 1) * ((fstCnt + lastCnt) / 2);
        ans += fstCnt / 2;
      } else {
        ans += (ll)K * (vec[i] / 2);
      }
    }
  }

  if (fstCnt == 1 && lastCnt != 1) {
    if (vec.size() == 1) {
      ans += (ll)(K - 1) * ((1 + lastCnt) / 2);
      ans += lastCnt / 2;
      cout << ans << endl;
      return 0;
    }

    rep(i, (int)vec.size()) {
      if (i == (int)vec.size() - 1) {
        assert(vec[i] == lastCnt);
        ans += (ll)(K - 1) * ((1 + lastCnt) / 2);
        ans += lastCnt / 2;
      } else {
        ans += (ll)K * (vec[i] / 2);
      }
    }
  }

  if (fstCnt != 1 && lastCnt != 1 && vec.size() == 1) {
    assert(false);
  }

  if (fstCnt != 1 && lastCnt != 1) {
    rep(i, (int)vec.size()) {
      if (i == 0) {
        // 最初の1回だけカウント
        ans += fstCnt / 2;
      } else if (i == (int)vec.size() - 1) {
        ans += (ll)(K - 1) * ((fstCnt + lastCnt) / 2);
        ans += lastCnt / 2;
      } else {
        ans += (ll)K * (vec[i] / 2);
      }
    }
  }

  cout << ans << endl;

  /* output */

  return 0;
}