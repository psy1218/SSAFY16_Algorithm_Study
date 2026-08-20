#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool desc(int a, int b) {
	if (a > b) {
		return 1;
	}
	else return 0;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N;
		int ans = 0;
		cin >> N;
		vector<int> cloth;

		for (int i = 0; i < N; i++) {
			int cl;
			cin >> cl;
			cloth.push_back(cl);
		}

		sort(cloth.begin(), cloth.end(), desc);
		
		for (int i = 0; i <= N / 3; i++) {
			for (int j = i*3; j < i*3+2; j++) {
				ans += cloth[j];
			}
		}

		cout <<"#"<<test_case<<' '<< ans << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
