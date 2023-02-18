#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
 
struct edge{
	int kam,kap,flo,rev;
	edge( int a , int b , int c , int d ){
		kam=a,kap=b,flo=c,rev=d;
	}
	edge(){}
};
 
int n,m,i,a,b,c,cur;
int nivo[5002],nak[5002];
vector<edge> v[5002];
ll reza;
queue<int> q;
 
int dfs( int cur , int flo ){
	
	if( cur==n )return flo;
	
	for(;nak[cur] < v[cur].size();nak[cur]++ ){
		edge z = v[cur][ nak[cur] ];
		
		if( !( nivo[z.kam] == nivo[cur] + 1 && z.kap > z.flo ) )continue;
		
		int ret=dfs( z.kam , min( flo , z.kap - z.flo ) );
		
		if(ret>0){
			
			v[cur][nak[cur]].flo+=ret;
			v[ z.kam ][ z.rev ].flo-=ret;
			
			return ret;
		}
		
	}
	
	return 0;
}
 
int main(){
 
    scanf("%d%d",&n,&m);
    
    for(;i<m;i++){
    	scanf("%d%d%d",&a,&b,&c);
    	if(a==b)continue;
    	v[a].push_back( edge( b , c , 0 , v[b].size() ) );
    	v[b].push_back( edge( a , c , 0 , v[a].size()-1 ) );
    }
    
    while(1){
    	while(!q.empty())q.pop();
    	memset( nivo , 0 , sizeof nivo ) , memset( nak , 0 , sizeof nak );
    	nivo[1]=1;
    	cur=1;
    	q.push( 1 );
    	while(!q.empty()){
    		while( q.size() && cur == nivo[q.front()] ){
    			int z=q.front();
    			q.pop();
    			for(int g=0;g<v[z].size();g++)
					if( !nivo[ v[z][g].kam ] && v[z][g].kap - v[z][g].flo > 0 )nivo[ v[z][g].kam ]=cur+1,q.push( v[z][g].kam );
    		}
    		++cur;
    	}
    	
    	if(!nivo[n])break;
    	
    	ll ac;
    	int ok=0;
    	
    	while( ac=dfs( 1 , 1123456789 ) )reza+=ac,ok=1;
    	
    	if(!ok)break;
    }
    
    printf("%lld",reza);
    return 0;
}  
