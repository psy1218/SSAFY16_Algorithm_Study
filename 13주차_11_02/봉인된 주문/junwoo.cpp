#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long spell_idx(string spell){
    long long power = 1;
    int n = spell.length();
    long long id = 0;
    
    for (int i = n-1; i >= 0; i--){
        id += ((int(spell[i]) - int('a') + 1) * power);
        power *= (int('z') - int('a') + 1);
    }
    
    return id;
}

string decode_id(long long id) {
    string spell = "";

    while (id > 0) {
        id--;

        spell += char('a' + id % 26);
        id /= 26;
    }

    reverse(spell.begin(), spell.end());

    return spell;
}

string solution(long long n, vector<string> bans) {
    string answer = "";
    
    vector<long long> bans_id (bans.size());
    for (int i = 0; i < bans.size(); i++){
        bans_id[i] = spell_idx(bans[i]);
    }
    
    sort(bans_id.begin(), bans_id.end());

    // 앞에 몇 개 사라졌는지 확인
    for (int i = 0; i < bans_id.size(); i++){
        if (bans_id[i] <= n){
            n++;
        }
    }
    
    
    
    return decode_id(n);
}
