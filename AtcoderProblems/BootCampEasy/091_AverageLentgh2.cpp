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
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int factorial(int n) {
  if (n == 1) return 1;
  return n * factorial(n - 1);
}

// next_permutationを使って解く
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
  double sum = 0;
  // 0からn-1の配列
  vector<int> path(n);
  rep(i, n) path[i] = i;
  // pathを更新しながら全通り試す
  do {
    for (int i = 0; i < n - 1; i++) {
      int x1 = points[path[i]].first;
      int y1 = points[path[i]].second;
      int x2 = points[path[i + 1]].first;
      int y2 = points[path[i + 1]].second;

      sum += distance(x1, y1, x2, y2);
    }

  } while (next_permutation(path.begin(), path.end()));

  // out
  cout.precision(15);
  cout << fixed << sum / factorial(n) << endl;

  return 0;
}