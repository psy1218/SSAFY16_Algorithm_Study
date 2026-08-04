#include <iostream>
#include <vector>
#include <string>
#include <vector>
using namespace std; 

int main()
{
	for (int tc = 1; tc <= 10; tc++) {
		int n;
		cin >> n;
		string str;
		cin >> str;
		vector<char> arr;
		for (int i = 0; i < str.length(); i++) {
			char cur = str[i];
			while (arr.size()>=2) {
				char top = arr.back();
				arr.pop_back();
				char nxt_top = arr.back();
				arr.pop_back();
				if (top == ')' && nxt_top == '(') {
					continue;
				}
				else if (top == '}' && nxt_top == '{') {
					continue;
				}
				else if (top == ']' && nxt_top == '[') {
					continue;
				}
				else if (top == '>' && nxt_top == '<') {
					continue;
				}
				else {
					arr.push_back(nxt_top);
					arr.push_back(top);
					break; 
				}
			}
			arr.push_back(cur);
		}
		while (!arr.empty()) {
			char top = arr.back();
			arr.pop_back();
			char nxt_top = arr.back();
			arr.pop_back();
			if (top == ')' && nxt_top == '(') {
				continue;
			}
			else if (top == '}' && nxt_top == '{') {
				continue;
			}
			else if (top == ']' && nxt_top == '[') {
				continue;
			}
			else {
				arr.push_back(nxt_top);
				arr.push_back(top);
				break;
			}
		}
		if (arr.empty()) {
			cout << "#" << tc << " " << 1 << endl;
		}
		else {
			cout << "#" << tc << " " << 0 << endl;
		}
	}
	return 0;
}
