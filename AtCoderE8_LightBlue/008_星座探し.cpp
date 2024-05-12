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
  int m, n;
  cin >> m;
  vector<pair<int, int>> Constellation(m);
  rep(i, m) cin >> Constellation[i].first >> Constellation[i].second;
  cin >> n;
  vector<pair<int, int>> Stars(n);
  rep(i, n) cin >> Stars[i].first >> Stars[i].second;

  /* solve */
  // ソートしておく
  sort(Stars.begin(), Stars.end());
  // Constellation[0]がStars[i]から始まると仮定して、星座の位置に星が存在するかチェックする。どこかで存在しない座標があれば次のループへ
  rep(i, n) {
    // x, yへどれだけ平行移動するか
    int x = Stars[i].first - Constellation[0].first;
    int y = Stars[i].second - Constellation[0].second;
    //
    bool flag = true;
    for (int j = 1; j < m; j++) {
      if (!binary_search(Stars.begin(), Stars.end(),
                         make_pair(Constellation[j].first + x,
                                   Constellation[j].second + y))) {
        // 星座と仮定した時に存在するはずの座標に星が存在しないなら、falseとして次のループへ
        flag = false;
        break;
      }
    }
    if (flag) {
      // 星座と合致した場合
      cout << x << " " << y << endl;
      return 0;
    }
  }

  return 0;
}