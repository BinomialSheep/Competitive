#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

/*
double distance(int ax, int ay, int bx, int by) {
  return sqrt(abs(ax - bx) * abs(ax - bx) + abs(ay - by) * abs(ay - by));
}
*/

int main() {
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  int xDis = abs(x2 - x1);
  int yDis = abs(y2 - y1);

  bool isYes = false;

  if (xDis == 0 && (yDis == 2 || yDis == 4)) {
    isYes = true;
  } else if (xDis == 1 && (yDis == 1 || yDis == 3)) {
    isYes = true;
  } else if (xDis == 2 && (yDis == 0 || yDis == 4)) {
    isYes = true;
  } else if (xDis == 3 && (yDis == 1 || yDis == 3)) {
    isYes = true;
  } else if (xDis == 4 && (yDis == 0 || yDis == 2)) {
    isYes = true;
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}