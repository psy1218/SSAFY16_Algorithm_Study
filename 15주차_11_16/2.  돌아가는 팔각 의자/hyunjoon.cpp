
#include <iostream>
using namespace std;

int table[4][8];
bool same[3];

void spin(int dir, int t_num) {
    if (dir == 1) {
        int end = table[t_num][7];

        for (int i = 7; i > 0; i--) {
            table[t_num][i] = table[t_num][i - 1];
        }

        table[t_num][0] = end;
    }
    else if (dir == -1) {
        int start = table[t_num][0];

        for (int i = 0; i < 7; i++) {
            table[t_num][i] = table[t_num][i + 1];
        }

        table[t_num][7] = start;
    }
}

// 
void check_same(){
    for(int i = 0; i<3; i++){
        if(table[i][2] == table[i+1][6]){
            same[i] = true;
        }
        else{
            same[i] = false;
        }
    }
}

void solve(int num, int dir){
    int org_dir = dir;
    int R_start = num + 1;
    int L_start = num - 1;


    check_same();
    spin(dir, num);
    for(int i = R_start; i<4; i++){
        dir = dir*-1;
        if(same[i-1]){
            break;
        }
        spin(dir, i);
    }
    dir = org_dir;
    for(int i = L_start; i>=0; i--){
        dir = dir*-1;
        if(same[i]){
            break;
        }
        spin(dir, i);
    }
}

int value(){
    int ans = 0;
    for(int i = 0; i<4; i++){
        if(table[i][0]){
            ans += 0x1<<i;
        }
    }
    return ans;
}

int main() {
    // Please write your code here.

    int num = 0, dir = 0;
    int k = 0;
    for (int i = 0; i < 4; i++) {
        string s;
        cin >> s;

        for (int j = 0; j < 8; j++) {
            table[i][j] = s[j] - '0';
        }
    }
    cin >> k;

    for(int i = 0; i<k; i++){
        cin >> num >> dir;
        solve(num-1, dir);
    }

    cout << value();
    return 0;
}
