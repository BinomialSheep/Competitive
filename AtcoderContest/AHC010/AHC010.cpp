#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

// タイルの状態
vector<vector<int>> initTiles(30, vector<int>(30));
vector<vector<int>> tiles(30, vector<int>(30));

// 状態t番のタイルに方向dから侵入した際の次のタイルの方向をto[t][d]とする
// ただしその方向から侵入不可能な場合は-1
vector<vector<int>> to = {
    {1, 0, -1, -1}, {3, -1, -1, 0}, {-1, -1, 3, 2}, {-1, 2, 1, -1},
    {1, 0, 3, 2},   {3, 2, 1, 0},   {2, -1, 0, -1}, {-1, 3, -1, 1},
};

// 方向を左上右下の順に0, 1, 2, 3と番号づけると、座標の変化は
vector<int> di = {0, -1, 0, 1};
vector<int> dj = {-1, 0, 1, 0};

// 答えを入れる
string ans;

// 環状線の長さを求める
int calcLen(int si, int sj, int sd) {
  // (si, sj) のタイルに sd
  // 方向のタイルから侵入した状態からスタートして環状線の長さを求める
  int i = si, j = sj, d = sd;
  int length = 0;
  while (true) {
    // 次のタイルの方向
    int d2 = to[tiles[i][j]][d];
    // 線路が途切れていたら長さ0
    if (d2 == -1) return 0;
    i += di[d2];
    j += dj[d2];
    // 線路が端で途切れたら長さ0
    if (i < 0 || i >= 30 || j < 0 || j >= 30) return 0;
    // 今いたタイルの方向
    d = (d2 + 2) % 4;
    length++;
    // 最初にいたタイルの位置、方向に返ってきたら終わり
    if (i == si && j == sj && d == sd) return length;
  }
}

void obvious() {
  rep(j, 30) {
    rep(k, 30) {
      // 自明な最適化
      if (tiles[j][k] == 0) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 2;
          else if (k == 29)
            tiles[j][k] = 1;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 3;
          else if (k == 29)
            tiles[j][k] = 0;
        }
      } else if (tiles[j][k] == 1) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 2;
          else if (k == 29)
            tiles[j][k] = 1;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 3;
          else if (k == 29)
            tiles[j][k] = 0;
        }
      } else if (tiles[j][k] == 2) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 2;
          else if (k == 29)
            tiles[j][k] = 1;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 3;
          else if (k == 29)
            tiles[j][k] = 0;
        }
      } else if (tiles[j][k] == 3) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 2;
          else if (k == 29)
            tiles[j][k] = 1;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 3;
          else if (k == 29)
            tiles[j][k] = 0;
        }
      } else if (tiles[j][k] == 4) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 4;
          else if (k == 29)
            tiles[j][k] = 5;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 5;
          else if (k == 29)
            tiles[j][k] = 4;
        }
      } else if (tiles[j][k] == 5) {
        if (j == 0) {
          if (k == 0)
            tiles[j][k] = 4;
          else if (k == 29)
            tiles[j][k] = 5;
        } else if (j == 29) {
          if (k == 0)
            tiles[j][k] = 5;
          else if (k == 29)
            tiles[j][k] = 4;
        }
      } else if (tiles[j][k] == 6) {
        if (k == 0 || k == 29) tiles[j][k] = 7;
      } else {
        if (j == 0 || j == 29) tiles[j][k] = 6;
      }
    }
  }
}

// 端をざっくりいい感じにする
void obvious2() {
  rep(j, 30) {
    rep(k, 30) {
      if (tiles[j][k] == 0) {
        if (j == 0) {
          // 1か2に変更するのがいい
          tiles[j][k] = 1;
        } else if (k == 0) {
          tiles[j][k] = 2;
        }
      }
      if (tiles[j][k] == 1) {
        if (j == 29) {
          tiles[j][k] = 0;
        } else if (k == 0) {
          tiles[j][k] = 2;
        }
      }
      if (tiles[j][k] == 2) {
        if (j == 29) {
          tiles[j][k] = 0;
        } else if (k == 29) {
          tiles[j][k] = 1;
        }
      }
      if (tiles[j][k] == 3) {
        if (j == 0) {
          tiles[j][k] = 2;
        } else if (k == 29) {
          tiles[j][k] = 1;
        }
      }
    }
  }
}

int rotateTile(int i, int j, int k) {
  if (tiles[i][j] <= 3) {
    tiles[i][j] = tiles[i][j] + (k + 4) % 4;
  } else if (tiles[i][j] <= 5) {
    tiles[i][j] = 4 + (tiles[i][j] + k) % 2;
  } else {
    tiles[i][j] = 6 + (tiles[i][j] + k) % 2;
  }
  return tiles[i][j];
}

// 今のタイル[i, j]をk回回転させた時の長さを求める
int rotateLen(int i, int j, int k) {
  rotateTile(i, j, k);
  int len;
  if (tiles[i][j] == 4) {
    len = max(calcLen(i, j, 0), calcLen(i, j, 2));
  } else if (tiles[i][j] == 5) {
    len = max(calcLen(i, j, 0), calcLen(i, j, 1));
  } else if (tiles[i][j] == 0 || tiles[i][j] == 1 || tiles[i][j] == 6) {
    len = calcLen(i, j, 0);
  } else if (tiles[i][j] == 2 || tiles[i][j] == 3) {
    len = calcLen(i, j, 2);
  } else {
    len = calcLen(i, j, 1);
  }

  return len;
}

// 周りを4 ^ 3 回くらい最適化する
int stupidRec(int i, int j, int depth, map<pair<int, int>, int> &mp,
              int limit) {
  int origin = tiles[i][j];
  //  何回回転させた時が1番スコアがいいか
  int maxScore = -1;
  int score = -1;
  int ro = tiles[i][j] <= 3 ? 3 : 1;
  for (int k = 0; k <= ro; k++) {
    if (depth == limit) {
      // k回回転させて改善するなら回転させる
      score = rotateLen(i, j, k);
      if (score >= maxScore) {
        maxScore = score;
        mp[make_pair(i, j)] = k;
      }
    } else {
      // 回転させる
      int kind = rotateTile(i, j, k);
      int thisScore = -1;
      pair<pair<int, int>, int> p;
      // 1個隣を回転させる（枝狩り）
      if (j != 0 &&
          (kind == 0 || kind == 1 || kind == 4 || kind == 5 || kind == 6)) {
        score = stupidRec(i, j - 1, depth + 1, mp, limit);
        if (score > thisScore) {
          thisScore = score;
          p.first = make_pair(i, j - 1);
          p.second = mp[make_pair(i, j - 1)];
        }
        mp[make_pair(i, j - 1)] = 0;
      }
      if (i != 0 &&
          (kind == 0 || kind == 3 || kind == 4 || kind == 5 || kind == 7)) {
        score = stupidRec(i - 1, j, depth + 1, mp, limit);
        if (score > thisScore) {
          thisScore = score;
          p.first = make_pair(i - 1, j);
          p.second = mp[make_pair(i - 1, j)];
        }
        mp[make_pair(i - 1, j)] = 0;
      }
      if (j != 29 &&
          (kind == 2 || kind == 3 || kind == 4 || kind == 5 || kind == 6)) {
        score = stupidRec(i, j + 1, depth + 1, mp, limit);
        if (score > thisScore) {
          thisScore = score;
          p.first = make_pair(i, j + 1);
          p.second = mp[make_pair(i, j + 1)];
        }
        mp[make_pair(i, j + 1)] = 0;
      }
      if (i != 29 &&
          (kind == 1 || kind == 2 || kind == 4 || kind == 5 || kind == 7)) {
        score = stupidRec(i + 1, j, depth + 1, mp, limit);
        if (score > thisScore) {
          thisScore = score;
          p.first = make_pair(i + 1, j);
          p.second = mp[make_pair(i + 1, j)];
        }
        mp[make_pair(i + 1, j)] = 0;
      }

      if (thisScore > maxScore) {
        maxScore = score;
        mp[p.first] = p.second;
        mp[make_pair(i, j)] = k;
      }
    }
    // tileを戻す
    tiles[i][j] = origin;
  }
  // 最適な回転数のmapが返る
  return maxScore;
}

// 5回最適化しても2^10 * 30 * 30 = 9 * 10^5程度のループのはず
void stupidSearch(int limit) {
  for (int i = 1; i <= 28; i++) {
    for (int j = 1; j <= 28; j++) {
      map<pair<int, int>, int> mp;
      stupidRec(i, j, 0, mp, limit);
      int k = mp[make_pair(i, j)];
      // 回転させる
      if (tiles[i][j] <= 3) {
        tiles[i][j] = tiles[i][j] + (k + 4) % 4;
      } else if (tiles[i][j] <= 5) {
        tiles[i][j] = 4 + (tiles[i][j] + k) % 2;
      } else {
        tiles[i][j] = 6 + (tiles[i][j] + k) % 2;
      }
    }
  }
}

void calcRotate() {
  rep(i, 30) {
    rep(j, 30) {
      int num;
      if (tiles[i][j] <= 3) {
        num = (4 + tiles[i][j] - initTiles[i][j]) % 4;
      } else {
        num = (2 + tiles[i][j] - initTiles[i][j]) % 2;
      }
      ans[30 * i + j] = (char)('0' + num);
    }
  }
}

int main() {
  /* input */
  rep(i, 30) {
    string s;
    cin >> s;
    rep(j, 30) initTiles[i][j] = tiles[i][j] = s[j] - '0';
  }
  // 回転数の初期化
  rep(i, 900) ans.push_back('0');
  cout << ans << endl;

  /* solve */
  // ざっくり最適化
  obvious2();
  calcRotate();
  cout << ans << endl;
  // 自明な最適化
  obvious();
  calcRotate();
  cout << ans << endl;

  // 隣まで読んで最適化
  stupidSearch(4);
  calcRotate();
  cout << ans << endl;

  // 再調整
  obvious2();
  obvious();
  // 1個だけ見て最適化する
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;
  stupidSearch(1);
  calcRotate();
  cout << ans << endl;
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;
  stupidSearch(1);
  calcRotate();
  cout << ans << endl;
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;
  stupidSearch(1);
  calcRotate();
  cout << ans << endl;
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;
  stupidSearch(1);
  calcRotate();
  cout << ans << endl;
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;
  stupidSearch(0);
  calcRotate();
  cout << ans << endl;

  /* output */
  calcRotate();
  cout << ans << endl;

  return 0;
}