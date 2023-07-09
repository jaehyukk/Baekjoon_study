#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> map(n, vector<int>(m, 0));
	int botr, botc, botdir;
	cin >> botr >> botc >> botdir;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	int answer = 0;
	bool all_clean = false;
	while (1) {

		all_clean = false;
		if (map[botr][botc] == 0) {
			map[botr][botc] = 2;
			answer++;
		}

		for (int i = 0; i < 4; i++) {
			if (botdir == 0) {
				botdir = 3; 
				
				if (botc - 1 >= 0 && map[botr][botc - 1] == 0) {
					
					botc -= 1;
					break;
				}
			}
			else if (botdir == 1) {
				botdir = 0;
				if (botr - 1 >= 0 && map[botr - 1][botc] == 0) {
					botr -= 1;
					break;
				}
			}
			else if (botdir == 2) {
				botdir = 1;
				if (botc + 1 < m && map[botr][botc + 1] == 0) {
					botc += 1;
					break;
				}
			}
			else {
				botdir = 2;
				if (botr + 1 < n && map[botr + 1][botc] == 0) {
					botr += 1;
					break;
				}
			}
			if (i == 3) {
				all_clean = true;
			}
		}
		if (all_clean) {
			if (botdir == 0) {
				if (map[botr + 1][botc] != 1) {
					botr += 1;
				}
				else {
					break;
				}
			}
			else if (botdir == 1) {
				if (map[botr][botc - 1] != 1) {
					botc -= 1;
				}
				else {
					break;
				}
			}
			else if (botdir == 2) {
				if (map[botr - 1][botc] != 1) {
					botr -= 1;
				}
				else {
					break;
				}
			}
			else {
				if (map[botr][botc + 1] != 1) {
					botc += 1;
				}
				else {
					break;
				}
			}
		}
	}
	cout << answer;
	return 0;
}
