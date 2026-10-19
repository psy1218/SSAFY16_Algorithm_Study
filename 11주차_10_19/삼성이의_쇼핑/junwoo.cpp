#include<iostream>

using namespace std;

int N;
int M;
int P[25];
int S[25];

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin >> T;
	
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M;

		for (int i = 0; i < M; i++) {
			cin >> P[i] >> S[i];
		}

		int maxS = -1;
		int bestMask = 0;

		for (int mask = 0; mask < (1 << M); mask++) {
			int totalP = 0;
			int totalS = 0;

			for (int i = 0; i < M; i++) {
				if (mask & (1 << i)) {
					totalP += P[i];
					totalS += S[i];
				}
			}

			if (totalP < N && totalS > maxS) {
				maxS = totalS;
				bestMask = mask;
			}
		}

		cout << "#" << test_case << " ";

		for (int i = 0; i < M; i++) {
			if (bestMask & (1 << i)) {
				cout << i << " ";
			}
		}

		cout << maxS << "\n";
		


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
