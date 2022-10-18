#include <iostream>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

using namespace std;

class Map {

public:

	int size = 4;
	vector<vector<int>> map;
	Map() {

		CreateMap();
	}

	void CreateMap() {
		for (int i = 0; i < size; i++) {
			vector<int> row;
			for (int j = 0; j < size; j++) {
				row.push_back(0);
			}
			map.push_back(row);
		}
	}

	void setNum(int x, int y, int num) {
		map[x][y] = num;
	}

	int getNum(int x, int y) {
		return map.at(x).at(y);
	}

	void CreateNum() {
		int x = rand() % 4;
		int y = rand() % 4;
		while (getNum(x, y) != 0) {
			x = rand() % size;
			y = rand() % size;
		}
		int num_choice = rand() % 2;
		if (num_choice == 0) setNum(x, y, 2);
		else setNum(x, y, 4);
	}

	int MoveToLeft() {
		int IncreasedScore = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (getNum(i, j) > 0) {
					int x = j;
					while (x >= 1) {
						if (getNum(i, x - 1) == 0) {
							setNum(i, x - 1, getNum(i, x));
							setNum(i, x, 0);
						}
						else if (getNum(i, x - 1) == getNum(i, x)) {
							int new_num = getNum(i, x) * 2;
							setNum(i, x - 1, new_num);
							setNum(i, x, 0);
							IncreasedScore += new_num;
							break;
						}
						x--;
					}
				}
			}
		}
		return IncreasedScore;
	}

	int MoveToRight() {
		int IncreasedScore = 0;
		for (int i = 0; i < size; i++) {
			for (int j = size - 1; j >= 0; j--) {
				if (getNum(i, j) > 0) {
					int x = j;
					while (x < size - 1) {
						if (getNum(i, x + 1) == 0) {
							setNum(i, x + 1, getNum(i, x));
							setNum(i, x, 0);
						}
						else if (getNum(i, x + 1) == getNum(i, x)) {
							int new_num = getNum(i, x) * 2;
							setNum(i, x + 1, new_num);
							setNum(i, x, 0);
							IncreasedScore += new_num;
							break;
						}
						x++;
					}
				}
			}
		}
		return IncreasedScore;
	}

	int MoveToUp() {
		int IncreasedScore = 0;
		for (int j = 0; j < size; j++) {
			for (int i = 0; i < size; i++) {
				if (getNum(i, j) > 0) {
					int y = i;
					while (y > 0) {
						if (getNum(y - 1, j) == 0) {

							setNum(y - 1, j, getNum(y, j));
							setNum(y, j, 0);
						}
						else if (getNum(y - 1, j) == getNum(y, j)) {

							int new_num = getNum(y, j) * 2;
							setNum(y - 1, j, new_num);
							setNum(y, j, 0);
							IncreasedScore += new_num;
							break;
						}
						y--;
					}
				}
			}
		}
		return IncreasedScore;
	}

	int MoveToDown() {

		int IncreasedScore = 0;

		for (int j = 0; j < size; j++) {
			for (int i = size - 2; i >= 0; i--) {
				if (getNum(i, j) > 0) {
					int y = i;
					while (y < size - 1) {
						if (getNum(y + 1, j) == 0) {
							setNum(y + 1, j, getNum(y, j));
							setNum(y, j, 0);
						}
						else if (getNum(y + 1, j) == getNum(y, j)) {
							int new_num = getNum(y, j) * 2;
							setNum(y + 1, j, new_num);
							setNum(y, j, 0);
							IncreasedScore += new_num;
							break;
						}
						y++;
					}
				}
			}
		}
		return IncreasedScore;
	}

	bool operator != (Map& otherMap) {

		if (this->size != otherMap.size) return true;

		for (int i = 0; i < this->size; i++) {

			for (int j = 0; j < this->size; j++) {

				if (this->getNum(i, j) != otherMap.getNum(i, j)) {

					return true;
				}
			}
		}
		return false;
	}

	void print() {

		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				cout << getNum(i, j);
			}
			cout << endl;
		}
	}
};

void gotoxy(int y, int x)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}


class Drawer {

public:

	char DrawingMap(int y, int x, int max_y, int max_x) {


		if (x % 7 == 0) {

			return '|';
		}
		else if (y % 2 == 0) {

			return '.';
		}
		else {

			return ' ';
		}
	}

	void ShowScore(int score, int size) {

		string sc_str = to_string(score);

		gotoxy(size * 2 + 10, 2);
		cout << "Score: " << score;

	}

	void Draw(Map map) {

		gotoxy(1, 0);

		int max_y = 9; // 2 * 4 + 1
		int max_x = 29; // 4 * 6 + 4 + 1

		for (int i = 0; i < max_y; i++) {

			for (int j = 0; j < max_x; j++) {

				char m = DrawingMap(i, j, max_y, max_x);

				cout << m;
			}
			cout << endl;
		}

		for (int i = 0; i < map.size; i++) {

			for (int j = 0; j < map.size; j++) {

				int val = map.getNum(i, j);
				string val_str = to_string(val);
				if (val_str == "0") val_str = " ";

				if (val_str.length() < 4) {

					int l = val_str.length();
					for (int k = 0; k < 4 - l; k++) {
						val_str = " " + val_str;
					}
				}

				gotoxy(i * 2 + 1 + 1, j * 7 + 1 + 1);
				cout << val_str;
			}
		}

	}
};

class Game {

public:
	Map* map;
	Drawer drawer;
	int score = 0;
	int size;
	int currentMax = 0;
	bool isGameOver = false;
	bool hasWon = false;
	bool exit = false;



	void Init() {

		system("cls");
		score = 0;
		currentMax = 0;
		isGameOver = false;
		map = new Map();

		map->CreateNum();
		map->CreateNum();
	}

	void getAction() {

		while (true) {

			bool pressed = false;

			if (GetAsyncKeyState(VK_LEFT) & 0x8000 != 0) {
				score += map->MoveToLeft();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0) {
				score += map->MoveToRight();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0) {
				score += map->MoveToUp();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0) {
				score += map->MoveToDown();
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000 != 0) {
				exit = true;
				pressed = true;
			}

			if (pressed) {

				drawer.ShowScore(score, size);
				map->CreateNum();
				break;
			}
		}
	}

	void CheckWin() {

		for (int i = 0; i < size; i++) {

			for (int j = 0; j < size; j++) {

				int val;
				val = map->getNum(i, j);
				if (val > currentMax) {

					currentMax = val;
					if (currentMax == 2048) {

						hasWon = true;
					}
				}
			}
		}
	}

	void EndGame() {

		bool dif = false;

		Map expMap = *map;
		expMap.MoveToLeft();
		if (*map != expMap) {
			dif = true;
		}

		if (!dif) {

			expMap = *map;
			expMap.MoveToRight();
			if (*map != expMap) {
				dif = true;
			}
		}

		if (!dif) {

			expMap = *map;
			expMap.MoveToUp();
			if (*map != expMap) {
				dif = true;
			}
		}

		if (!dif) {

			expMap = *map;
			expMap.MoveToDown();
			if (*map != expMap) {
				dif = true;
			}
		}

		if (dif == false) {

			isGameOver = true;
		}
	}

	void Show() {

	play:
		Init();
		while (true) {

			drawer.Draw(*map);
			drawer.ShowScore(score, size);
			CheckWin();
			EndGame();

			if (hasWon || isGameOver) {

				gotoxy(size * 2 + 10, 2);
				if (hasWon) {

					cout << "You got 2048! Do you want to restart? (y/n): ";
				}
				else {

					cout << "You lost! Do you want to restart? (y/n): ";
				}
				char c;
				cin >> c;
				if (c == 'y') {
					goto play;
				}
				else {
					exit = true;
					break;
				}
			}
			getAction();
			if (exit) goto out;
		}
	out: {

		gotoxy(0, 0);
		system("cls");
		}
	}
};

int main() {

	system("cls");
	Game game;
	game.Show();
}