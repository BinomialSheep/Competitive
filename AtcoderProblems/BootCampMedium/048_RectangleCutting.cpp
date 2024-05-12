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

int main() {
  /* input */
  int W, H, x, y;
  cin >> W >> H >> x >> y;

  /* solve */
  // 自明な上界を達成できる
  double area = (double)W * H / 2;
  int flag = 0;

  if (W % 2 == 0 && x == W / 2 && H % 2 == 0 && y == H / 2) {
    flag = 1;
  }

  /* output */
  cout.precision(20);
  cout << fixed << area << " " << flag << endl;

  return 0;
}