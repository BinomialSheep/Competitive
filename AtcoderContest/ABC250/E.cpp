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
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N;
  cin >> N;
  vi A(N);
  rep(i, N) cin >> A[i];
  vi B(N);
  rep(i, N) cin >> B[i];

  /* solve */
  // 前処理
  unordered_set as;
  unordered_set bs;
  vector<bool> res(N, false);
  rep(i, N) {
    if (A[i] == B[i]) {
      if (i == 0)
        res[i] = true;
      else
        res[i] = res[i - 1];
    } else {
      if (bs.count(A[i]) == 1) {
        bs.erase(A[i]);
      } else {
        as.insert(A[i]);
      }
      if (as.count(B[i]) == 1) {
        as.erase(B[i]);
      } else {
        bs.insert(B[i]);
      }
      if (A[i].size() == 0 && A[i].size() == 0) {
        res[i] = true;
      }
    }
  }
  // クエリ処理
  rep(i, Q) {
    int x, y
  }


  /* output */

  return 0;
}