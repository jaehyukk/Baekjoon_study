#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
int graph[51][51];
int sy, sx;
int bead_cnt = 0;
int one = 0, two = 0, three = 0;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0,1,0,-1 };
vector<int> vec;

void filling() {
	int cnt = 1, dir = 0;
	int cy = n / 2;
	int cx = n / 2;
	int while_cnt = 0;

	int temp = vec.size();
	while (1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				int ny = cy + dy[dir];
				int nx = cx + dx[dir];

				if (ny >= 0 && ny < n && nx >= 0 && nx < n) {
					if (while_cnt < temp) {
						graph[ny][nx] = vec[while_cnt];
					}
					else {
						graph[ny][nx] = 0;
					}
				}

				cy = ny;
				cx = nx;
				while_cnt++;
				if (while_cnt == n * n) return;
			}
			dir++;
			dir = dir % 4;
		}
		cnt++;
	}
}

void transblock() {
	int cnt = 1, dir = 0, temp = 0;
	int cy = n / 2;
	int cx = n / 2;
	vector<pair<int, int>> block;

	// 블록 현황 파악
	int vecsize = vec.size();
	int num = vec[0];
	for (int i = 1; i < vecsize; i++) {
		if (num == vec[i]) {
			cnt++;
		}
		else if (num != vec[i]) {
			block.push_back({ cnt, num });
			num = vec[i];
			cnt = 1;
		}

		if (i == vecsize - 1) {
			block.push_back({ cnt, num });
		}
	}

	// 블록 변환
	int for_cnt = 1;
	cnt = 1;
	while (1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				if (for_cnt == n * n) return;

				int ny = cy + dy[dir];
				int nx = cx + dx[dir];

				if (for_cnt % 2 == 1) graph[ny][nx] = block[temp].first;
				else {
					graph[ny][nx] = block[temp].second;
					temp++;
				}
				if (temp == block.size()) {
					return;
				}
				cy = ny;
				cx = nx;
				for_cnt++;
			}
			dir++;
			dir = dir % 4;
		}
		cnt++;
	}
	return;
}

int explode() {
	int cnt = 1, size = 0;

	int vecsize = vec.size();
	int num = vec[0];
	int start;
	for (int i = 1; i < vecsize; i++) {
		if (num == vec[i]) {
			// 구슬 묶음 시작 지점 정하기
			if (i == 1) start = 0;
			else {
				if (cnt == 1) start = i - 1;
			}
			cnt++;

			// 구슬 폭발 조건(마지막 인덱스인 경우)
			if (i == vecsize - 1 && cnt >= 4) {
				fill(vec.begin() + start, vec.end(), 0);
				bead_cnt -= cnt;

				if (num == 1) one += cnt;
				else if (num == 2) two += cnt;
				else three += cnt;
			}
		}
		else if (num != vec[i]) {
			// 구슬 폭발 조건
			if (cnt >= 4) {
				fill(vec.begin() + start, vec.begin() + i, 0);
				bead_cnt -= cnt;

				if (num == 1) one += cnt;
				else if (num == 2) two += cnt;
				else three += cnt;
			}

			num = vec[i];
			cnt = 1;
		}
	}

	// 폭파된 구슬 제거
	cnt = 0;
	int i = 0;
	while (1) {
		if (vec[i] == 0) {
			vec.erase(vec.begin() + i);
			size++;
		}
		else i++;

		cnt++;
		if (cnt == vecsize) break;
	}
	filling();

	return size;
}

void moving(int length) {
	int cnt = 1, dir = 0;
	int cy = n / 2;
	int cx = n / 2;

	int while_cnt = 0;
	while (1) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < cnt; k++) {
				int ny = cy + dy[dir];
				int nx = cx + dx[dir];

				if (while_cnt == bead_cnt + length) {
					filling();
					return;
				}

				// 옮겨야 하는 구슬 담기
				if (graph[ny][nx] != 0) {
					vec.push_back({ graph[ny][nx] });
				}

				cy = ny;
				cx = nx;
				while_cnt++;
			}
			dir++;
			dir = dir % 4;
		}
		cnt++;
	}
}

void ice_frac(int dir, int length) {

	switch (dir)
	{
	case 1:
		for (int i = 1; i <= length; i++) {
			if (graph[sy - i][sx] != 0) {
				graph[sy - i][sx] = 0;
				bead_cnt -= 1;
			}
		}
		break;

	case 2:
		for (int i = 1; i <= length; i++) {
			if (graph[sy + i][sx] != 0) {
				graph[sy + i][sx] = 0;
				bead_cnt -= 1;
			}
		}
		break;

	case 3:
		for (int i = 1; i <= length; i++) {
			if (graph[sy][sx - i] != 0) {
				graph[sy][sx - i] = 0;
				bead_cnt -= 1;
			}
		}
		break;

	case 4:
		for (int i = 1; i <= length; i++) {
			if (graph[sy][sx + i] != 0) {
				graph[sy][sx + i] = 0;
				bead_cnt -= 1;
			}
		}
		break;

	default:
		break;
	}
	return;
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num;
			cin >> num;
			graph[i][j] = num;
			if (num != 0) bead_cnt++;
		}
	}

	for (int i = 0; i < m; i++) {
		int dir, length;
		sy = n / 2;
		sx = n / 2;

		cin >> dir >> length;

		// 블리자드 마법
		ice_frac(dir, length);

		// 구슬 이동
		if (bead_cnt <= 0) break;
		moving(length);

		// 구슬 폭발
		int exp_block = explode();
		while (exp_block != 0) {
			if (vec.size() == 0 || bead_cnt == 0) break;

			exp_block = explode();
		}

		// 구슬 변환
		if (vec.size() != 0) transblock();

		vec.clear();
		bead_cnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (graph[i][j] != 0) bead_cnt++;
			}
		}
	}
	int result = one + 2 * two + 3 * three;
	cout << result << "\n";

	return 0;
}



/*
1. 배열의 최대 범위 = n * n - 1, transblock() 내의 while 탈출 조건 확인
2. 블리자드 마법 단계에서 마법 범위 내의 구슬이 없을 경우(0인 경우)는 제거 후에 구슬 bead_cnt 감소 안 함
*/
