#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int INF = 1000*1000*1000;

struct rib {
	int b, u, c, f;
	size_t back;
};

void add_rib (vector < vector<rib> > & g, int a, int b, int u, int c) {
	rib r1 = { b, u, c, 0, g[b].size() };
	rib r2 = { a, 0, -c, 0, g[a].size() };
	g[a].push_back (r1);
	g[b].push_back (r2);
}


int main(){
	
	int n, k;
	
	cin>>n;
	vector < vector<rib> > g (2*n+2);
	
	for(int i=1;i<=n;i++){
		
		add_rib( g , 0 , i , 1 , 0 );
		
		add_rib( g , n+i , 2*n+1 , 1 , 0 );
		
	}
	
	for(int i=1;i<=n;i++){
		for(int j=n+1;j<=2*n;j++){
			int d;
			cin>>d;
			add_rib( g , i , j , 1 , d );
		}
	}
	
	k=n;
	
	n=2*n+2;
	
	int s=0, t=n-1;
	//IDE PRAVO POSLE

	int flow = 0,  cost = 0;
	while (flow < k) {
		vector<int> id (n, 0);
		vector<int> d (n, INF);
		vector<int> q (n);
		vector<int> p (n);
		vector<size_t> p_rib (n);
		int qh=0, qt=0;
		q[qt++] = s;
		d[s] = 0;
		while (qh != qt) {
		
			int v = q[qh++];
			id[v] = 2;
			if (qh == n)  qh = 0;
			for (size_t i=0; i<g[v].size(); ++i) {
				rib & r = g[v][i];
				if (r.f < r.u && d[v] + r.c < d[r.b]) {
					d[r.b] = d[v] + r.c;
					if (id[r.b] == 0) {
						q[qt++] = r.b;
						if (qt == n)  qt = 0;
					}
					else if (id[r.b] == 2) {
						if (--qh == -1)  qh = n-1;
						q[qh] = r.b;
					}
					id[r.b] = 1;
					p[r.b] = v;
					p_rib[r.b] = i;
				}
			}
		}
		
		if (d[t] == INF)  break;
		int addflow = k - flow;
		for (int v=t; v!=s; v=p[v]) {
			
			int pv = p[v];  size_t pr = p_rib[v];
			addflow = min (addflow, g[pv][pr].u - g[pv][pr].f);
			
		}
		
		for (int v=t; v!=s; v=p[v]) {
			int pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;
			g[pv][pr].f += addflow;
			g[v][r].f -= addflow;
			cost += g[pv][pr].c * addflow;
		}
		flow += addflow;
	}

	cout<<"flow "<< flow <<endl;
	cout<<"cost "<< cost <<endl;
	
	return 0;
}



/*


3
20 25 20
15 10 35
33 17 25


4
5 9 3 6
8 7 8 2
6 10 12 7
3 10 8 6

*/



