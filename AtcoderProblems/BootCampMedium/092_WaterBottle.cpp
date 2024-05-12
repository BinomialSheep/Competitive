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
  double a, b, x;
  cin >> a >> b >> x;

  /* solve */
  double height = x / a / a;
  // cout << height << endl;

  double PI = 3.141592653589793;

  cout.precision(10);

  double deg = 0;

  if (b - height <= height) {
    double d = (b - height) * 2;
    // cout << d << endl;
    //  横がa、縦がdの三角形の角度を求める
    deg = atan2(d, a) * 180 / PI;
  } else {
    double width = a * height * 2 / b;
    deg = atan2(b, width) * 180 / PI;
  }

  /* output */
  cout << fixed << deg << endl;

  return 0;
}