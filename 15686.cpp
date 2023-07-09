#include<iostream>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;

int n, m, answer = 100000000;
vector<tuple<int, int, bool>> chicken;
vector<pair<int, int>> home;

int distance() {
	int result = 0, temp;
	for (int i = 0; i < home.size(); i++) {
		int dis = 100000000;
		for (int j = 0; j < chicken.size(); j++) {
			if (get<2>(chicken[j]) == false) continue;

			temp = abs(home[i].first - get<0>(chicken[j])) + abs(home[i].second - get<1>(chicken[j]));
			dis = min(temp, dis);
		}
		result += dis;
	}
	return result;
}

void dfs(int start, int cnt) {
	if (cnt == m) {		// m개의 치킨집이 선택된 경우
		int result = distance();
		answer = min(answer, result);
		return;
	}
	for (int i = start; i < chicken.size(); i++) {
		if (get<2>(chicken[i]) == true) continue;

		get<2>(chicken[i]) = true;		// 선택한 치킨집은 true로 설정
		dfs(i, cnt + 1);
		get<2>(chicken[i]) = false;
	}
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> n >> m;
	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;
			if (num == 1) home.push_back({ i, j });
			else if (num == 2) chicken.push_back({ i, j, false });
		}
	}
	dfs(0, 0);
	cout << answer << "\n";

	return 0;
}
