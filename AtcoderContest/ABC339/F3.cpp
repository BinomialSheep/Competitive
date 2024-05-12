#include <bits/stdc++.h>
using namespace std;
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

int main() {
  long MOD1 = 100000123;
  long MOD2 = 100000193;
  /* input */
  int N;
  cin >> N;

  vector<long> vec1(N), vec2(N);
  for (int i = 0; i < N; i++) {
    string S;
    cin >> S;
    vec1[i] = stoll((cpp_int(S) % MOD1).str());
    vec2[i] = stoll((cpp_int(S) % MOD2).str());
  }

  /* solve */
  map<long, int> mp1, mp2;
  for (int i = 0; i < N; i++) mp1[vec1[i]]++, mp2[vec2[i]]++;

  long ans = 0;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      long v1 = (vec1[i] * vec1[j]) % MOD1;
      long v2 = (vec2[i] * vec2[j]) % MOD2;
      ans += min(mp1[v1], mp2[v2]);
    }

  /* output */
  cout << ans << endl;
}
