#include<iostream>
#include<vector>
#include<memory.h>
using namespace std;

int n, m;
int graph[51][51];
bool visited[51][51] = { false };
int dx[4] = { -1,1,-1,1 };
int dy[4] = { -1,-1,1,1 };
vector<pair<int, int>> cloud;

int sum_water() {
	int total = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			total += graph[i][j];
		}
	}
	return total;
}

void cloud_plus() {
	cloud.clear();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] >= 2 && visited[i][j] == false) {
				cloud.push_back({ i, j });
				graph[i][j] -= 2;
			}
		}
	}
}

void water_plus() {
	for (int i = 0; i < cloud.size(); i++) {
		for (int j = 0; j < 4; j++) {
			int ny = cloud[i].first + dy[j];
			int nx = cloud[i].second + dx[j];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (graph[ny][nx] == 0) continue;
			graph[cloud[i].first][cloud[i].second]++;
		}
	}
}

void raining() {
	memset(&visited, false, sizeof(visited));
	for (int i = 0; i < cloud.size(); i++) {
		int y = cloud[i].first;
		int x = cloud[i].second;
		graph[y][x]++;
		visited[y][x] = true;
	}
}

void cloud_move(int dir, int cnt) {
	for (int i = 0; i < cnt; i++) {
		switch (dir)
		{
		case 1:	// 왼쪽
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].second - 1 < 0) cloud[i].second = n - 1;
				else cloud[i].second--;
			}
			break;

		case 2:	// 왼쪽 대각선 위
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first - 1 < 0) cloud[i].first = n - 1;
				else cloud[i].first--;

				if (cloud[i].second - 1 < 0) cloud[i].second = n - 1;
				else cloud[i].second--;
			}
			break;

		case 3:	// 위쪽
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first - 1 < 0) cloud[i].first = n - 1;
				else cloud[i].first--;
			}
			break;

		case 4:		// 오른쪽 대각선 위
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first - 1 < 0) cloud[i].first = n - 1;
				else cloud[i].first--;

				if (cloud[i].second + 1 >= n) cloud[i].second = 0;
				else cloud[i].second++;
			}
			break;

		case 5:		// 오른쪽
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].second + 1 >= n) cloud[i].second = 0;
				else cloud[i].second++;
			}
			break;

		case 6:		// 오른쪽 대각선 아래
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first + 1 >= n) cloud[i].first = 0;
				else cloud[i].first++;

				if (cloud[i].second + 1 >= n) cloud[i].second = 0;
				else cloud[i].second++;
			}
			break;

		case 7:		// 아래
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first + 1 >= n) cloud[i].first = 0;
				else cloud[i].first++;
			}
			break;

		case 8:		// 왼쪽 대각선 아래
			for (int i = 0; i < cloud.size(); i++) {
				if (cloud[i].first + 1 >= n) cloud[i].first = 0;
				else cloud[i].first++;

				if (cloud[i].second - 1 < 0) cloud[i].second = n - 1;
				else cloud[i].second--;
			}
			break;

		default:
			break;
		}
	}
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);

	int result = 0;

	// input
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num;
			cin >> num;
			graph[i][j] = num;
		}
	}

	// cloud 생성
	cloud.push_back({ n - 1, 0 });
	cloud.push_back({ n - 1, 1 });
	cloud.push_back({ n - 2, 0 });
	cloud.push_back({ n - 2, 1 });

	// cloud 나머지 기능
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		cloud_move(x, y);
		raining();
		water_plus();
		cloud_plus();
	}
	result = sum_water();
	cout << result << "\n";

	return 0;
}
