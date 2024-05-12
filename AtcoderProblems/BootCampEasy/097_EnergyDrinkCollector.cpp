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
  // input
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> AB;
  rep(i, n) {
    int A, B;
    cin >> A >> B;
    AB.emplace_back(A, B);
  }
  // solve
  // 安い順にソートして貪欲法
  sort(AB.begin(), AB.end());
  ll cost = 0;
  rep(i, n) {
    ll A = AB[i].first;
    ll B = AB[i].second;
    if (m > B) {
      m -= B;
      cost += A * B;
    } else {
      cost += A * m;
      break;
    }
  }
  //
  cout << cost << endl;

  return 0;
}