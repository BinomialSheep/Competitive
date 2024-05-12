#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
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
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, n) cin >> a[i];

  /* solve */
  vector<bool> color(8, false);
  int any = 0;
  rep(i, n) {
    if (a[i] < 400)
      color[0] = true;
    else if (a[i] < 800)
      color[1] = true;
    else if (a[i] < 1200)
      color[2] = true;
    else if (a[i] < 1600)
      color[3] = true;
    else if (a[i] < 2000)
      color[4] = true;
    else if (a[i] < 2400)
      color[5] = true;
    else if (a[i] < 2800)
      color[6] = true;
    else if (a[i] < 3200)
      color[7] = true;
    else
      any++;
  }
  int ansMin = 0;
  rep(i, color.size()) {
    if (color[i]) ansMin++;
  }
  int ansMax = ansMin + any;
  // 全員が3200以上のケース
  if (ansMin == 0) ansMin = 1;

  /* output */
  cout << ansMin << " " << ansMax << endl;

  return 0;
}