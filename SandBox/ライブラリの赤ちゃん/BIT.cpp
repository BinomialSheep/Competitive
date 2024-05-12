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

// https://algo-logic.info/binary-indexed-tree/
template <typename T>
struct BIT {
  int n;          // 配列の要素数(数列の要素数+1)
  vector<T> bit;  // データの格納先(1-indexed)。初期値は0
  BIT(int n_) : n(n_ + 1), bit(n, 0) {}

  // 1点加算（a_i += x）
  void add(int i, T x) {
    // iから始めて、iに最後の1が立っているビットを加算（区間分をどんどん足している）
    for (int idx = i; idx < n; idx += (idx & -idx)) {
      bit[idx] += x;
    }
  }

  // a_1 + a_2 + ... + a_i の取得
  T sum(int i) {
    T s(0);
    // i からはじめて、 iに最後の1が立っているビットを減算しながら、
    //場所iの値を合計
    for (int idx = i; idx > 0; idx -= (idx & -idx)) {
      s += bit[idx];
    }
    return s;
  }

  // BIT上の二分探索
  // a_1 + a_2 + ... + a_x >= w となるような最小の x
  // を求める(ただし a_i >= 0)
  int lower_bound(T w) {
    if (w <= 0) {
      return 0;
    } else {
      int x = 0, r = 1;
      while (r < n) r = r << 1;
      // 長さlenは1段下るごとに半分に
      for (int len = r; len > 0; len = len >> 1) {
        if (x + len < n && bit[x + len] < w) {  // 採用するとき
          w -= bit[x + len];
          x += len;
        }
      }
      return x + 1;
    }
  }
};

int main() {
  /* input */

  /* solve */

  /* output */

  return 0;
}