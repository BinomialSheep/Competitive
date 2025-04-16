#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  /* input */
  string N;
  cin >> N;

  /* solve */
  auto naive = [](int N2) {
    auto sum = [](int x) {
      int ret = 0;
      while (x) {
        ret += x % 10;
        x /= 10;
      }
      return ret;
    };
    auto g = [sum](int x) -> bool { return x % sum(x) == 0; };

    vector<pair<int, int>> ret;
    for (int i = N2; i + 1 <= 2 * N2; i++) {
      if (g(i) && g(i + 1)) {
        ret.emplace_back(i, i + 1);
        return ret;
      }
    }
    return ret;
  };

  string ans = "";
  if (N.size() < 5) {
    auto vec = naive(stoi(N));
    if (vec.size() == 0) {
      ans = "-1";
    } else {
      ans = to_string(vec[0].first);
    }
  } else {
    if (N[0] >= '6') {
      ans = "11";
      rep(i, (int)N.size() - 1) ans.push_back('0');
    } else if (N[0] >= '4') {
      ans = "62";
      rep(i, (int)N.size() - 2) ans.push_back('0');
    } else if (N[0] == '3') {
      ans = "44";
      rep(i, (int)N.size() - 2) ans.push_back('0');
    } else if (N[0] == '2') {
      ans = "35";
      rep(i, (int)N.size() - 2) ans.push_back('0');
    } else if (N[0] == '1') {
      int ok = 0;
      for (int i = 1; i < (int)N.size(); i++)
        if (N[i] != '0') ok = 1;
      if (ok) {
        ans = "2";
        rep(i, (int)N.size() - 1) ans.push_back('0');
      } else {
        ans = "11";
        rep(i, (int)N.size() - 2) ans.push_back('0');
      }
    } else {
      assert(false);
    }
  }

  /* output */
  cout << ans << endl;
}
