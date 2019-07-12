#include <vector>
#include <iostream>

using namespace std;

void scan_right(vector<int> &cv, int &sp, int k) {
	sp = k - 1;
	++cv[sp];
}

void scan_left(vector<int> &cv, int &sp, int &finished, vector<int> &left) {
	while (sp >= 0) {
		if (cv[sp] <= left[sp]) break;
		if (sp == 0) {
			finished = 1;
			break;
		}
		cv[sp] = 0;
		--sp;
		++cv[sp];
	}
}

int getMoney(int amount, vector<int> kamount, vector<int> &left, vector<int> &give) {
	int k = kamount.size();
	// Current variants
	vector<int> cv(k);
	// Scan position
	int sp = k - 1;
	int min_kcount = amount;
	vector<int> best_cv;
	int finished = 0;
	int cycle = 0;
	while (1) {
		int sum = 0;
		int kcount = 0;
		for (int i = 0; i < k; ++i) {
			sum += cv[i] * kamount[i];
			kcount += cv[i];
		}
		if (sum == amount && kcount < min_kcount) {
			best_cv = cv;
			min_kcount = kcount;
		}
		++cycle;
		scan_right(cv, sp, k);
		scan_left(cv, sp, finished, left);
		if (finished) break;
	}
	cout << "Cycles: " << cycle << "\n";
	if (!best_cv.size()) return 1;
	give.clear();
	give.resize(k);
	for (int i = 0; i < k; ++i) {
		give[i] = best_cv[i];
		left[i] = left[i] - best_cv[i];
	}
	return 0;
}

int main() {
	vector<int> kamount = { 5000, 1000, 500, 100, 50,  30 };
	vector<int> left = { 4,    5,    2,   5,   100, 23 };
	vector<int> give;
	int k = kamount.size();
	int amount = 7620;
	cout << "Giving " << amount << "\n";
	int res = getMoney(amount, kamount, left, give);
	if (res) {
		cout << "Impossible\n";
	}
	else {
		cout << "Give: ";
		for (int i = 0; i < k; ++i) {
			cout << give[i] << "x" << kamount[i] << " ";
		}
		cout << "\nLeft: ";
		for (int i = 0; i < k; ++i) {
			cout << left[i] << "x" << kamount[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}
