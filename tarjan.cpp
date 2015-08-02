#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <limits>
#include <stack>
using namespace std;
 
int vertex, edge;
int *d, *low, visited;
bool *inL, sccFound;
int NIL = numeric_limits<int>::min();
int maxGroup, maxGroupAux, numGroupsMax, shareOutside, numShareInsideGroup;
 
vector<int> *G;
stack<int> L;
/**/
bool shareOutsideGroup(){
    unsigned i;
    int u, n;
     
    for(u=1; u<=vertex; u++) {
        if(inL[u]){
            for(i=0;i<G[u].size();i++){
                n=G[u][i];
                if(!inL[n]){
                    return true;
                }
            }
        }
    }
    return false;
}
         
void tarjanVisit(int u) {
    int v=NIL;
    unsigned i;
     
    d[u]=visited;
    low[u]=visited;
    visited=visited+1;
    L.push(u);
    inL[u]=true;
 
    for(i=0;i<G[u].size();i++){
        v=G[u][i];
        if(d[v] == NIL){
            tarjanVisit(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inL[v])
            low[u]=min(low[u],d[v]);        
    }
     
     
     
    if(low[u]==d[u]){ 
        maxGroupAux=0;
        shareOutside=0;
        if(shareOutsideGroup())
            shareOutside++;
        while(v!=u){            
            maxGroupAux++;
            v=L.top();
            L.pop();            
            inL[v]=false;               
            sccFound=true;      
        }
        L.empty();
         
         
    }
    if(sccFound){
        if(shareOutside==0)
            numShareInsideGroup++;
        numGroupsMax++;
        maxGroup = max(maxGroup,maxGroupAux);
        sccFound=false;
    }
     
         
}
 
void sccTarjan() {
    int u;
    visited=0;
         
    for(u=1; u<=vertex; u++) {
        d[u] = NIL;
    }
    for(u=1; u<=vertex; u++) {
        if(d[u] == NIL) {
            tarjanVisit(u);
        }
    }
     
    cout << numGroupsMax;
    cout << endl;
    cout << maxGroup;
    cout << endl;
    cout << numShareInsideGroup;
    cout << endl;
     
}
 
int main(void){
    int i;
    int u;
    int v;
     
    cin >> vertex >> edge;
    G = new vector<int>[edge];
    inL = new bool[edge];
    d = new int[edge];
    low = new int[edge];
    for(i=0; i<edge; i++) {
        cin >> u >> v;
        G[u].push_back(v);
    }
     
    sccTarjan();
     
    return 0;
}
