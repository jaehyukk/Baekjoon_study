#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;

int n, m, cnt = 0, result = 0;
int graph[8][8], temp[8][8];
bool visited[8][8];
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0 , 0 };
vector<pair<int, int>> vec;

void dfs(int y, int x) {
	temp[y][x] = 2;
	visited[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (nx < 0 || ny < 0 || ny >= n || nx >= m) continue;

		if (temp[ny][nx] == 0 && visited[ny][nx] == false) {
			dfs(ny, nx);
		}
	}
}

void con(int y1, int x1, int y2, int x2, int y3, int x3) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			temp[i][j] = graph[i][j];
		}
	}
	memset(visited, false, sizeof(visited));
	temp[y1][x1] = 1;
	temp[y2][x2] = 1;
	temp[y3][x3] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (temp[i][j] == 2) dfs(i, j);
		}
	}
	cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (temp[i][j] == 0) cnt++;
		}
	}
	result = max(result, cnt);
}

void sel() {
	int index = vec.size();
	for (int i = 0; i < index - 2; i++) {
		int y1 = vec[i].first;
		int x1 = vec[i].second;
		for (int j = i + 1; j < index - 1; j++) {
			int y2 = vec[j].first;
			int x2 = vec[j].second;
			for (int k = j + 1; k < index; k++) {
				int y3 = vec[k].first;
				int x3 = vec[k].second;
				con(y1, x1, y2, x2, y3, x3);
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 0) {
				vec.push_back({ i, j });
			}
		}
	}
	sel();
	cout << result << '\n';

	return 0;
}
