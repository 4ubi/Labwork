#include <bits/stdc++.h>

using namespace std;

int main (){
    int lengthWay, minimal;
    int m[301], dump[301][1001]={0};

    cout << "Длина пути: ";
    cin >> lengthWay;

    int wayJump[lengthWay];
    cout << "Составить карту камней:" << endl;

    for (int i = 1; i <= lengthWay; i++) {
         cin >> m[i];
    }

	for (int i = 0; i<= lengthWay; i++){
	    for (int v = 0; v<= lengthWay/2; v++) {
	            dump[v][i] = 99999;
	    }
	}

	dump[0][0] = 0;

	for (int i = 0; i <= lengthWay; i++) {
	    for (int v = 0; v <= lengthWay/2; v++){
	        if (v > 0 && m[i+v]) {
	            dump[v][i+v] = min(dump[v][i+v], dump[v][i]+1);
	        }

        	if (v > 1 && m[i+v-1]) {
        	    dump[v-1][i+v-1] = min(dump[v-1][i+v-1], dump[v][i]+1);
        	}

        	if (m[i+v+1]) {
        	    dump[v+1][i+v+1] = min(dump[v+1][i+v+1], dump[v][i]+1);
        	}
        }
	}

	minimal = dump[0][lengthWay];

	for (int v = 0; v <= lengthWay/2; v++) {
        if (dump[v][lengthWay] < minimal) {
            minimal = dump[v][lengthWay];
        }
	}

	cout << endl << "Ответ: " << minimal << endl;
}
