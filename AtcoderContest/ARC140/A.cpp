#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
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

int main() {
  /* input */
  int N, K;
  cin >> N >> K;
  string S;
  cin >> S;

  /* solve */
  if (N == 1) {
    cout << 1 << endl;
    return 0;
  }
  int ans = N;
  for (int i = 1; i <= N / 2; i++) {
    // i種類にできますか？という問題を解く
    // 明らかに約数でない種類にはならない
    if (N % i != 0) continue;

    vvi cnt(i, vi(26));
    //
    rep(j, N) {
      int idx = j % i;
      // cout << idx << " " << S[j] - 'a' << endl;
      cnt[idx][S[j] - 'a']++;
    }
    //
    int change = 0;
    for (auto vec : cnt) {
      int mc = -1;
      for (auto v : vec) {
        // 1番数が多い文字に合わせる
        mc = max(mc, v);
      }
      // 何文字変更しなければいけないか
      change += N / i - mc;
    }
    // 判定
    if (change <= K) {
      ans = i;
      break;
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}