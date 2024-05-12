#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
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
  string S;
  cin >> N >> S;

  /* solve */
  multiset<int> nums;

  int cntA = 0;
  int cntR = 0;
  int cntC = 0;
  if (S[0] == 'A') cntA++;
  for (int i = 1; i < N; i++) {
    if (S[i] == 'A') {
      if (cntA && cntC) {
        // ARC成功
        nums.insert(min(cntA, cntC));
        cntR = 0;
        cntC = 0;
        cntA = 1;
      } else if (cntR) {
        // ARC失敗
        cntR = 0;
        cntC = 0;
        cntA = 1;
      } else {
        // Aの連続するところ
        cntA++;
      }
    } else if (S[i] == 'R') {
      if (cntA && cntC) {
        // ARC成功
        nums.insert(min(cntA, cntC));
        cntA = 0;
        cntC = 0;
      } else if (cntR) {
        // ARC失敗
        cntA = 0;
        cntC = 0;
      }
      cntR++;
    } else {
      if (cntR != 1 || !cntA) {
        // ARC失敗
        cntA = 0;
        cntR = 0;
        cntC = 0;
      } else {
        // ARC継続
        cntC++;
      }
    }
  }
  // 最後の分
  if (cntA && cntC) {
    nums.insert(min(cntA, cntC));
  }

  // debug
  // for (auto num : nums) cout << num << endl;

  // シミュレーション
  int ans = 0;
  bool isEven = false;
  while (!nums.empty()) {
    if (isEven) {
      auto lt = nums.lower_bound(1);
      if (lt == nums.end()) break;
      nums.erase(lt);
    } else {
      auto lt = nums.lower_bound(2);
      if (lt == nums.end()) {
        lt = nums.lower_bound(1);
        if (lt == nums.end()) break;
        nums.erase(lt);
      } else {
        int v = *lt - 1;
        nums.erase(lt);
        nums.insert(v);
      }
    }
    ans++;
    isEven = !isEven;
  }

  /* output */
  cout << ans << endl;

  return 0;
}