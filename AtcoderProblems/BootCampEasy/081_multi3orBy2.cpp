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

int main() {
  int n;
  vector<ll> a(n);
  cin >> n;
  rep(i, n) cin >> a[i];

  // 全部が奇数になった時点で終わり
  int cnt = 0;
  rep(i, n) {
    int tempCnt = 0;
    while (a[i] % 2 == 0) {
      a[i] /= 2;
      cnt++;
    }
  }

  cout << cnt << endl;

  return 0;
}