#include <iostream>
#include <vector>
#include <algorithm>


/*
 * knapsack problem:
 *
 *
 *
 *
 */
#define matrix vector<vector<int>>

using namespace std;



matrix createCoinMatrix(const int& amountOfCoins, const int& bill){
    matrix m;
    m.resize(amountOfCoins+1);



    for(int j = 0; j < amountOfCoins + 1; j++){
        vector<int> row;
        row.resize(bill+1);
        for(int i = 0; i < bill+1; i++){
            row[i] = 0;
        }
        m[j] = row;
    }
    for(int i = 0; i < m.size();i++){
        m[0][i] = i;
    }



    return m;
}


matrix changeMaking(const vector<int>& coins, const int& bill){
    matrix m = createCoinMatrix(coins.size(), bill);
    for(unsigned long row = 1; row < m.size();row++){
        int currentCoin = coins[row - 1];
        for(unsigned long column = 1; column < m[row].size(); column++){
            unsigned long currentBill = column;
            int& currentCell = m[row][column];

            if(currentCoin == currentBill){
                currentCell = 1;
            }else if(currentCoin > currentBill){
                currentCell = m[row-1][column];
            }else{
                currentCell = min(m[row-1][column], 1 + m[row][column - currentCoin]); // TODO
            }
        }
    }
    return m;
}


ostream& operator<<(ostream& os,const matrix& m){
    for(unsigned long i = 0; i < m.size() ;i++){
        for(int n: m[i]){
            os << n << " ";
        }
        os << endl;
    }
    return os;
}


vector<int> recreateCoinsBeingUsed(const vector<int>& coins, matrix& m){
    vector<int> result;
    result.resize(coins.size());


    unsigned long row = m.size() -1;
    unsigned long column = m[row].size() - 1;

    while(m[row][column] > 0){
        int& currentCell = m[row][column];
        int currentCoin = coins[row - 1];
        if(currentCell == m[row-1][column]){
            row--;
        }else{
            result[row - 1]++;
            column -= currentCoin;
        }
    }
    return result;
}




int main() {
    int testCases;
    cin >> testCases;
    for(int testCase= 0; testCase < testCases;testCase++) {
        int n,c;
        cin >> n;
        cin >> c;
        int& bill = c;
        vector<int> coins;
        coins.resize(n);
        for(int coin = 0; coin < n; coin++){
            cin >> coins[coin];
        }
        matrix m = changeMaking(coins, bill);
        vector<int> result = recreateCoinsBeingUsed(coins, m);
        cout << "Case #"<< testCase + 1 << ": ";
        for (int n: result) {
            cout << n << " ";
        }
    }
    return 0;
}