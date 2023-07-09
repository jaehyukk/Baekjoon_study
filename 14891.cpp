#include<iostream>
#include<vector>
#include<string>
#include<memory.h>
using namespace std;

vector<vector<int>> vec(4);
bool check[4] = { false, };		// 회전시켜야 할 톱니바퀴
bool visited[4] = { false, };	// rotation()를 거친 톱니바퀴 확인

void checking(int num, int seq) {		// 회전시켜야 할 톱니바퀴 모두 확인
	int temp = num;
	while (1) {					// 첫 톱니바퀴 기준 오른쪽 방향의 톱니바퀴들 확인
		if (temp >= 3) break;
		if (vec[temp][2] == vec[temp + 1][6]) {
			check[temp + 1] = true;
			break;
		}
		temp++;
	}
	temp = num;
	while (1) {					// 첫 톱니바퀴 기준 왼쪽 방향의 톱니바퀴들 확인
		if (temp <= 0) break;
		if (vec[temp][6] == vec[temp - 1][2]) {
			check[temp - 1] = true;
			break;
		}
		temp--;
	}
	return;
}

void rotation(int before, int num, int seq, int dir) {
	if (num > 4 || num < 1 || check[num - 1] == true || visited[num - 1] == true) return;

	visited[num - 1] = true;
	if (seq == 0) {				// 첫 회전
		if (dir == -1) {
			int temp = vec[num - 1][0];
			vec[num - 1].erase(vec[num - 1].begin());
			vec[num - 1].push_back(temp);
		}
		else {
			int temp = vec[num - 1][7];
			vec[num - 1].pop_back();
			vec[num - 1].insert(vec[num - 1].begin(), temp);
		}
	}
	else {						// 두 번째 톱니바퀴 회전부터~
		if (before < num) {		// 기준 톱니바퀴보다 오른쪽에 있는 경우
			if (dir == -1) {		// 기준 톱니바퀴가 반시계 방향이었을 경우
				int temp = vec[num - 1][7];
				vec[num - 1].pop_back();
				vec[num - 1].insert(vec[num - 1].begin(), temp);
				dir = 1;
			}
			else {
				int temp = vec[num - 1][0];
				vec[num - 1].erase(vec[num - 1].begin());
				vec[num - 1].push_back(temp);
				dir = -1;
			}
		}
		else {					// 기준 톱니바퀴보다 왼쪽에 있는 경우			
			if (dir == -1) {		// 기준 톱니바퀴가 반시계 방향이었을 경우
				int temp = vec[num - 1][7];
				vec[num - 1].pop_back();
				vec[num - 1].insert(vec[num - 1].begin(), temp);
				dir = 1;
			}
			else {
				int temp = vec[num - 1][0];
				vec[num - 1].erase(vec[num - 1].begin());
				vec[num - 1].push_back(temp);
				dir = -1;
			}
		}
	}
	rotation(num, num + 1, seq + 1, dir);
	rotation(num, num - 1, seq + 1, dir);
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);

	string str;
	int k, num, dir;
	int result = 0;

	for (int i = 0; i < 4; i++) {
		cin >> str;
		for (int j = 0; j < 8; j++) {
			num = str[j] - '0';
			vec[i].push_back(num);
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> num >> dir;
		checking(num - 1, 0);
		rotation(0, num, 0, dir);
		memset(check, false, sizeof(check));
		memset(visited, false, sizeof(visited));
	}
	if (vec[0][0] == 1) result += 1;
	if (vec[1][0] == 1) result += 2;
	if (vec[2][0] == 1) result += 4;
	if (vec[3][0] == 1) result += 8;
	cout << result << "\n";

	return 0;
}
