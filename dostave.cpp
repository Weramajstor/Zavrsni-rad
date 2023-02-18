#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <vector>
#include <ctime>
#include <queue>
#include <utility>
using namespace std;
typedef long long ll;
typedef pair<int,int> pll;
#define x first
#define y second
 
int n,N1,N2;
 
 
ll cena[2002][2002];
pll konzum[2000], ljudi[2][2000];
ll A[2002], B[2002];
 
int Akam[2002], Bkam[2002];
 
int match[2002][2002],postoji[2002][2002];
 
int bioB[2002];
int mA[2002],mB[2002];
int nazA[2002],nazB[2002];
int koj[2002][2002];

bool okej( int j , int k ){
	return cena[j][k] == (A[j] + B[k]);
}

int dist( const pll& p1 ,const pll& p2 ){
	return abs(p1.x-p2.x) + abs(p1.y-p2.y);
}
 
void kraj(int novi){
	
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
 
 
 
int augment(){
	
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
	
	while(1){
		
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
		
		if(!potjera){
			
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

void van(int i, int j){
	int g=koj[i][j];
	cout<<ljudi[0][i].x<<" "<<ljudi[0][i].y<<" || "
	<<konzum[g].x<<" "<<konzum[g].y<<" || "
	<<ljudi[1][j].x<<" "<<ljudi[1][j].y<<endl;
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
	
	for(int i=0;i<N1;i++){
		A[i]=cena[i][0];
		for(int b=0;b<N2;b++){
			A[i]=min(A[i],cena[i][b]);
		}
	}
	
	for(int i=0;i<N1;i++){
		augment();
	}
	
	double reza=0;
	for(int j=0;j<N1;j++){
		for(int k=0;k<N2;k++){
			if(  match[j][k]  ){
				van(j,k);
				reza+=cena[j][k];
			}
		}
	}
	
	cout<<reza<<endl;
	
}



int main(){
	
	srand(time(NULL));
	
	cin>>n;
//	cout<<21<<endl;
	for(int i=0;i<n;i++){
		cin>>konzum[i].x>>konzum[i].y;
//		cout<<konzum[i].x<<" "<<konzum[i].y<<endl;
	}
	
	N1=18;
	N2=20;
	
	int mod1=783;
	int mod2=586;
	int d=rand()%mod1;
	d=rand()%mod1;
	d=rand()%mod1;
	d=rand()%mod1;
	
	cout<<18<<endl;
	for(int i=0;i<N1;i++){
		ljudi[0][i].x=rand()%mod1;
		ljudi[0][i].y=rand()%mod2;
		cout<<ljudi[0][i].x<<" "<<ljudi[0][i].y<<endl;
	}
	cout<<20<<endl;
	for(int i=0;i<N2;i++){
		ljudi[1][i].x=rand()%mod1;
		ljudi[1][i].y=rand()%mod2;
		cout<<ljudi[1][i].x<<" "<<ljudi[1][i].y<<endl;
	}
	
	for(int i=0;i<N1;i++){
		for(int j=0;j<N2;j++){
			cena[i][j]=dist( ljudi[0][i] , konzum[0] ) +  dist( konzum[0] , ljudi[1][j] );
			koj[i][j]=0;
//			postoji[i][j]=1;
			for(int g=0;g<n;g++){
				int val=dist( ljudi[0][i] , konzum[g] ) +  dist( konzum[g] , ljudi[1][j] );
				
				if( cena[i][j] > val ){
					cena[i][j]=val;
					koj[i][j]=g;
				}
				
			}
		}
	}
	
	solve();
	
	return 0;
}

/*

3
20 25 20
15 10 35
20 15 25


polozaji konzuma:
21
55 145
123 139
194 119
208 144
301 144
371 191
391 162
442 179
521 141
586 163
503 306
618 250
766 269
777 405
697 418
459 387
338 430
228 382
179 440
91 475
23 395


mobovi
642 473
436 317
706 581
488 575
596 526
447 285
194 213
526 258
192 159
140 240
550 44
642 213
191 195
693 379
715 2
255 91
432 297
230 377
=========
===========
=========
688 474
610 320
613 173
297 141
281 253
359 121
70 281
134 264
141 443
415 454
481 135
61 83
555 149
565 305
643 32
698 562
18 129
575 263
449 564
687 92
=========
===========
=========
642 473 || 697 418 || 688 474
436 317 || 503 306 || 565 305
706 581 || 697 418 || 698 562
488 575 || 459 387 || 415 454
596 526 || 697 418 || 610 320
447 285 || 442 179 || 481 135
194 213 || 208 144 || 134 264
526 258 || 586 163 || 643 32
192 159 || 123 139 || 61 83
140 240 || 55 145 || 18 129
550 44 || 521 141 || 555 149
642 213 || 586 163 || 687 92
191 195 || 208 144 || 281 253
693 379 || 618 250 || 575 263
715 2 || 586 163 || 613 173
255 91 || 301 144 || 297 141
432 297 || 371 191 || 359 121
230 377 || 179 440 || 141 443
2573.3



*/
 
