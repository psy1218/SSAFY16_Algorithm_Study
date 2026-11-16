#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <array>
using namespace std;

// 2랑 6이 중요
deque<int> table[4];

void turn_table(int table_idx, int d){
    if (d == 1){
        int temp = table[table_idx].back();
        table[table_idx].pop_back();
        table[table_idx].push_front(temp);
    }
    else if (d == -1){
        int temp = table[table_idx].front();
        table[table_idx].pop_front();
        table[table_idx].push_back(temp);
    }
}

void command(int center, int d){
    int turn_dir[4] = {0, 0, 0, 0};
    turn_dir[center] = d;

    int center_dir = d;
    for (int table_idx = center + 1; table_idx < 4; table_idx++){
        if (table[table_idx][6] == table[table_idx-1][2]){
            break;    
        }
        turn_dir[table_idx] = center_dir * -1;
        center_dir *= -1;
    }

    center_dir = d;
    for (int table_idx = center - 1; table_idx >= 0; table_idx--){
        if (table[table_idx][2] == table[table_idx+1][6]){
            break;
        }
        turn_dir[table_idx] = center_dir * -1;
        center_dir *= -1;
    }

    // turn
    for (int idx = 0; idx < 4; idx++){
        if (turn_dir[idx] == 0){
            continue;
        }
        turn_table(idx, turn_dir[idx]);
    }

    return;
}

int main() {
    // Please write your code here.

    for (int i = 0; i < 4; i++){
        string str;
        cin >> str;
        
        for (int j = 0; j < 8; j++){
            table[i].push_back(str[j] - '0');  
        }
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++){
        int n, d;
        cin >> n >> d;

        command(n-1, d);

    }
    
    int answer = 0;
    int power = 1;
    for (int i = 0; i < 4; i++){
        answer += power * table[i][0];
        power *= 2;
    }

    cout << answer;

    return 0;
}
