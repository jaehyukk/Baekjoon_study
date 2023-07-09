#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct Student {
	int person;
	int love[4];
};

struct Pos {
	int x;
	int y;
	int empty;
	int want;
};

int n;
int graph[21][21] = { 0, };
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { -1,1,0,0 };
vector<Student> student;
unordered_map<int, Student> um;

int score() {
	int total = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num = graph[i][j];
			int cnt = 0;

			// 상하좌우로 모든 자리 전수조사
			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;

				for (int l = 0; l < 4; l++) {
					if (graph[ny][nx] == um[num].love[l]) {
						cnt++;
						break;
					}
				}
			}
			// 점수 측정
			if (cnt == 1) total += 1;
			else if (cnt == 2) total += 10;
			else if (cnt == 3) total += 100;
			else if (cnt == 4) total += 1000;
		}
	}
	return total;
}

// 학생이 앉을 자리에 대한 우선순위 별 정렬
bool cmp(Pos a, Pos b) {
	if (a.want > b.want) {
		return true;
	}
	else if (a.want == b.want) {
		if (a.empty > b.empty) {
			return true;
		}
		else if (a.empty == b.empty) {
			if (a.y < b.y) {
				return true;
			}
			else if (a.y == b.y) {
				if (a.x < b.x) {
					return true;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

void sitting() {
	for (int i = 0; i < student.size(); i++) {
		vector<Pos> pos;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (graph[j][k] != 0) continue;

				int blank = 0;
				int fri = 0;

				// 상하좌우로 모든 자리 전수조사
				for (int l = 0; l < 4; l++) {
					int nx = k + dx[l];
					int ny = j + dy[l];

					if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;

					if (graph[ny][nx] == 0) blank++;	// 공석인 경우
					else {
						for (int m = 0; m < 4; m++) {
							int num = student[i].love[m];
							if (graph[ny][nx] == num) {
								fri++;
								break;
							}
						}
					}
				}
				pos.push_back({ k,j,blank,fri });
			}
		}
		// 가장 올바른 자리 찾기(정렬한 배열의 맨 앞이 가장 알맞은 자리)
		sort(pos.begin(), pos.end(), cmp);
		int px = pos[0].x;
		int py = pos[0].y;
		graph[py][px] = student[i].person;
	}
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// 값 입력 받기
	cin >> n;
	for (int i = 0; i < n * n; i++) {
		int num, a, b, c, d;
		cin >> num >> a >> b >> c >> d;
		student.push_back({ num, {a,b,c,d} });
		um[num] = { num, {a,b,c,d} };
	}

	// 자리 앉히기
	sitting();

	// 점수 측정
	int result = score();
	cout << result << "\n";

	return 0;
}

/*
점수 측정을 위해 별도의 배열을 만들어줄 때, 배열의 크기를 N^2으로 했어야 함
=> 배열 크기 조건 잘 확인하기
*/
