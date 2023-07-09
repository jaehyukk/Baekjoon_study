#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

int n, q, l;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1, 1, 0 ,0 };
int graph[65][65] = { 0, };
int temp[65][65] = { 0, };
int temp2[65][65] = { 0, };
bool visited[65][65] = { false, };
int l_value[1001] = { 0, };
int row = 0;
int total_cnt = 0;

int dfs(int y, int x, int wid) {
	visited[y][x] = true;
	total_cnt += graph[y][x];
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= row || nx >= row || visited[ny][nx] == true) continue;
		if (graph[ny][nx] > 0) {
			wid = max(wid, dfs(ny, nx, wid + 1));
		}
	}
	return wid;
}

void resulting() {
	int block_cnt = 0;
	int temp_cnt = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (graph[i][j] > 0 && visited[i][j] != true) {
				block_cnt = dfs(i, j, 1);
				temp_cnt = max(temp_cnt, block_cnt);
			}
		}
	}
	cout << total_cnt << '\n';
	cout << temp_cnt << '\n';
	return;
}

void ice_braking() {
	vector<pair<int, int>> ice;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			if (graph[i][j] > 0) {
				// 주변 얼음 개수 파악
				int ice_cnt = 0;
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];

					if (ny < 0 || nx < 0 || ny >= row || nx >= row) continue;
					if (graph[ny][nx] > 0) {
						ice_cnt++;
					}
				}
				// 얼음 녹일 칸 담기
				if (ice_cnt <= 2) ice.push_back({ i, j });
			}
		}
	}
	// 얼음 녹이기
	for (int i = 0; i < ice.size(); i++) {
		graph[ice[i].first][ice[i].second]--;
	}
	return;
}

void rotation(int num) {
	int row2 = pow(2, num);
	int cnt = (row * row) / (row2 * row2);
	int seq = 0;
	int start_row = 0, start_col = 0;

	while (seq < cnt) {
		// 부분 격자 배열 복사
		int temp_row = 0, temp_col = 0;
		for (int i = start_row; i < start_row + row2; i++) {
			for (int j = start_col; j < start_col + row2; j++) {
				temp[temp_row][temp_col] = graph[i][j];
				temp_col++;
			}
			temp_row++;
			temp_col = 0;
		}

		// 부분 격자 회전
		for (int i = 0; i < row2; i++) {
			for (int j = 0; j < row2; j++) {
				temp2[i][j] = temp[row2 - j - 1][i];
			}
		}

		// 회전한 부분 격자 배열을 원래 배열에 대입하기
		temp_row = 0, temp_col = 0;
		for (int i = start_row; i < start_row + row2; i++) {
			for (int j = start_col; j < start_col + row2; j++) {
				graph[i][j] = temp2[temp_row][temp_col];
				temp_col++;
			}
			temp_row++;
			temp_col = 0;
		}

		// 다음 배열 위치 설정
		if (row - start_col == row2) {
			start_col = 0;
			start_row += row2;
		}
		else {
			start_col += row2;
		}
		seq++;
	}
	return;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> n >> q;
	row = pow(2, n);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			int num;
			cin >> num;
			graph[i][j] = num;
		}
	}
	for (int i = 0; i < q; i++) {
		cin >> l;
		l_value[i] = l;
	}
	
	for (int i = 0; i < q; i++) {
		rotation(l_value[i]);
		ice_braking();
	}
	resulting();

	return 0;
}
