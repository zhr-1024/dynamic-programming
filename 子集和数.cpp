#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NUM = 100;
const int MAX_WEIGHT = 1000;

class SubSetProblem {
public:
  void init(int n, int W) {
    this->n = n;
    this->W = W;
    memset(optional, 0, sizeof(optional));
    for (int i = 1; i <= n; ++i) {
      cin >> weight[i];
    }
  }
  void process() {
    for (int i = 1; i <= n; ++i) {
      for (int w = 0; w <= W; ++w) {
        if (w < weight[i]) {
          optional[i][w] = optional[i-1][w];
        } else if (optional[i-1][w] < weight[i] + optional[i-1][w-weight[i]]) {
          optional[i][w] = weight[i] + optional[i-1][w-weight[i]];
        } else {
          optional[i][w] = optional[i-1][w];
        }
      }
    }
  }
  void result() {
    cout << "选择:";
    for (int i = n, w = W; i != 0; --i) {
      if (optional[i][w] == optional[i-1][w]) {
        cout<< ' ' <<"0";
      } else {
        cout << ' ' <<"1";
        w -= weight[i];
      }
    }
    cout << "\n总共: " << optional[n][W] << endl;
  }
private:
  int n, W;
  int weight[MAX_NUM + 1];
  int optional[MAX_NUM + 1][MAX_WEIGHT + 1];
};

int main() {
  SubSetProblem ssp;
  int n, W;
  cin >> n >> W;
  if (n > MAX_NUM || W > MAX_WEIGHT) {
    cout << "error" << endl;
    return -1;
  }
  ssp.init(n, W);
  ssp.process();
  ssp.result();
  return 0;
}
