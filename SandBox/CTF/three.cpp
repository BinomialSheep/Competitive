
#include <bits/stdc++.h>
using namespace std;

vector<int> flag_0 = {99, 0, 0,   0, 52,  0, 0,  0, 99,  0, 0,  0, 95, 0,
                      0,  0, 117, 0, 0,   0, 98, 0, 0,   0, 95, 0, 0,  0,
                      95, 0, 0,   0, 100, 0, 0,  0, 116, 0, 0,  0, 95, 0,
                      0,  0, 114, 0, 0,   0, 95, 0, 0,   0, 49, 0, 0,  0,
                      95, 0, 0,   0, 52,  0, 0,  0, 125, 0, 0,  0};
vector<int> flag_1 = {116, 0, 0, 0, 98,  0, 0, 0, 52,  0, 0, 0, 121, 0, 0, 0,
                      95,  0, 0, 0, 49,  0, 0, 0, 116, 0, 0, 0, 117, 0, 0, 0,
                      48,  0, 0, 0, 52,  0, 0, 0, 116, 0, 0, 0, 101, 0, 0, 0,
                      115, 0, 0, 0, 105, 0, 0, 0, 102, 0, 0, 0, 103, 0, 0, 0};
vector<int> flag_2 = {102, 0, 0, 0, 123, 0, 0, 0, 110, 0, 0, 0, 48,  0, 0, 0,
                      97,  0, 0, 0, 101, 0, 0, 0, 48,  0, 0, 0, 110, 0, 0, 0,
                      95,  0, 0, 0, 101, 0, 0, 0, 52,  0, 0, 0, 101, 0, 0, 0,
                      112, 0, 0, 0, 116, 0, 0, 0, 49,  0, 0, 0, 51,  0, 0, 0};

bool validate_flag(string argS) {
  char cVar1;

  if (argS.size() != 49) {
    puts("Invalid FLAG");
    return 1;
  }

  for (int i = 0; i < 49; i++) {
    if (i % 3 == 0) {
      cVar1 = (char)(flag_0[(i / 3) * 4]);
    } else if (i % 3 == 1) {
      cVar1 = (char)(flag_1[(i / 3) * 4]);
    } else {
      cVar1 = (char)(flag_2[(i / 3) * 4]);
    }
    cout << cVar1;
    // if (cVar1 != argS[i]) {
    //   puts("Invalid FLAG");
    //   return 1;
    // }
  }
  cout << endl;
  puts("Correct!");
  return 0;
}

int main() {
  string tmp = string(49, 'a');
  validate_flag(tmp);

  return 0;
}
