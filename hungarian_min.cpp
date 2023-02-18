#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int,int> pll;
#define x first
#define y second
 
int n,N1,N2;
 
 
ll cena[2002][2002];//cijena spajanja i j
 
ll A[2002], B[2002];//labele
 
int Akam[2002], Bkam[2002];
 
int match[2002][2002];//je li spojen i j
int postoji[2002][2002];//postoji li i j brid
 
int bioB[2002];
int mA[2002],mB[2002];//je li vrh matchan
int nazA[2002],nazB[2002];//nazad po vrhovima po spojenostima

bool okej( int j , int k ){
	return cena[j][k] == (A[j] + B[k]);//je li brid u El
}
 
 
void kraj(int novi){//vracanje po cik cak dodavanjem jednog novog vrha u spojene
	
	int x=nazB[novi];
	
	mA[x]=1, mB[novi]=1;
	match[x][novi]=1;
	
	Bkam[novi]=x;
	int help=nazA[x];
	nazA[x]=novi;
	
	
	while(help!=-1){
		
		match[x][help]=0;
		
		int y=nazB[help];
		int ze=nazA[y];
		match[y][help]=1;
		
		nazA[y]=help;
		Bkam[help]=y;
		
		help=ze;
		x=y;
	}
	mA[x]=1;
}
 
 
 
int augment(){//glavni motor madarskog
	
	memset(bioB,0,sizeof(bioB));
	queue<int> bfs;
	
	for(int i=0;i<N2;i++){
		
		if(mB[i]){
			nazA[Bkam[i]]=i;
			nazB[i]=Bkam[i];
		}
	}
	
	for(int i=0;i<N1;i++){
		if(!mA[i]){
			nazA[i]=-1;
			bfs.push(i);
		}
	}
	
	vector<int> desno(N2),desnobak(N2);
	fill(desno.begin(),desno.end(),5+1e9);
	
	while(1){//bfs
		
		int potjera=1, novi;
		ll d=5+1e9;
		
		while(!bfs.empty()){
			
			queue<int> pom;
			
			while(!bfs.empty()){
				
				int x=bfs.front();
				bfs.pop();
				
				for(int j=0;j<N2;j++){
					
					if(!okej(x,j)){//implicitno se zna da nemre bit bioB[i]
						
						if( desno[j] >  cena[x][j] -(A[x] + B[j]) ){//min<-->max
							desno[j] = cena[x][j] -(A[x] + B[j]);//min<-->max
							desnobak[j] = x;
						}
						
					}
					else if(okej(x,j) && !bioB[j]){
						
						bioB[j]=1;
						
						if( !mB[j] && potjera ){
							nazB[j]=x;
							novi=j;
							potjera=0;
						}
						else if( mB[j] ){
							nazB[j]=x;
							nazA[Bkam[j]]=j;
							pom.push( Bkam[j] );
						}
						
					}
					
				}
				
			}
			
			bfs=pom;
			
		}
		
		for(int i=0;i<N2;i++){
			if(!bioB[i]){
				d=min(d,(ll)desno[i]);
			}
		}
		
		if(!potjera){//ako je kraj
			
			kraj(novi);
			return 1;
		}
		else{
			for(int j=0;j<N1;j++){
				if( !mA[j]  ){
					A[j]+=d;//min<-->max
				}
				else if(bioB[nazA[j]]){
					A[j]+=d;//min<-->max
					B[nazA[j]]-=d;////min<-->max
				}
			}
			
			for(int j=0;j<N2;j++){
				
				desno[j]-=d;
				if(desno[j]==0 && !bioB[j]){
					
					if(!mB[j]){
						novi=j;
						nazB[j]=desnobak[j];
						
						kraj( j );
						return 1;
					}
					else{
						bioB[j]=1;
						nazB[j]=desnobak[j];
						bfs.push(Bkam[j]);
					}
				}
			}
		}
		
	}
	
	return 0;
}
 
void solve(){
	
	memset(mA,0,sizeof(mA));
	memset(mB,0,sizeof(mB));
	memset(A,0,sizeof(A));
	memset(B,0,sizeof(B));
	memset(match,0,sizeof(match));
//	memset(nazA,0,sizeof(nazA));
//	memset(nazB,0,sizeof(nazB));
//	memset(Bkam,0,sizeof(Bkam));
//	memset(Akam,0,sizeof(Akam));
	
	for(int i=0;i<N1;i++){//inicijalizacija labela
		A[i]=cena[i][0];
		for(int b=0;b<N2;b++){
			A[i]=min(A[i],cena[i][b]);
		}
	}
	
	for(int i=0;i<N1;i++){
		augment();
	}
	
	ll reza=0;
	for(int j=0;j<N1;j++){
		for(int k=0;k<N2;k++){
			if(  match[j][k]  ){//zbrajanje spojenih bridova, lagana rekonstrukcija rjesenja
				reza+=cena[j][k];
			}
		}
	}
	
	cout<<reza<<endl;
	
}
 
int main(){
	
	cin>>n;
	
	for(int i=0;i<n;i++){//unos, u idealnom slucaju
		for(int b=0;b<n;b++){
			cin>>cena[i][b];
		}
	}
	
	N1=N2=n;
	
	solve();
	
	return 0;
}

/*

3
20 25 20
15 10 35
20 15 25

*/
 
