#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int travelproblem(int graph[][15],int s,int V, int M )
{
	// store all vertex apart from source vertex
	vector<int> vertex;
	for (int i = 0; i < V; i++)
	{
		if (i != s)
		{
			vertex.push_back(i);
			// Store minimum weight - Halminton circle
		}
	}
	int count = 0;
	do
	{
		// Store current path
		int current_pathweight = 0;
		// Compute the current path weight
		int k =s;
		for (int i = 0; i < vertex.size(); i++)
		{
			current_pathweight += graph[k][vertex[i]];
			k= vertex[i];
		}
		current_pathweight += graph[k][s];

		// Upgrace minimum
		if (current_pathweight <= M)
		{
			count ++;
		}
	}
	while(
		next_permutation(vertex.begin(),vertex.end()));
		return count;
}


int main(){
	int N;
	int M;
	cin >> N >> M;
	int distance[15][15];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; i < N; j++)
		{
			cin >> distance[i][j];
		}
	}
	cout << travelproblem(distance,0,N,M) << endl;
	return 0;

}