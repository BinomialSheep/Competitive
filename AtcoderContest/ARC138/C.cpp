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

int k;
ll s;

void stupid(int N, vector<int>& A) {
  rep(j, N) {
    priority_queue<int, vector<int>, greater<int>> que;
    ll score = 0;
    int i = j;
    int turn = 1;
    while (true) {
      que.push(A[i]);
      if (turn % 2 == 0) {
        turn = 0;
        score += que.top();
        // cout << "que:" << que.top();
        que.pop();
      }
      i++;
      turn++;
      if (i == N) i = 0;
      if (i == j) break;
    }

    // cout << j << " " << score << endl;

    if (score < s) {
      k = j;
      s = score;
    }
  }
}

int main() {
  /* input */
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  int minI;
  int minV = (1 << 30);
  rep(i, N) {
    if (minV > A[i]) {
      minI = i;
    }
  }

  // init
  s = (1LL << 62);

  /* solve */
  // 最小太郎は、[0, 1]で1番小さい数、[0, 4]で2番目に小さい数、[0,
  // 6]で3番目に小さい数、...[0, N]でN/2番目に小さい数を取る
  // stupid(N, A);

  priority_queue<int, vector<int>, greater<int>> que;
  ll score = 0;
  int i = minI;
  int turn = 1;
  while (true) {
    que.push(A[i]);
    if (turn % 2 == 0) {
      turn = 0;
      score += que.top();
      // cout << "que:" << que.top();
      que.pop();
    }
    i++;
    turn++;
    if (i == N) i = 0;
    if (i == minI) break;
  }

  // cout << j << " " << score << endl;

  ll sum = 0;
  rep(i, N) sum += A[i];

  /* output */
  cout << minI << " " << sum - score << endl;

  return 0;
}