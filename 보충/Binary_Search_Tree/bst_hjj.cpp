#include <iostream>
#include <queue>

using namespace std;

/**
 * 
 * Leet Code - 235. Lowest Common Ancestor of a Binary Search Tree
 * https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 * Leet Code - 450. Delete Node in a BST
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * 
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;

	// C++ 의 멤버 초기화 리스트 문법을 사용한 생성자
	// 일반 대입 방식으로 구현하는 경우, 작업 효율성이 떨어짐 (변수를 쓰레기값으로 먼저 생성 -> 값 초기화)
	// 멤버 초기화 리스트는 변수를 처음부터 원하는 값으로 할당 (효율적)
	// 
	// TreeNode() {
	//     val = 0;
	//     left = nullptr;
	//     right = nullptr;
	// }
	// 
	// 생성자도 일종의 함수라고 이해하면 편하다. (그래서 뒤에 {} 가 있음)
	// {}에서는 구조체를 생성하고 추가로 진행할 작업에 대해서 정의한다
	// 
	TreeNode() : val(0), left(nullptr), right(nullptr) {};
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {};
};

class binarySearchTree {
private:
	TreeNode* root;
public:
	binarySearchTree() {
		root = nullptr;
	}

	// elem을 val로 하는 노드 삽입
	void insertNode(int elem);

	// elem을 val로 하는 노드 탐색
	TreeNode* findNode(int elem);

	// elem을 val로 하는 노드 삭제
	void deleteNode(int elem);

	// 지정하는 노드를 루트를 하는 하위 트리 모두 출력
	void printTree(TreeNode* rootNode);

	// 최상단 노드 리턴
	TreeNode* rootNode();
};

/// <summary>
/// BST에 elem을 val로 하는 노드를 삽입
/// </summary>
/// <param name="elem(삽입할 노드의 값)"></param>
void binarySearchTree::insertNode(int elem) {
	TreeNode* newNode = new TreeNode(elem);

	if (root == nullptr) {
		root = newNode;
		return;
	}

	// 현재 노드 초기화
	TreeNode* currNode = root;

	// 반복문은 끝나지 않게 되어있으나, 안전한 종료를 위해 조건 명시
	while (currNode != nullptr) {
		// 1. 추가하려는 노드의 값이 현재 노드의 값보다 작은 경우
		if (elem < currNode->val) {
			// 현재 노드의 왼쪽 노드가 존재하지 않을 경우
			// 새 노드를 현재 노드의 왼쪽에 추가하면서 종료
			if (currNode->left == nullptr) {
				currNode->left = newNode;
				return;
			}

			// 현재 노드의 왼쪽 노드가 존재할 경우, 그 노드로 이동
			currNode = currNode->left;
		}
		// 2. 추가하려는 노드의 값이 현재 노드의 값보다 큰 경우
		else if (elem > currNode->val) {
			// 현재 노드의 오른쪽 노드가 존재하지 않을 경우
			// 새 노드를 현재 노드의 오른쪽에 추가하면서 종료
			if (currNode->right == nullptr) {
				currNode->right = newNode;
				return;
			}

			// 현재 노드의 오른쪽 노드가 존재할 경우, 그 노드로 이동
			currNode = currNode->right;
		}
		// 3. 추가하려는 노드의 값이 현재 노드의 값과 같은 경우
		else {
			cout << "You cannot add same value in this tree." << endl;
			// 메모리 해제
			delete newNode;
			return;
		}
	}
}

/// <summary>
/// BST에서 elem을 val로 하는 노드를 탐색
/// 만약 원하는 노드를 찾지 못할 경우 nullptr를 리턴
/// </summary>
/// <param name="elem(탐색할 노드의 값)"></param>
TreeNode* binarySearchTree::findNode(int elem) {
	// 현재 노드 초기화
	TreeNode* currNode = root;

	// 비어있는 트리인 경우
	if (root == nullptr) {
		cout << "This tree is empty." << endl;
		return nullptr;
	}

	while (currNode != nullptr) {
		// 1. 찾으려는 노드의 값이 현재 노드의 값보다 작은 경우
		if (elem < currNode->val) {
			currNode = currNode->left;
		}
		// 2. 찾으려는 노드의 값이 현재 노드의 값보다 큰 경우
		else if (elem > currNode->val) {
			currNode = currNode->right;
		}
		// 3. 원하는 노드를 탐색한 경우, 해당 노드 리턴
		else {
			return currNode;
		}
	}
	// while 문을 탈출한 경우:
	// 
	// BST 규칙에 따라 elem이 존재한다면
	// <1번 케이스>
	// 반드시 현재 노드의 왼쪽 서브트리에 있어야 하는데, 왼쪽 노드가 없으므로 존재할 수 없다.
	// <2번 케이스>
	// 반드시 현재 노드의 오른쪽 서브트리에 있어야 하는데, 오른쪽 노드가 없으므로 존재할 수 없다.
	//
	cout << "Cannot find node having value (" << elem << ")." << endl;
	return nullptr;
}

/// <summary>
/// BST에서 elem을 val로 하는 노드 삭제
/// </summary>
/// <param name="elem(삭제할 노드의 값)"></param>
void binarySearchTree::deleteNode(int elem) {
	// 현재 노드 초기화
	TreeNode* currNode = root;
	// 부모 노드 정의
	TreeNode* currParentNode = nullptr;

	// 비어있는 트리인 경우
	if (root == nullptr) {
		cout << "This tree is empty." << endl;
		return;
	}

	while (currNode != nullptr) {
		// 현재 노드가 삭제 대상인 경우
		if (elem == currNode->val) {
			// 1. 어떠한 자식 노드도 없는 경우 바로 삭제
			if (currNode->left == nullptr && currNode->right == nullptr) {
				// 삭제하려는 노드가 root인 경우
				if (currParentNode == nullptr) {
					root = nullptr;
				}
				// 부모 노드가 존재하는 경우 연결 해제
				if (currParentNode != nullptr) {
					if (currParentNode->left == currNode) {
						currParentNode->left = nullptr;
					}
					else {
						currParentNode->right = nullptr;
					}
				}
				// 대상 노드 삭제
				delete currNode;
				return;
			}

			// 2. 현재 노드가 한 쪽 방향의 노드만 있는 경우
			else if (currNode->right == nullptr || currNode->left == nullptr) {
				// 자식 노드
				TreeNode* childNode = (currNode->right != nullptr) ? currNode->right : currNode->left;

				// 삭제하려는 노드가 root인 경우
				if (currParentNode == nullptr) {
					root = childNode;
				}
				// 부모 노드가 존재하는 경우, 연결 재정의
				if (currParentNode != nullptr) {
					if (currParentNode->left == currNode) {
						currParentNode->left = childNode;
					}
					else {
						currParentNode->right = childNode;
					}
				}
				// 대상 노드 삭제
				delete currNode;
				return;
			}

			// 3. 현재 노드가 모든 방향의 노드가 있는 경우
			else {
				// 방법이 2가지 있음
				// A. 왼쪽 서브트리의 최댓값으로 대체
				// B. 오른쪽 서브트리의 최솟값으로 대체
				// 현재 코드에선 A 방식은 주석 처리

				/*
				// [ A 방식 ]
				// a. 서브트리 탐색(해당 서브트리 안에서 최댓값 탐색)
				// 왼쪽 서브트리 중 최댓값 노드
				// 왼쪽 서브트리의 최상단 노드부터 시작
				TreeNode* leftSubTreeMaxNode = currNode->left;
				// leftSubTreeMaxNode의 부모 노드를 저장하기 위함
				TreeNode* leftSubTreeMaxParentNode = currNode;

				// 서브트리 탐색 (탐색이 끝나면 반복문 종료)
				// 종료할 때 자연스럽게 왼쪽 서브트리 중 최댓값 노드가 됨
				while (leftSubTreeMaxNode->right != nullptr) {
					leftSubTreeMaxParentNode = leftSubTreeMaxNode;
					leftSubTreeMaxNode = leftSubTreeMaxNode->right;
				}

				// b. 삭제 과정 진행 (노드 값 바꾸기 -> 연결관계 재정의 -> leftSubTreeMaxNode 완전 삭제)
				// b-1. 삭제할 노드 값을 leftSubTreeMaxNode의 값으로 바꾸기
				currNode->val = leftSubTreeMaxNode->val;
				// b-2. 연결관계 재정의
				// b-2-1. leftSubTreeMaxParentNode 가 currNode 인 경우 (삭제할 노드가 leftSubTreeMaxNode의 부모 노드인 경우)
				if (leftSubTreeMaxParentNode == currNode) {
					currNode->left = leftSubTreeMaxNode->left;
				}
				// b-2-2. 그 외의 경우
				// leftSubTreeMaxNode의 왼쪽 노드 유무 상관 없이 연결(노드 없는 경우 nullptr 임)
				else {
					leftSubTreeMaxParentNode->right = leftSubTreeMaxNode->left;
				}
				// b-3. leftSubTreeMaxNode 완전 삭제
				delete leftSubTreeMaxNode;
				return;
				*/

				// [ B 방식 ]
				// a. 서브트리 탐색(해당 서브트리 안에서 최솟값 탐색)
				// 오른쪽 서브트리 중 최솟값 노드
				// 오른쪽 서브트리의 최상단 노드부터 시작
				TreeNode* rightSubTreeMinNode = currNode->right;
				// rightSubTreeMinNode의 부모 노드를 저장하기 위함
				TreeNode* rightSubTreeMinParentNode = currNode;

				// 서브트리 탐색 (탐색이 끝나면 반복문 종료)
				// 종료할 때 자연스럽게 오른쪽 서브트리 중 최솟값 노드가 됨
				while (rightSubTreeMinNode->left != nullptr) {
					rightSubTreeMinParentNode = rightSubTreeMinNode;
					rightSubTreeMinNode = rightSubTreeMinNode->left;
				}

				// b. 삭제 과정 진행 (노드 값 바꾸기 -> 연결관계 재정의 -> rightSubTreeMinNode 완전 삭제)
				// b-1. 삭제할 노드 값을 rightSubTreeMinNode의 값으로 바꾸기
				currNode->val = rightSubTreeMinNode->val;
				// b-2. 연결관계 재정의
				// b-2-1. rightSubTreeMinParentNode 가 currNode 인 경우 (삭제할 노드가 rightSubTreeMinNode의 부모 노드인 경우)
				if (rightSubTreeMinParentNode == currNode) {
					currNode->right = rightSubTreeMinNode->right;
				}
				// b-2-2. 그 외의 경우
				// rightSubTreeMinNode의 오른쪽 노드 유무 상관 없이 연결(노드 없는 경우 nullptr 임)
				else {
					rightSubTreeMinParentNode->left = rightSubTreeMinNode->right;
				}
				// b-3. leftSubTreeMaxNode 완전 삭제
				delete rightSubTreeMinNode;
				return;
			}
		}
		// 삭제 대상 노드의 값이 현재 노드의 값보다 작은 경우
		else if (elem < currNode->val) {
			currParentNode = currNode;
			currNode = currNode->left;
		}
		// 삭제 대상 노드의 값이 현재 노드의 값보다 큰 경우
		else {
			currParentNode = currNode;
			currNode = currNode->right;
		}
	}
	// while 문을 탈출한 경우:
	// 
	// BST 규칙에 따라 elem이 존재한다면
	// <1번 케이스>
	// 반드시 현재 노드의 왼쪽 서브트리에 있어야 하는데, 왼쪽 노드가 없으므로 존재할 수 없다.
	// <2번 케이스>
	// 반드시 현재 노드의 오른쪽 서브트리에 있어야 하는데, 오른쪽 노드가 없으므로 존재할 수 없다.
	//
	cout << "Cannot find node having value (" << elem << ")." << endl;
	return;
}

/// <summary>
/// BST에서 지정하는 노드를 루트를 하는 하위 트리 모두 출력
/// </summary>
/// <param name="rootNode(탐색할 서브트리의 최상위 노드)"></param>
void binarySearchTree::printTree(TreeNode* rootNode) {
	// 비어있는 트리
	if (rootNode == nullptr) {
		cout << "[]" << endl;
		return;
	}

	// BFS
	queue<TreeNode*> route;
	route.push(rootNode);

	// 출력 시작
	cout << "[";

	while (!route.empty()) {
		TreeNode* currNode = route.front();
		route.pop();

		// 현재 노드가 비어있는(=존재하지 않는) 노드인 경우 null로 표시
		if (currNode == nullptr) cout << "null";

		else {
			// 현재 노드의 값 출력
			cout << currNode->val;

			// 왼쪽 -> 오른쪽 순
			route.push(currNode->left);
			route.push(currNode->right);
		}

		// 순회할 노드가 비어있지 않는 한, 출력이 자연스럽도록 콤마 구분
		if (!route.empty()) cout << ", ";
	}

	// 출력 종료
	cout << "]" << endl;
}

/// <summary>
/// BST의 최상단 노드 출력
/// </summary>
TreeNode* binarySearchTree::rootNode() {
	return root;
}


// 임시로 아무 코드나 작성함
int main() {
	binarySearchTree* bst = new binarySearchTree();
	bst->insertNode(1);
	bst->insertNode(6);
	bst->insertNode(2);
	bst->insertNode(5);
	bst->insertNode(3);
	bst->insertNode(4);
	bst->printTree(bst->rootNode());
	return 0;
}