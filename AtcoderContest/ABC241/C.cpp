#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  int n;
  cin >> n;
  vector<string> S(n);
  rep(i, n) cin >> S[i];

  bool isYes = false;
  // 横
  rep(i, n) {
    int num = 0;
    for (int j = 0; j <= 5; j++) {
      if (S[i][j] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int j = 6; j < n; j++) {
      if (S[i][j] == '#') num++;
      if (S[i][j - 6] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }

  // 縦
  rep(i, n) {
    int num = 0;
    for (int j = 0; j <= 5; j++) {
      if (S[j][i] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int j = 6; j < n; j++) {
      if (S[j][i] == '#') num++;
      if (S[j - 6][i] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }

  // 右下がり斜め（1行目スタート）
  for (int i = 0; i < n - 5; i++) {
    // 0行目, i列目から始まる
    int num = 0;
    for (int k = 0; k <= 5; k++) {
      if (S[k][i + k] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int k = 6; i + k < n; k++) {
      if (S[k][i + k] == '#') num++;
      if (S[k - 6][i + k - 6] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }
  // 右下がり斜め（1列目スタート)
  for (int i = 0; i < n - 5; i++) {
    // 0行目, i列目から始まる
    int num = 0;
    for (int k = 0; k <= 5; k++) {
      if (S[i + k][k] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int k = 6; i + k < n; k++) {
      if (S[i + k][k] == '#') num++;
      if (S[i + k - 6][k - 6] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }

  // 左下がり斜め（1列目スタート）
  for (int i = 5; i < n - 5; i++) {
    // 0行目, i列目から始まる
    int num = 0;
    for (int k = 0; k <= 5; k++) {
      if (S[i - k][k] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int k = 6; k < i + 1; k++) {
      //  cout << "i, k: " << i << " " << k << endl;
      if (S[i - k][k] == '#') num++;
      if (S[i - k + 6][k - 6] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }

  // 左下がり斜め（n-1行目スタート）
  for (int i = 0; i < n - 5; i++) {
    // n-1行目, i列目から始まる
    int num = 0;
    for (int k = 0; k <= 5; k++) {
      if (S[n - 1 - k][i + k] == '#') num++;
    }
    if (num >= 4) {
      isYes = true;
      break;
    }
    for (int k = 6; i + k < n; k++) {
      if (S[n - 1 - k][i + k] == '#') num++;
      if (S[n - 1 - k + 6][i + k - 6] == '#') num--;
      if (num >= 4) {
        isYes = true;
        break;
      }
    }
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}