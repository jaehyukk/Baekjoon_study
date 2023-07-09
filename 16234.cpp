#include<iostream>
#include<vector>
#include<algorithm>
#include<memory.h>
using namespace std;

int n, l, r, cnt = 0, result = 0;
bool change = false;
int graph[51][51];
bool visited[51][51] = { false, };
vector<pair<int, int>> vec;
int dx[4] = { 0,0,-1, 1 };
int dy[4] = { -1,1,0,0 };

void changing(int sum) {			// 공유된 나라의 인구 수 변경
	int num = sum / vec.size();
	for (int i = 0; i < vec.size(); i++) {
		int y = vec[i].first;
		int x = vec[i].second;
		graph[y][x] = num;
	}

	return;
}

int dfs(int y, int x, int sum, int cnt) {
	if (visited[y][x] == true) {
		sum -= graph[y][x];
		return sum;
	}

	vec.push_back({ y, x });
	visited[y][x] = true;
	for (int i = 0; i < 4; i++) {		// 나라 기준으로 상.하.좌.우 탐색
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;		// 그래프를 벗어날 경우
		else {														// 인구 차이가 범위 안에 들어올 경우
			if (abs(graph[y][x] - graph[ny][nx]) <= r && abs(graph[y][x] - graph[ny][nx]) >= l) {
				sum += graph[ny][nx];
				sum = dfs(ny, nx, sum, cnt + 1);
			}
		}
	}
	return sum;
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> l >> r;
	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;
			graph[i][j] = num;
		}
	}

	bool plus_result = false;
	while (1) {
		for (int i = n - 1; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j] == true) continue;
				int sum = graph[i][j];
				int temp = dfs(i, j, sum, 1);

				if (vec.size() > 1) {			// 국경선 공유하는 나라가 있는 경우
					changing(temp);
					plus_result = true;
					vec.clear();
				}
				else vec.clear();
			}
		}
		if (plus_result == false) break;
		else if (plus_result == true) {
			result++;
			plus_result = false;
		}
		memset(&visited, false, sizeof(visited));
	}
	cout << result << "\n";

	return 0;
}
