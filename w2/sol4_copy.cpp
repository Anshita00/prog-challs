#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
typedef long long int ll;
ll n, m, q, x, y, finalans[600000], comp[600000], done[600000], rank1[600000], ans = 0, pop[600000], counter1 = 0, city_pop[600000], edge[600000], type[600000], cit[600000], change[600000], rem[600000];
pair<int, int> roads[600000]; 
char c;
int root(int x)
{
	if (comp[x] == x)
		return x;
	int res = root(comp[x]);
	comp[x] = res;
	return res;
}

void join(int a, int b)
{
	int a1 = root(a), b1 = root(b);
	if (a1 == b1)
		return;
	if (rank1[a1] >= rank1[b1])
	{
		comp[b1] = a1;
		rank1[a1] = max(rank1[a1], 1+rank1[b1]);
		pop[a1] += pop[b1];
		ans = max(ans, pop[a1]);
	}
	else
	{
		comp[a1] = b1;
		rank1[b1] = max(rank1[b1], 1+rank1[a1]);
		pop[b1] += pop[a1];
		ans = max(ans, pop[b1]);
	}
}

int main()
{	
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>m>>q;
	for (int i = 1; i <= n; i++)
		cin>>city_pop[i];
	for (int i = 1; i <= m; i++)
	{
		cin>>x>>y;
		roads[i].first = x;
		roads[i].second = y;
	}
	for (int i = 1; i <= q; i++)
	{
		cin>>c;
		if (c == 'D')
		{
			cin>>x;
			edge[x] = 1;
			rem[i] = x;		
			type[i] = 1;
		}
		else
		{
			cin>>x>>y;
			cit[i] = x;
			change[i] = city_pop[x];
			city_pop[x] = y;
			type[i] = 2;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		comp[i] = i;
		pop[i] = city_pop[i];
		rank1[i] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		if (edge[i] == 0)
		{
			join(roads[i].first, roads[i].second);
		}
	}

	priority_queue< pair<ll, ll> > pq;
	for (int i = 1; i <= n; i++)
	{
		int a1 = root(i);
		if (!done[a1])
		{
			done[a1] = 1;
			pq.push(make_pair(pop[a1], a1));
		}
	}

	for (int i = q; i >= 1; i--)
	{
		if (type[i] == 1)
		{
			pair<ll, ll> temp = pq.top();
			int a2 = root(temp.second);
			while (a2 != temp.second or temp.first != pop[temp.second])
			{
				pq.pop();
				temp = pq.top();
				a2 = root(temp.second);
			}
			finalans[i] = temp.first;
			join(roads[rem[i]].first, roads[rem[i]].second);
			int a1 = root(roads[rem[i]].first);
			pq.push(make_pair(pop[a1], a1));
		}
		else
		{
			pair<ll, ll> temp = pq.top();
			int a2 = root(temp.second);
			while (a2 != temp.second or temp.first != pop[temp.second])
			{
				pq.pop();
				temp = pq.top();
				a2 = root(temp.second);
			}
			finalans[i] = temp.first;
			int res = root(cit[i]);
			ll diff = change[i]-city_pop[cit[i]];
			pop[res] += diff;
			city_pop[cit[i]] = change[i];
			pq.push(make_pair(pop[res], res));
		}
	}

	for (int i = 1; i <= q; i++)
		cout<<finalans[i]<<"\n";
}