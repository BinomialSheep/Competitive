#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

void putQueen(int r, int c, vector<vector<int>>& b) {
  for (int i = -8; i <= 8; i++) {
    bool fr = 0 <= r + i && r + i <= 7;
    bool cr = 0 <= c + i && c + i <= 7;
    bool cr2 = 0 <= c - i && c - i <= 7;
    if (fr) b[r + i][c] = 1;
    if (cr) b[r][c + i] = 1;
    if (fr && cr) b[r + i][c + i] = 1;
    if (fr && cr2) b[r + i][c - i] = 1;
  }
  b[r][c] = 0;
}

vector<vector<int>> copyB(vector<vector<int>> b) {
  vector<vector<int>> copy(8, vector<int>(8, -1));
  rep(i, 8) rep(j, 8) copy[i][j] = b[i][j];
  return copy;
}

void printBoard(vector<vector<int>>& copy) {
  rep(i, 8) {
    rep(j, 8) {
      // cout << copy[i][j];
      if (copy[i][j] == 0) {
        cout << 'Q';
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}

int main() {
  vector<vector<int>> Board(8, vector<int>(8, -1));
  set<int> rSet;
  /* input */
  int k;
  cin >> k;
  rep(i, k) {
    int r, c;
    cin >> r >> c;
    rSet.insert(r);
    putQueen(r, c, Board);
  }

  /* solve */
  vector<int> ord;
  vector<int> org;
  rep(i, 8) {
    if (rSet.find(i) == rSet.end()) {
      org.push_back(i);
    }
  }
  rep(i, 8) ord.push_back(i);
  // rep(i, ord.size()) cout << ord[i] << endl;

  do {
    vector<vector<int>> copy = copyB(Board);
    bool flag = true;
    rep(i, org.size()) {
      // if (rSet.find(i) != rSet.end()) continue;
      if (copy[org[i]][ord[i]] != -1) {
        flag = false;
        break;
      }
      putQueen(org[i], ord[i], copy);
    }
    if (flag) {
      // rep(i, ord.size()) cout << ord[i] << endl;
      printBoard(copy);
      return 0;
    }
    // rep(i, ord.size()) cout << ord[i] << endl;
    // printBoard(copy);

  } while (next_permutation(ord.begin(), ord.end()));

  /* output */

  return 0;
}