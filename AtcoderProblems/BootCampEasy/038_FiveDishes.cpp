#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int a, b, c, d, e;
  cin >> a >> b >> c >> d >> e;

  // 1桁目が1以上で1番小さい数字を最後に頼めばいい
  int a1 = a % 10, b1 = b % 10, c1 = c % 10, d1 = d % 10, e1 = e % 10;
  int aRoundUp = (a1 == 0 ? a : a + 10 - a1);
  int bRoundUp = (b1 == 0 ? b : b + 10 - b1);
  int cRoundUp = (c1 == 0 ? c : c + 10 - c1);
  int dRoundUp = (d1 == 0 ? d : d + 10 - d1);
  int eRoundUp = (e1 == 0 ? e : e + 10 - e1);
  int sumRoundUp = aRoundUp + bRoundUp + cRoundUp + dRoundUp + eRoundUp;

  vector<int> not0List;
  if (a1 != 0) not0List.push_back(a1);
  if (b1 != 0) not0List.push_back(b1);
  if (c1 != 0) not0List.push_back(c1);
  if (d1 != 0) not0List.push_back(d1);
  if (e1 != 0) not0List.push_back(e1);

  if (not0List.empty()) {
    cout << a + b + c + d + e << endl;
    return 0;
  }
  int min1 = 10;
  for (auto v : not0List) min1 = min(min1, v);

  int ans;
  if (min1 == a1) {
    ans = sumRoundUp - aRoundUp + a;
  } else if (min1 == b1) {
    ans = sumRoundUp - bRoundUp + b;
  } else if (min1 == c1) {
    ans = sumRoundUp - cRoundUp + c;
  } else if (min1 == d1) {
    // cout << sumRoundUp << " " << dRoundUp << " " << d << endl;
    ans = sumRoundUp - dRoundUp + d;
  } else {
    ans = sumRoundUp - eRoundUp + e;
  }

  cout << ans << endl;

  return 0;
}