#include <bits/stdc++.h>
using namespace std;
	
main(){
	int m, n;
	cout<<"Количество узлов:"<<endl;
	cin>> n;
	cout<<endl;
	
	cout<<"Количество вершин:"<<endl;
	cin>> m;
	cout<<endl;
	
	vector < pair < int, pair<int,int> > > g (m);
	
	cout<<"Веса нитей (A B вес):"<<endl;
	for (int i=0; i<m; i++)
		cin>>g[i].second.first>>g[i].second.second>>g[i].first;

	int cost = 0;
	vector < pair<int,int> > res;
	
	sort (g.begin(), g.end());
	vector<int> tree_id (n);
	
	for (int i=0; i<n; ++i)
		tree_id[i] = i;
		
	for (int i=0; i<m; ++i)
	{
		int a = g[i].second.first,  b = g[i].second.second,  l = g[i].first;
		if (tree_id[a] != tree_id[b])
		{
			cost += l;
			res.push_back (make_pair (a, b));
			int old_id = tree_id[b],  new_id = tree_id[a];
			for (int j=0; j<n; ++j)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;
		}
	}
	
	cout<<endl<<"Минимальное ост. дерево:"<<endl;

	for (int i=0; i<res.size(); i++)
		cout<<res[i].first<<" - "<<res[i].second<<endl;
	cout<<"Вес = "<<cost;
	
		
}
