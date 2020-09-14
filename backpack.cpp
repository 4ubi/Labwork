#include <bits/stdc++.h>

using namespace std;


void sortByWeightIncrease(int *m,int  *c, int n)
{
	int flag = 0;

	while(!flag) {
		flag = 1;

		for(int i = 0; i < n-1; i++) {
			if (m[i] > m[i+1]) {
				swap(m[i], m[i+1]);
				swap(c[i], c[i+1]);
				flag = 0;
			}
		}
	}

}


void addThingsToBackpack(int mx, int n, int *m, int *d, int *c)
{
	int tmpMax;

	for(int x = 1; x <= mx; x++) {
		tmpMax = 0;

		for (int i = 0; i < n; i++) {
			if ((x-m[i]) >= 0) {
				if (d[x - m[i]] + c[i] > tmpMax) {
					tmpMax = d[x - m[i]] + c[i];
				}
			}
		}

		d[x] = tmpMax;
	}
}

int main()
{
	int n, mx, tmpMax;
	int m[1000], c[1000], d[1000] = {0};

	cout << "Number of various things" << endl;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cout << endl << "m[" << i <<"] = ";
		cin >> m[i];
		cout << endl << "c[" << i << "] = ";
		cin >> c[i];
	}


	cout << "Input carrying capacity = ";
	cin >> mx;

	sortByWeightIncrease(m, c, n);

	addThingsToBackpack(mx, n, m, d, c);

	cout << endl << endl;

	for (int i = 0; i <= mx; i++) {
		cout << d[i] << " ";
	}

	cout << endl << endl;

	cout << "Value of backpack = " << d[mx];

	cout << endl << "Things in backpack (m, c): " << endl;
	
	while (mx > 0) {
		for (int i = 0; i < n; i++) {
			if (mx - m[i] >= 0) {
				if (d[mx] - c[i] == d[mx-m[i]]) {
					cout << "(" << m[i] << "," << c[i] << ")" << endl;
					mx -= m[i];
					break;
				}
			}
		}	
	}
}


