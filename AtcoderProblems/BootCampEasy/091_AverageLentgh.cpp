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

double distance(int x1, int y1, int x2, int y2) {
  return sqrt(abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2));
}

int factorial(int n) {
  if (n == 1) return 1;
  return n * factorial(n - 1);
}

int main() {
  // input
  int n;
  cin >> n;
  vector<pair<int, int>> points(n);
  rep(i, n) {
    int x, y;
    cin >> x >> y;
    points[i].first = x;
    points[i].second = y;
  }
  // solve
  // 各点間の距離(nC2通り)を求めておく
  vector<double> distanceVec;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      int x1 = points[i].first;
      int y1 = points[i].second;
      int x2 = points[j].first;
      int y2 = points[j].second;

      distanceVec.push_back(distance(x1, y1, x2, y2));
    }
  }
  // 各点間の距離は、全経路に等しい回数表れる
  // 具体的にはそれぞれn!（経路の数）* n-1(1経路あたりの経路間の数) / nC2回
  int facN = factorial(n);
  int num = facN * (n - 1) / (n * (n - 1) / 2);

  double sum = 0;
  for (auto dist : distanceVec) {
    // cout << dist << endl;
    sum += dist * num;
  }

  // out
  cout.precision(15);
  cout << fixed << sum / facN << endl;

  return 0;
}