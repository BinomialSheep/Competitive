#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  int x3, y3, x4, y4;
  if (x2 - x1 >= 0 && y2 - y1 >= 0) {
    x3 = x2 - abs(y2 - y1);
    y3 = y2 + abs(x2 - x1);
    x4 = x1 - abs(y2 - y1);
    y4 = y1 + abs(x2 - x1);
  } else if (x2 - x1 < 0 && y2 - y1 >= 0) {
    x3 = x2 - abs(y2 - y1);
    y3 = y2 - abs(x1 - x2);
    x4 = x1 - abs(y2 - y1);
    y4 = y1 - abs(x1 - x2);
  } else if (x2 - x1 < 0) {
    x3 = x2 + abs(y1 - y2);
    y3 = y2 - abs(x1 - x2);
    x4 = x1 + abs(y1 - y2);
    y4 = y1 - abs(x1 - x2);
  } else {
    x3 = x2 + abs(y1 - y2);
    y3 = y2 + abs(x2 - x1);
    x4 = x1 + abs(y1 - y2);
    y4 = y1 + abs(x2 - x1);
  }
  printf("%d %d %d %d\n", x3, y3, x4, y4);

  return 0;
}