#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int>x;

bool possible(int R) {

	int i = 0;
	int bombcnt = 0;

	while (1) {
		if (i >= n) break;

		bombcnt++;

		if (k < bombcnt) return false; // 폭탄 가능 개수 k보다 더 많이 터트리면 불가능 한 거임. 

		int end = x[i] + R * 2;


		while (i < n && x[i] <= end) { // x[i] <= end : end가 폭탄 터질 수 있는 범위인데, 그게 우리가 원하는 N개의 점들이 가능한지, x와 index로 판별. 
			// 애초에 end로 범위 지정해서 가능한 곳까지 index 옮기기. 
			i++;
		}
	}

	return true;
	
}

int main() {
	cin >> n >> k;

	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		x.push_back(num);
	}


	sort(x.begin(), x.end());

	int right = x.size();
	int left = 0;


	while (left < right) {
		
		int mid = (right + left) / 2;
		
		if (possible(mid)) right = mid;
		else left = mid + 1;
	}
	
	cout << left;
	// mid = 현재 검사해보는 후보값
	// left, right = 정답이 존재할 수 있는 범위
	// left == right 일 경우 정답임. 

	return 0;
}

/*

R의 값을 구하기 위해서는 R의 값을 임의로 정하고, R일 때, 요구되는 K번이 가능한지 판별하기. 
요구되는 K번이 가능하면서 최소 R을 구하기 = R의 최소값은 이분탐색으로 찾기 

가장 왼쪽부터 left+R 의 중심으로  left ~ left+ 2R 범위 지울 수 있으니까, -> 이게 하나의 폭탄.
이걸 반복하면 K개의 폭탄을 구할 수 있다. 

*/
