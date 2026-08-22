#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(int a, int b) {
	return a > b;
}

int main() {

//	freopen("input.txt", "r", stdin);

	int T, N, num;
	cin >> T;
	for (int t = 1;t <= T;t++) {
		cin >> N;

		vector<int>arr;
		int res = 0;
		for (int n = 0;n < N;n++) {
			cin >> num;
			arr.push_back(num);
			res += num;
		}

		sort(arr.begin(), arr.end(), cmp);
		
		// 2,5,8
		int minus = 0;
		for (int i = 0;i < N;i++) {
			if (i >= 2 && (i - 2) % 3 == 0) minus += arr[i];
		}

		cout << "#" << t << " " << res - minus << "\n";
	}

	return 0;
}



/*
* 
* 싼 값 기준으로 정렬해서 묶음의 앞을 빼려고 함. -> 틀림
* 
* 4
* 1 2 3 4  경우 1/234로 2가 세일되는게 좋은데, 나의 경우는 123/4 이렇게 묶어서 안 됨.
* 비싼 거 묶어야함.
* 
using namespace std;

int main() {

	freopen("input.txt", "r", stdin);

	int T, N, num;
	cin >> T;
	for (int t = 1;t <= T;t++) {
		
		cin >> N;

		vector<int>arr;
		int res = 0;
		for (int n = 0;n < N;n++) {
			cin >> num;
			arr.push_back(num);
			res += num;
		}

		sort(arr.begin(), arr.end());

		int temp = 0, minus = 0;
		for (int i = 0;i < N;i=i+3) {
			if (N % 3 != 0)	 temp = arr[i];
			minus += arr[i];
		}

		cout << "#" << t << " " << res - minus + temp << "\n";
	}
	
	return 0;
}
*/
