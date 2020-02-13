#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef vector<int> Row;
typedef vector<Row> Matrix;

Matrix gcdptable(vector<int>& denoms, int lim) {
    Matrix t(lim, Row(lim, 0));
    for (int q = 0; q < lim; ++q){
        t[0][q] = q;
    }
    for (int j =1; j < denoms.size(); ++j){
        for (int i = 0; i < lim; ++i){
            if (denoms[i] <= i) t[j][i] = min(t[j-1][i], 1 + t[j][i-denoms[j]]);
            else t[j][i] = t[j-1][i];
        }
    }
    return t;
}

map<int, int> trace(vector<vector<int> >& gctab, vector<int>& denoms, int q){
    map<int, int> r;
    for (int dn = 0; dn < denoms.size(); ++dn){
        r[denoms[dn]] = 0;
    }
    int d = (denoms.size() - 1);
    while(q){
        if (d==0){
            r[denoms[d]] += q;
            break;
        }
        else if (gctab[d][q] == gctab[d-1][q]) --d;
        else{
            r[denoms[d]] += 1;
            q -= denoms[d];
        }
    }
    return r;
}

bool check_denoms(vector<int>& denoms, int a){
    for(int j=0; j < denoms.size(); ++j){
        if(denoms[j] == a) return true;
    }
    return false;
}

int main(){
    int dq;
    int lim;
    int q;
    cout << "Type in the number of coin denominations: ";
    cin >> dq;
    Row denoms(dq);

    for(int i=0; i < dq; ++i){
        cin >> denoms[i];
    }
    cout << "Type in the uppes limit: " << endl;
    cin >> lim;

    if (check_denoms(denoms, 1) == false){
        cout << "Adding a denomination of 1 so that 1 is rechable.";
        denoms.push_back(1);
    }
    sort(denoms.begin(), denoms.end());
    Matrix gctab = gcdptable(denoms, lim + 1); //must reach from 0 to limit

    cout << "Type in a quantity to reach, 0 to finish: ";
    cin >> q;

    while(q){ //mentres la q sigui positiva
        if (q > lim) cout << "is too large a quantity right now, sorry." << endl;
        else{
            map<int, int> r = trace(gctab, denoms, q);
            for(int i = 0; i < r.size(); ++i){
                cout << i << ":" <<r[i] << endl;
            }
        }
        cout << "Type in a quantity to reach, 0 to finish:" << endl;
        cin >> q;
    }

}
