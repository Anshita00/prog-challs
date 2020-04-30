#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <bitset>

using namespace std;

#define PB push_back
#define MP make_pair
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,l,h) for(int i=(l);i<=(h);++i)
#define DWN(i,h,l) for(int i=(h);i>=(l);--i)
#define CLR(vis,pos) memset(vis,pos,sizeof(vis))
#define PI acos(-1.0)
#define INF 0x3f3f3f3f
#define LINF 1000000000000000000LL
#define eps 1e-8

typedef long long ll;

const int mm=11111*4;
const int mn=888;

int n,m;
int node,s,t,edge,max_flow;

int ver[mm],flow[mm],nxt[mm];

int head[mn],work[mn],dis[mn],q[mn];

int vis[mn];

inline void init(int _node,int _s,int _t)
{
    node=_node, s=_s, t=_t;
    for(int i=0;i<node;++i)
        head[i]=-1;
    edge=max_flow=0;
}


inline void addedge(int u,int v,int c)
{
    ver[edge]=v,flow[edge]=c,nxt[edge]=head[u],head[u]=edge++;
    ver[edge]=u,flow[edge]=0,nxt[edge]=head[v],head[v]=edge++;
}


bool Dinic_bfs()
{
    int i,u,v,l,r=0;
    for(i=0;i<node;++i)  dis[i]=-1;
    dis[ q[r++]=s ] = 0;
    for(l=0;l<r;l++)
    {
       for(i=head[ u=q[l] ]; i>=0 ;i=nxt[i])
        if(flow[i] && dis[ v=ver[i] ]<0)
        {
            dis[ q[r++]=v ]=dis[u]+1;
            if(v==t) return 1;
        }
    }
    return 0;
}

int Dinic_dfs(int u,int exp)
{
    if(u==t) return exp;
    for(int &i=work[u],v,temp; i>=0 ;i=nxt[i])
    {
        if(flow[i] && dis[ v=ver[i] ]==dis[u]+1 && ( temp=Dinic_dfs(v,min(exp,flow[i])) )>0)
        {
           flow[i]-=temp;
           flow[i^1]+=temp;
           return temp;
        }
    }
    return 0;
}

int Dinic_flow()
{
    int res,i;
    while(Dinic_bfs())
    {
        for(i=0;i<node;++i) work[i]=head[i];
        while( ( res=Dinic_dfs(s,INF) ) )  max_flow+=res;
    }
    return  max_flow;
}


void dfs1(int u){
    vis[u]=1;
    for(int i=head[u]; ~i ; i=nxt[i]){
        if(!vis[ver[i]] && flow[i]){
            dfs1(ver[i]);
        }
    }
}

void dfs2(int u){
    vis[u]=1;
    for(int i=head[u]; ~i ; i=nxt[i]){
        if(!vis[ver[i]] && flow[i^1]){
            dfs2(ver[i]);
        }
    }
}

int main()
{
    int ss,tt;
    cin>>n>>m>>ss>>tt;
    ss--,tt--;
    init(n,ss,tt);
    int u,v,w;
    REP(i,m){
        scanf("%d%d%d",&u,&v,&w);
        u--,v--;
        addedge(u,v,w);
        addedge(v,u,w);
    }
    Dinic_flow();
    for (int i = 0; i < edge; i++) {
        printf("%d - Edge is from %d to %d with cap %d\n", i, ver[i^1], ver[i], flow[i]);
    }


    CLR(vis,0);
    dfs1(s);
    dfs2(t);
    int flag=0;
    REP(i,n){
        printf("%d %d\n", i, vis[i]);
        if(vis[i]==0){
            flag=1;
            break;
        }
    }

    if(flag==0) printf("UNIQUE\n");
    else     printf("AMBIGUOUS\n");

    return 0;
}