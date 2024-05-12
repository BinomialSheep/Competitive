#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

double f(double x, double p) { return x + p * pow(0.5, x / 1.5); }

int main() {
  /* input */
  double p;
  cin >> p;

  // 三分探索で解く
  // 範囲の下限と上限の初期値
  double lb = 0, ub = p;
  // 200回くらいやっておけば誤差の範囲に収まっている
  rep(i, 200) {
    // 3等分した点
    double t1 = (2.0 * lb + ub) / 3.0;
    double t2 = (lb + 2.0 * ub) / 3.0;

    // t2年後の方が速ければ探索範囲を右側に縮められる
    // ↑ f(t1) > ans > f(t2)の場合もf(t1) > ans > f(t2)の場合も
    if (f(t1, p) > f(t2, p))
      lb = t1;
    else
      ub = t2;
  }

  /* output */
  cout.precision(10);
  cout << fixed << f(lb, p) << endl;

  return 0;
}