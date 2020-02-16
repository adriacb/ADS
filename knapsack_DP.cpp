#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Row;
typedef vector<Row> Table;


int max(int a,int b){
  if (a > b) return a;
  else return b;
}

void print_table(const Table& T){
  for (int i=0; i < T.size(); ++i){
    for (int j=0; j < T[0].size(); ++j) cout << T[i][j] << " ";
    cout << endl;
    }
}

vector<int> read_vector(int n, string s){
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cout << s <<"[" << i+1 << "]: ";
    cin >> v[i];
  }
  return v;
}

void list_items(const Table& T,int n, int w,const vector<int>& wt, const vector<int>& v){
    int res = T[n][w];
    for (int i = n; i > 0 && res > 0; i--) {
        if (res == T[i-1][w]) continue;
        else {
            cout << "Item in the knapsack = ";
            cout << wt[i-1] << " ";
            res = res - v[i-1];
            w = w - wt[i-1];
        }
        cout << endl;
    }
}

int DPknapsack(const vector<int>& v,const vector<int>& wt, int n, int W){
  Table T(n+1,Row(W+1,0)); //The table is initialize with 0
  for (int i=0; i <= n; ++i) {
      for (int w=0; w <= W; ++w) {
          if (i==0 or w == 0) T[i][w] = 0;
          else if ((wt[i-1] <= w)) {
              T[i][w] = max(T[i-1][w], v[i-1] + T[i-1][w-wt[i-1]]);
          }
          else T[i][w] = T[i-1][w];
        }
    }
    print_table(T);
    list_items(T,n,W,wt,v);
    return T[n][W];
}

int main(){
    int W, n;
    cout << "Type in the knapsack capability (weight): ";
    cin >> W;
    cout << "Type in the number of items: ";
    cin >> n;
    vector<int> v = read_vector(n,"values");         //values of the items
    vector<int> w = read_vector(n,"weights");        //weights of the items
    int k = DPknapsack(v,w,n,W);
    cout << endl;
    cout << "knapsack algorithm = " << k << endl;
}
