#include <bits/stdc++.h>

#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
typedef long long ll;

int main() {
  ll n;
  cin >> n;
  if (pow(2, n) > n * n)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;

  return 0;
}