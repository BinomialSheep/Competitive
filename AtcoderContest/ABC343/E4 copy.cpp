#include <bits/stdc++.h>

using namespace std;

int f(int a1, int b1, int c1, int a2, int b2, int c2) {
  int res = 1;
  res *= max(0, min(a1, a2) + 7 - max(a1, a2));
  res *= max(0, min(b1, b2) + 7 - max(b1, b2));
  res *= max(0, min(c1, c2) + 7 - max(c1, c2));
  return res;
}

int f(int a1, int b1, int c1, int a2, int b2, int c2, int a3, int b3, int c3) {
  int res = 1;
  res *= max(0, min({a1, a2, a3}) + 7 - max({a1, a2, a3}));
  res *= max(0, min({b1, b2, b3}) + 7 - max({b1, b2, b3}));
  res *= max(0, min({c1, c2, c3}) + 7 - max({c1, c2, c3}));
  return res;
}

int main() {
  int v1, v2, v3;
  cin >> v1 >> v2 >> v3;
  for (int a2 = -7; a2 <= 7; a2++) {
    for (int b2 = -7; b2 <= 7; b2++) {
      for (int c2 = -7; c2 <= 7; c2++) {
        for (int a3 = -7; a3 <= 7; a3++) {
          for (int b3 = -7; b3 <= 7; b3++) {
            for (int c3 = -7; c3 <= 7; c3++) {
              int nv3 = f(0, 0, 0, a2, b2, c2, a3, b3, c3);
              int nv2 = f(0, 0, 0, a2, b2, c2) + f(0, 0, 0, a3, b3, c3) +
                        f(a2, b2, c2, a3, b3, c3) - nv3 * 3;
              int nv1 = 3 * 7 * 7 * 7 - nv2 * 2 - nv3 * 3;
              if (v1 != nv1 or v2 != nv2 or v3 != nv3) continue;
              printf("Yes\n0 0 0 %d %d %d %d %d %d\n", a2, b2, c2, a3, b3, c3);
              return 0;
            }
          }
        }
      }
    }
  }
  cout << "No" << endl;
}
