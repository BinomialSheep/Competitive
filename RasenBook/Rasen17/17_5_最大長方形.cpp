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

struct Rectangle {
  int height;
  // 左端
  int pos;
};

int main() {
  // input
  int H, W;
  cin >> H >> W;
  vector<vector<int>> c(H, vector<int>(W));
  rep(i, H) rep(j, W) cin >> c[i][j];

  // solve

  // 上方向に続くキレイなタイルの数を求めておく
  // T[i][j]は[i][j]を含めて上方向に連続するキレイなタイルの数
  // W+1としているのは、あとでT[i][W]を使いたいため
  vector<vector<int>> T(H, vector<int>(W + 1, 0));
  // 1行目はそのタイルの汚れのみで決まる
  rep(j, W) T[0][j] = (c[0][j] == 1) ? 0 : 1;
  // 縦方向に走査する必要がある
  rep(j, W) for (int i = 1; i < H; i++) {
    // タイル[i][j]自身が汚ければ0
    if (c[i][j]) continue;
    // タイルがキレイなら、1行目上の数+1
    T[i][j] = T[i - 1][j] + 1;
  }

  //
  int maxv = 0;
  rep(i, H) {
    stack<Rectangle> S;

    vector<int> buffer = T[i];

    rep(j, W + 1) {
      Rectangle rect;
      rect.height = buffer[j];
      rect.pos = j;
      if (S.empty()) {
        // スタックが空なら追加
        S.push(rect);
      } else {
        if (S.top().height < rect.height) {
          // 今積む方が大きいならスタックに積んで続行
          S.push(rect);
        } else if (S.top().height > rect.height) {
          // 今積む方が小さいなら、直前までの高さの面積を確定させる
          int target = j;
          while (!S.empty() && S.top().height >= rect.height) {
            Rectangle pre = S.top();
            S.pop();
            int area = pre.height * (j - pre.pos);
            // cout << "i, j " << i << " " << j << " "
            //      << "height, pos, area:" << pre.height << " " << pre.pos << "
            //      "
            //      << area << endl;
            maxv = max(maxv, area);
            target = pre.pos;
          }
          rect.pos = target;
          S.push(rect);
        }
      }
    }
  }

  cout << maxv << endl;

  return 0;
}