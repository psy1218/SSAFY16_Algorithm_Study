#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

long long solution(int n, vector<int> works) {
	long long answer = 0;
	priority_queue<int, vector<int>, less<int>> pq;
	for (int i = 0; i < works.size(); i++) {
		pq.push(works[i]);
	}
	for (int i = 0; i < n; i++) {
		int poped = pq.top();
		pq.pop();
        if (poped == 0){
            pq.push(poped);
            continue;
        }
		pq.push(poped - 1);
	}
	while (!pq.empty()) {
		int poped = pq.top();
		pq.pop();
		answer += poped * poped;
	}
	return answer;
}
