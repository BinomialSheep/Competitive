#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N;
  cin >> N;
  int Ax, Ay, Bx, By;
  cin >> Ax >> Ay >> Bx >> By;
  --Ax;
  --Ay;
  --Bx;
  --By;
  vector<string> S(N);
  rep(i, N) cin >> S[i];
  /* solve */
  vector<vector<int>> d(N, vector<int>(N, INFTY));
  queue<pair<int, int>> q;
  q.push(make_pair(Ax, Ay));
  d[Ax][Ay] = 0;
  N--;

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    assert(d[x][y] < INFTY);


    int i = 1;
    while (x - i >= 0 && y - i >= 0 && S[x - i][y - i] == '.' &&
           d[x - i][y - i] > d[x][y] + 1) {
      d[x - i][y - i] = d[x][y] + 1;
      q.push(make_pair(x - i, y - i));
      i++;
    }
    i = 1;
    while (x - i >= 0 && y + i <= N && S[x - i][y + i] == '.' &&
           d[x - i][y + i] > d[x][y] + 1) {
      d[x - i][y + i] = d[x][y] + 1;
      q.push(make_pair(x - i, y + i));
      i++;
    }

    i = 1;
    while (x + i <= N && y - i >= 0 && S[x + i][y - i] == '.' &&
           d[x + i][y - i] > d[x][y] + 1) {
      d[x + i][y - i] = d[x][y] + 1;
      q.push(make_pair(x + i, y - i));
      i++;
    }

    i = 1;
    while (x + i <= N && y + i <= N && S[x + i][y + i] == '.' &&
           d[x + i][y + i] > d[x][y] + 1) {
      d[x + i][y + i] = d[x][y] + 1;
      q.push(make_pair(x + i, y + i));
      i++;
    }
  }

  /* output */
  // rep(i, N) {
  //   rep(j, N) { cout << (d[i][j] == INFTY ? -1 : d[i][j]) << " "; }
  //   cout << endl;
  // }
  cout << (d[Bx][By] == INFTY ? -1 : d[Bx][By]) << endl;

  return 0;
}