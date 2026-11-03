#include <string>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// lower dictionary is true
bool cmp(string a, string b){
    if(a.length() != b.length()){
        return a.length() < b.length();
    }
    else return a < b;
}

string parsing(long long n) {
    string str;

    while (n > 0) {
        --n;
        str += char('a' + n % 26);
        n /= 26;
    }

    reverse(str.begin(), str.end());
    return str;
}

string solution(long long n, vector<string> bans) {
    string answer = "";
    
    /*for(int i = 0; i<bans.size(); i++){
        cout << bans[i] << '\n';
    }*/
    string str = parsing(n);
    cout << str << '\n';
    sort(bans.begin(), bans.end(), cmp);
    for(long long i = 0; i<bans.size(); i++){
        if(bans[i] == parsing(n)) {
            n++;
            continue;
        }
        if(cmp(bans[i], parsing(n))){
            n++;
        }
        else break;
    }
    
    str = parsing(n);
    cout << str;
    answer = str;
    return answer;
}
