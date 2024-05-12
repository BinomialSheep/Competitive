#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

vector<bool> isPrimeList(201, false);

void setPrime() {
  isPrimeList[2] = isPrimeList[3] = isPrimeList[5] = isPrimeList[7] = true;
  isPrimeList[11] = isPrimeList[13] = isPrimeList[17] = isPrimeList[19] = true;
  isPrimeList[23] = isPrimeList[29] = isPrimeList[31] = isPrimeList[37] = true;
  isPrimeList[41] = isPrimeList[43] = isPrimeList[47] = true;
  isPrimeList[53] = isPrimeList[59] = isPrimeList[61] = isPrimeList[67] = true;
  isPrimeList[71] = isPrimeList[73] = isPrimeList[79] = true;
  isPrimeList[83] = isPrimeList[89] = isPrimeList[97] = true;
  isPrimeList[101] = isPrimeList[103] = isPrimeList[107] = isPrimeList[109] =
      true;
  isPrimeList[113] = isPrimeList[127] = isPrimeList[131] = isPrimeList[137] =
      true;
  isPrimeList[139] = isPrimeList[149] = isPrimeList[151] = isPrimeList[157] =
      true;
  isPrimeList[163] = isPrimeList[167] = isPrimeList[173] = isPrimeList[179] =
      true;
  isPrimeList[181] = isPrimeList[191] = isPrimeList[193] = isPrimeList[197] =
      isPrimeList[199] = true;
}

int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;

  setPrime();

  bool isTakahashi = false;
  bool isAoki = false;
  for (int i = a; i <= b; i++) {
    isAoki = false;
    for (int j = c; j <= d; j++) {
      if (isPrimeList[i + j]) {
        // 特定のjを選ぶことでiに対して青木が勝つ
        isAoki = true;
        break;
      }
    }
    // どのjを選んでも青木が勝てないなら、そのiで高橋は勝つ
    if (!isAoki) {
      isTakahashi = true;
      break;
    }
  }

  cout << (isTakahashi ? "Takahashi" : "Aoki") << endl;

  return 0;
}