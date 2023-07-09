#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<memory.h>
using namespace std;

int n, m, k, x = 0, y = 0;
int score = 0;
int dir = 0;
int graph_score;
int graph[21][21] = { 0, };
bool visited[21][21] = { false };
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1, -1 };
int dice[6] = { 5, 2, 1, 6, 4, 3 }; // 앞 뒤 위 아래 왼 오

void rotation() {
	if (dice[3] > graph[y][x]) {
		if (dir == 3) dir = 0;
		else dir++;
	}
	else if (dice[3] < graph[y][x]) {
		if (dir == 0) dir = 3;
		else dir--;
	}
	return;
}

void dice_state(int num) {
	int d0 = dice[0];
	int d1 = dice[1];
	int d2 = dice[2];
	int d3 = dice[3];
	int d4 = dice[4];
	int d5 = dice[5];

	if (num == 0) {			// east
		if (x + 1 == m) {
			dice[4] = d2;
			dice[3] = d4;
			dice[5] = d3;
			dice[2] = d5;
			x--;
			dir = 2;
		}
		else {
			dice[5] = d2;
			dice[3] = d5;
			dice[4] = d3;
			dice[2] = d4;
			x++;
		}
	}
	else if (num == 1) {	// south
		if (y + 1 == n) {
			dice[2] = d0;
			dice[0] = d3;
			dice[3] = d1;
			dice[1] = d2;
			y--;
			dir = 3;
		}
		else {
			dice[0] = d2;
			dice[3] = d0;
			dice[1] = d3;
			dice[2] = d1;
			y++;
		}
	}
	else if (num == 2) {	// west
		if (x - 1 < 0) {
			dice[5] = d2;
			dice[3] = d5;
			dice[4] = d3;
			dice[2] = d4;
			x++;
			dir = 0;
		}
		else {
			dice[4] = d2;
			dice[3] = d4;
			dice[5] = d3;
			dice[2] = d5;
			x--;
		}
	}
	else if (num == 3) {		// north
		if (y - 1 < 0) {
			dice[0] = d2;
			dice[3] = d0;
			dice[1] = d3;
			dice[2] = d1;
			y++;
			dir = 1;
		}
		else {
			dice[2] = d0;
			dice[0] = d3;
			dice[3] = d1;
			dice[1] = d2;
			y--;
		}
	}
}

int dice_starting(queue<pair<int, int>> q) {
	int cnt = 1;
	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dy[i];
			int nx = cx + dx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
			if (graph[ny][nx] != graph_score) continue;
			if (visited[ny][nx] == true) continue;

			q.push({ ny, nx });
			visited[ny][nx] = true;
			cnt++;
		}
	}
	return cnt;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int num;
			cin >> num;
			graph[i][j] = num;
		}
	}

	for (int i = 0; i < k; i++) {
		queue<pair<int, int>> q;
		dice_state(dir);
		q.push({ y, x });
		graph_score = graph[y][x];
		visited[y][x] = true;

		score += dice_starting(q) * graph_score;
		rotation();
		memset(&visited, false, sizeof(visited));
	}

	cout << score << "\n";

	return 0;
}
