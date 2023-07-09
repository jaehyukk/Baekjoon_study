#include<iostream>
#include<vector>
#include<memory.h>
#include<algorithm>
using namespace std;

struct Block {
	int normal = 0;
	int rainbow = 0;
	int x;
	int y;
	int normal_value;
	vector<pair<int, int>> vec;
};

int n, m;
vector<Block> block;
vector<pair<int, int>> rainbow_ex;
vector<pair<int, int>> rainbow_yes;
int graph[21][21];
bool visited[21][21] = { false, };
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1, 1, 0, 0 };
int score = 0;

bool compare(pair<int, int>& a, pair<int, int>& b) {
	if (a.first < b.first) {
		return true;
	}
	else if (a.first == b.first) {
		if (a.second < b.second) {
			return true;
		}
		return false;
	}
	else return false;
}

bool cmp(Block a, Block b) {
	if (a.vec.size() > b.vec.size()) {
		return true;
	}
	else if (a.vec.size() == b.vec.size()) {
		if (a.rainbow > b.rainbow) {
			return true;
		}
		else if (a.rainbow == b.rainbow) {
			if (a.y > b.y) {
				return true;
			}
			else if (a.y == b.y) {
				if (a.x > b.x) {
					return true;
				}
				return false;
			}
			return false;
		}
		else return false;
	}
	else return false;
}

void rotation() {
	int temp_graph[21][21] = { -2, };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp_graph[i][j] = graph[j][n - i - 1];
		}
	}
	memcpy(graph, temp_graph, sizeof(graph));
}

void gravity() {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] == -10 && i != 0) {
				for (int k = i - 1; k >= 0; k--) {
					if (graph[k][j] == -1) break;
					else if (graph[k][j] == -10) continue;
					else {
						graph[i][j] = graph[k][j];
						graph[k][j] = -10;
						break;
					}
				}
			}
		}
	}
	return;
}

int block_pop() {
	int num = block[0].vec.size();
	for (int i = 0; i < num; i++) {
		int y = block[0].vec[i].first;
		int x = block[0].vec[i].second;
		graph[y][x] = -10;
	}
	return num * num;
}

void dfs(int y, int x, int cnt) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n || visited[ny][nx] == true) continue;

		if (graph[ny][nx] == 0 || graph[ny][nx] == block[cnt].normal_value) {
			if (visited[ny][nx] == false) {
				visited[ny][nx] = true;
				block[cnt].vec.push_back({ ny, nx });

				if (graph[ny][nx] == 0) {
					block[cnt].rainbow++;
					rainbow_yes.push_back({ ny, nx });
				}
				else if (graph[ny][nx] == block[cnt].normal_value) {
					block[cnt].normal++;
					rainbow_ex.push_back({ ny, nx });
				}

				dfs(ny, nx, cnt);
			}
			else continue;
		}
		else continue;
	}
	return;
}

void block_check() {			// 블록 영역 확인
	int block_cnt = 0;
	bool check = false;
	while (1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j] == false) {
					if (graph[i][j] > 0) {
						block.push_back({ 0,0, });		// 영역 초기값
						block[block_cnt].normal_value = graph[i][j];
						block[block_cnt].normal++;
						block[block_cnt].vec.push_back({ i, j });
						rainbow_ex.push_back({ i, j });
						visited[i][j] = true;
						dfs(i, j, block_cnt);

						if (block[block_cnt].vec.size() < 2 || block[block_cnt].normal == 0) {
							block.pop_back();
							rainbow_ex.clear();
						}
						else {
							sort(rainbow_ex.begin(), rainbow_ex.end(), compare);
							block[block_cnt].y = rainbow_ex[0].first;
							block[block_cnt].x = rainbow_ex[0].second;
							block_cnt++;
							check = true;
							rainbow_ex.clear();
							for (int i = 0; i < rainbow_yes.size(); i++) {
								visited[rainbow_yes[i].first][rainbow_yes[i].second] = false;
							}
						}
					}
					else continue;
				}
			}
		}
		if (check == false) break;
		else {
			if (block.size() > 1) {
				sort(block.begin(), block.end(), cmp); // 여러 블록 중 제거해야 할 블록 선정
			}

			score += block_pop();
			gravity();
			rotation();
			gravity();

			check = false;
			memset(&visited, false, sizeof(visited));
			block.clear();
			block_cnt = 0;
		}
	}
	return;
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;
			graph[i][j] = num;
		}
	}
	block_check();			// 체크 시작
	cout << score << "\n";

	return 0;
}
