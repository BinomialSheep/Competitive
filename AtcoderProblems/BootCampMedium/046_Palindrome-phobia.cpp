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

int main() {
  /* input */
  string S;
  cin >> S;

  /* solve */
  // 2文字同じ文字が続いたらダメで、3文字がXYXのようになってもダメ
  // つまり、XYZ形の連続が最後まで続けばいい
  // 具体的には、a, b, cのmaxとminの差が1以下であればよい
  int a = 0, b = 0, c = 0;
  rep(i, S.size()) {
    if (S[i] == 'a')
      a++;
    else if (S[i] == 'b')
      b++;
    else
      c++;
  }

  /* output */
  // 例外
  if (S.size() == 1) {
    cout << "YES" << endl;
    return 0;
  }
  if ((a == 0 && b == 0) || (b == 0 && c == 0) || (c == 0 && a == 0)) {
    cout << "NO" << endl;
    return 0;
  }
  // 通常
  cout << (max(a, max(b, c)) - min(a, min(b, c)) <= 1 ? "YES" : "NO") << endl;

  return 0;
}