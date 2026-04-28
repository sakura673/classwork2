#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct objekt {

	float x, y, w, h;
	objekt* children[4][100];

	void print() const {
		cout << setw(15) << left << x;
		cout << y;
		cout << setw(15) << right << w;
		cout << setw(15) << right << h << endl;
		cout << string(46, '-') << endl;
	}

};

void static print_zag() {

	cout << left << setw(15) << "x" << "y" << setw(15) << right << "w" << setw(15) << right << "h" << endl;
	cout << string(46, '-') << endl;

}

bool peresech(objekt* a, objekt* b) {

	if (a == nullptr || b == nullptr) return false;
	if (a->x + a->w <= b->x ||
		b->x + b->w <= a->x ||
		a->y + a->h <= b->y ||
		b->y + b->h <= a->y) {
		return false;
	}
	return true;

}

int el_peresech(objekt* chill[100]) {

	int schet = 0;
	for (int i = 0; i < 4; i++) {
		if (chill[i] == nullptr) {
			continue;
		}
		for (int k = i + 1; k < 100; k++) {
			if (i == k) {
				continue;
			}
			else if (peresech(chill[i], chill[k])) {
				schet++;
			}
			else {
				continue;
			}
		}
	}
	return schet;

}

int all_peresech(objekt* chill[4][100]) {

	int schet = 0;
	for (int i = 0; i < 4; i++) {
		schet += el_peresech(chill[i]);
	}
	for (int i = 0; i < 4; i++) {
		for (int k = i + 1; k < 4; k++) {
			for (int j = 0; j < 100; j++) {
				for (int h = j + 1; h < 100; h++) {
					if (chill[i][j] == nullptr or chill[k][h] == nullptr) {
						continue;
					}
					if (peresech(chill[i][j], chill[k][h])) {
						schet++;
						continue;
					}
				}
			}
		}
	}
	return schet;

}

void sob(objekt* chill) {

	float pl, ob;
	pl = chill->w * chill->w;
	ob = chill->w * chill->w * chill->h;
	cout << "ploshad: " << pl << endl;
	cout << "obem: " << ob << endl;

}

void del(objekt* &chill) {

	if (chill != nullptr) {
		delete chill;
		chill = nullptr;
	}

}

void printik(objekt* chill[100]) {

	print_zag();
	for (int i = 0; i < 100; i++) {
		if (chill[i] != nullptr) {
			chill[i]->print();
		}
	}

}

int static proverka(float xx, float yy) {

	if (xx > 0 and yy > 0) {
		return 1;
	}
	else if (xx < 0 and yy > 0) {
		return 2;
	}
	else if (xx < 0 and yy < 0) {
		return 3;
	}
	else if (xx > 0 and yy < 0) {
		return 4;
	}
	else {
		return -1;
	}

}

int static search(objekt* chill[100], float xx, float yy, float ww, float hh) {

	for (int i = 0; i < 100; i++) {
		if (chill[i] != nullptr) {
			if (chill[i]->x == xx and chill[i]->y == yy and chill[i]->w == ww and chill[i]->h == hh) {
				chill[i]->print();
				return i;
			}
		}
		else {
			continue;
		}
	}
	return 1000 - 7;

}

float s_peresech(objekt* a, objekt* b) {

	if (a == nullptr || b == nullptr) return 0;

	float overlapX = min(a->x + a->w, b->x + b->w) - max(a->x, b->x);
	float overlapY = min(a->y + a->h, b->y + b->h) - max(a->y, b->y);

	if (overlapX <= 0 || overlapY <= 0) return 0;
	return overlapX * overlapY;

}

int main() {

	objekt* root = new objekt();
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 100; k++) {
			root->children[i][k] = nullptr;
		}
	}

	int arr[2];

	int p, s, k, schet;
	float xx, x1, yy, y1, ww, w1, hh, h1, ress;
	int vibor, cont, num = 1;
	while (num == 1) {

		cout << "1(add) 2(delete) 3(search) 4(print)" << endl;
		cout << "5(s,v) 6(summa peresech) 7(s peresech): ";
		cin >> vibor;

		switch (vibor) {

		case 1:

			do {

				cout << "x: ";
				cin >> xx;
				cout << "y: ";
				cin >> yy;
				cout << "w: ";
				cin >> ww;
				cout << "h: ";
				cin >> hh;
				objekt* newNode = new objekt();
				newNode->x = xx;
				newNode->y = yy;
				newNode->w = ww;
				newNode->h = hh;
				for (int i = 0; i < 100; i++) {
					if (root->children[proverka(xx, yy) - 1][i] == nullptr) {
						root->children[proverka(xx, yy) - 1][i] = newNode;
						break;
					}
				}
				cout << "continue? 1/0:" << endl;
				cin >> cont;

			} while (cont == 1);
			break;

		case 2:

			cout << "x: ";
			cin >> xx;
			cout << "y: ";
			cin >> yy;
			cout << "w: ";
			cin >> ww;
			cout << "h: ";
			cin >> hh;
			p = proverka(xx, yy);
			if (p == 1) {
				for (int i = 0; i < 100; i++) {
					if (root->children[0][i] != nullptr and root->children[0][i]->x == xx and root->children[0][i]->y == yy and root->children[0][i]->w == ww and root->children[0][i]->h == hh) {
						del(root->children[0][i]);
					}
				}
			}
			else if (p == 2) {
				for (int i = 0; i < 100; i++) {
					if (root->children[1][i] != nullptr and root->children[1][i]->x == xx and root->children[1][i]->y == yy and root->children[1][i]->w == ww and root->children[1][i]->h == hh) {
						del(root->children[1][i]);
					}
				}
			}
			else if (p == 3) {
				for (int i = 0; i < 100; i++) {
					if (root->children[2][i] != nullptr and root->children[2][i]->x == xx and root->children[2][i]->y == yy and root->children[2][i]->w == ww and root->children[2][i]->h == hh) {
						del(root->children[2][i]);
					}
				}
			}
			else if (p == 4) {
				for (int i = 0; i < 100; i++) {
					if (root->children[3][i] != nullptr and root->children[3][i]->x == xx and root->children[3][i]->y == yy and root->children[3][i]->w == ww and root->children[3][i]->h == hh) {
						del(root->children[3][i]);
					}
				}
			}
			break;

		case 3:

			cout << "x: ";
			cin >> xx;
			cout << "y: ";
			cin >> yy;
			cout << "w: ";
			cin >> ww;
			cout << "h: ";
			cin >> hh;
			p = proverka(xx, yy);
			if (p == 1) {
				search(root->children[0], xx, yy, ww, hh);
			}
			else if (p == 2) {
				search(root->children[1], xx, yy, ww, hh);
			}
			else if (p == 3) {
				search(root->children[2], xx, yy, ww, hh);
			}
			else if (p == 4) {
				search(root->children[3], xx, yy, ww, hh);
			}
			break;

		case 4:

			cout << "enter element: ";
			cin >> p;
			if (p == 1) {
				printik(root->children[0]);
			}
			else if (p == 2) {
				printik(root->children[1]);
			}
			else if (p == 3) {
				printik(root->children[2]);
			}
			else if (p == 4) {
				printik(root->children[3]);
			}
			break;

		case 5:

			cout << "x: ";
			cin >> xx;
			cout << "y: ";
			cin >> yy;
			cout << "w: ";
			cin >> ww;
			cout << "h: ";
			cin >> hh;
			p = proverka(xx, yy);
			if (p == 1) {
				s = search(root->children[0], xx, yy, ww, hh);
				k = 0;
			}
			else if (p == 2) {
				s = search(root->children[1], xx, yy, ww, hh);
				k = 1;
			}
			else if (p == 3) {
				s = search(root->children[2], xx, yy, ww, hh);
				k = 2;
			}
			else if (p == 4) {
				s = search(root->children[3], xx, yy, ww, hh);
				k = 3;
			}
			if (s == 1000 - 7) {
				cout << "error!" << endl;
				break;
			}
			sob(root->children[k][s]);
			break;

		case 6:

			schet = all_peresech(root->children);
			cout << "all pr: " << schet << endl;
			break;

		case 7:

			for (int i = 0; i < 2; i++) {

				cout << "x: ";
				cin >> xx;
				cout << "y: ";
				cin >> yy;
				cout << "w: ";
				cin >> ww;
				cout << "h: ";
				cin >> hh;
				p = proverka(xx, yy);
				if (i == 0) {
					if (p == 1) {
						arr[0] = search(root->children[0], xx, yy, ww, hh);
						k = 0;
					}
					else if (p == 2) {
						arr[0] = search(root->children[1], xx, yy, ww, hh);
						k = 1;
					}
					else if (p == 3) {
						arr[0] = search(root->children[2], xx, yy, ww, hh);
						k = 2;
					}
					else if (p == 4) {
						arr[0] = search(root->children[3], xx, yy, ww, hh);
						k = 3;
					}
				}
				else {
					if (p == 1) {
						arr[1] = search(root->children[0], xx, yy, ww, hh);
						s = 0;
					}
					else if (p == 2) {
						arr[1] = search(root->children[1], xx, yy, ww, hh);
						s = 1;
					}
					else if (p == 3) {
						arr[1] = search(root->children[2], xx, yy, ww, hh);
						s = 2;
					}
					else if (p == 4) {
						arr[1] = search(root->children[3], xx, yy, ww, hh);
						s = 3;
					}
				}

			}
			if (arr[0] == 1000 - 7 or arr[1] == 1000 - 7) {
				cout << "error!" << endl;
				break;
			}

			ress = s_peresech(root->children[k][arr[0]], root->children[s][arr[1]]);
			cout << "Result: " << ress << endl; 
			break;

		}

		cout << "continue? 1/0:" << endl;
		cin >> num;

	}

}
