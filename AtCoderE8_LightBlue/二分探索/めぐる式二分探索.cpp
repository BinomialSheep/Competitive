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

vector<int> a = {1, 14, 32, 51, 51, 51, 243, 419, 750, 910};

// indexが条件を満たすかどうか
bool isOK(int index, int key) {
  if (a[index] >= key)
    return true;
  else
    return false;
}

// 汎用的な二分探索のテンプレ
int binarySearch(int key) {
  // index=0が条件を満たすこともあるので初期値は-1
  int ng = -1;
  // index = a.size()-1が条件を満たさないこともあるので初期値はa.size
  int ok = (int)a.size();

  // okとngのどちらが大きいか分からないことを考慮
  while (abs(ok - ng) > 1) {
    int mid = (ok + ng) / 2;

    if (isOK(mid, key))
      ok = mid;
    else
      ng = mid;
  }
  // okな最小のindexを返す
  return ok;
}

int main() {
  /* input */
  /* solve */

  /* output */
  // key以上の最小のindexが返ってくる
  cout << binarySearch(51) << endl;
  cout << binarySearch(1) << endl;
  cout << binarySearch(910) << endl;

  cout << binarySearch(52) << endl;
  cout << binarySearch(0) << endl;
  // 10 (場外)
  cout << binarySearch(911) << endl;

  return 0;
}