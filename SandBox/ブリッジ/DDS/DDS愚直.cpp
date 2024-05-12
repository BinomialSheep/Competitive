#include <bits/stdc++.h>
using namespace std;

class Card {
 public:
  char suit, number;
  Card(string s) {
    assert(s.size() == 2);
    suit = s[0];
    number = s[1];
  }
  static bool isSameSuit(Card c1, Card c2) { return c1.suit == c2.suit; }
  static bool isStrong(Card c1, Card c2) {
    string s = "AKQJT98765432";
    int idx1, idx2;
    for (int i = 0; i < 13; i++) {
      if (c1.number == s[i]) idx1 = i;
      if (c2.number == s[i]) idx2 = i;
    }
    return idx1 < idx2;
  }
};
bool operator==(Card card1, Card card2) {
  return card1.suit == card2.suit && card1.number == card2.number;
}
bool operator!=(Card card1, Card card2) { return !(card1 == card2); }

class Hand {
 public:
  vector<vector<Card>> hands;
  Hand(vector<string> vec) {
    hands.resize(4);
    assert(vec.size() == 4);
    for (int i = 0; i < 4; i++) {
      for (char c2 : vec[i]) {
        char c1 = "SHDC"[i];
        Card card(string({c1, c2}));
        hands[i].push_back(card);
      }
    }
  }
  void erase(Card card) {
    vector<Card> tmp;
    int idx = 0;
    for (; idx < 4; idx++)
      if ("SHDC"[idx] == card.suit) break;
    for (Card card2 : hands[idx])
      if (card != card2) tmp.push_back(card2);
    swap(tmp, hands[idx]);
    // auto it = remove(hands[card.suit].begin(), hands[card.suit].end(), card);
    // assert(it != hands[card.suit].end());
    // hands[card.suit].erase(it, hands[card.suit].end());
  }
  void add(Card card) {
    int idx = 0;
    for (; idx < 4; idx++)
      if ("SHDC"[idx] == card.suit) break;

    hands[idx].push_back(card);
  }
  int size() {
    int ret = 0;
    for (int i = 0; i < 4; i++) ret += (int)hands[i].size();
    return ret;
  }
};

vector<Hand> inputHands() {
  // あとで作る

  //
  //   Hand h1({"AKQJ", "AKQJ", "AKQJ", "A"});
  //   Hand h2({"T987", "T987", "T987", "K"});
  //   Hand h3({"6543", "6543", "6543", "Q"});
  //   Hand h4({"2", "2", "2", "JT987654532"});
  Hand h1({"", "", "AKQJ", "A"});
  Hand h2({"", "", "T987", "K"});
  Hand h3({"", "", "6543", "Q"});
  Hand h4({"2", "2", "2", "32"});
  return {h1, h2, h3, h4};

  // カードが被ってないかチェックする
};

int judgeWinner(vector<Card> cards, int nowSuit, char trump) {
  //
  int ret = 0;
  //
  char nowC = 'N';
  if (nowSuit >= 0) nowC = "SHDC"[nowSuit];
  auto f = [&](Card c1, Card c2) {
    if (c1.suit != c2.suit) {
      if (c1.suit == trump) return true;
      if (c2.suit == trump) return false;
      if (c1.suit == nowC) return true;
      if (c2.suit == nowC) return false;
      // それ以外の時は勝利判定に選ばれない
      assert(false);
    }
    return Card::isStrong(c1, c2);
  };

  for (int i = 1; i < 4; i++) {
    if (f(cards[i], cards[ret])) ret = i;
  }
  return ret;
};

int main() {
  // 入力
  vector<Hand> initialHands = inputHands();
  char trump = 'H';
  //
  int pattern = 0;  // for debug
  int start = 0;    // 現在の手番
  int sz = initialHands[0].size();

  auto dfs = [&](auto rec, int cnt, int player, vector<Hand> &hands,
                 vector<Card> cards, int nowSuit, int win) -> int {
    if (cnt == sz * 4) {
      assert(cards.size() == 0);
      //   for (int i = 0; i < 4; i++) assert(hands[i].size() == 0);
      printf("%d\n", ++pattern);
      return win;
    }
    int ret = 0;
    if (player % 2) ret = 13;  // 奇数プレイヤーは勝ち数の最小化を目指す
    int nextPlayer = (player + 1) % 4;
    vector<vector<Card>> playerHand = hands[player].hands;

    // 出せるスートを全部試す
    vector<int> suits;
    if (nowSuit >= 0 && !playerHand[nowSuit].empty()) {
      // そのスートしか出せない
      suits.push_back(nowSuit);
    } else {
      // 全スーツ出せる
      for (int i = 0; i < 4; i++) suits.push_back(i);
    }
    for (auto suit : suits) {
      for (Card card : playerHand[suit]) {
        // cout << card.suit << card.number << endl;
        vector<Card> nextCards = cards;
        nextCards.push_back(card);
        int nextwin = win;
        int nextSuit = nowSuit;

        // 4人出してたら勝敗判定
        if (nextCards.size() == 4) {
          int winner = judgeWinner(nextCards, nowSuit, trump);
          if (winner % 2 == 0) nextwin++;
          nextPlayer = (player + 4 - 3 + winner) % 4;
          nextCards.clear();
          nextSuit = -1;
        }
        // 1人目だったらスートを決める
        if (nextCards.size() == 1) nextSuit = suit;
        int tmp = hands[player].size();
        hands[player].erase(card);
        assert(tmp - 1 == hands[player].size());
        assert((int)nextCards.size() == (cnt + 1) % 4);
        int res =
            rec(rec, cnt + 1, nextPlayer, hands, nextCards, nextSuit, nextwin);
        ret = ((player % 2) ? min(ret, res) : max(ret, res));
        hands[player].add(card);
      }
    }

    return ret;
  };

  //
  vector<Card> emp;
  int ans = dfs(dfs, 0, start, initialHands, emp, -1, 0);
  cout << ans << endl;

  return 0;
}