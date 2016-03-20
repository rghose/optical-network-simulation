#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100

#define INFINITY 99999

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int size, int dist[], bool sptSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;

   for (int v = 0; v < size; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}


void djikstra(int n, int G[MAX_NODES][MAX_NODES],int *distance,int startnode)
{
	int cost[MAX_NODES][MAX_NODES],pred[MAX_NODES];

	int visited[MAX_NODES],count,mindistance,nextnode,i,j;

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0) cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];


	for(i=0;i<n;i++) {
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n-1) {
		mindistance=INFINITY;
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i]) {
				mindistance=distance[i];
				nextnode=i;
			}

		visited[nextnode]=1;
		for(i=0;i<n;i++)
			if(!visited[i])
				if(mindistance+cost[nextnode][i]<distance[i]) {
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}

		count++;
	}

	//print the path and distance of each node
	for(i=0;i<n;i++) if(i!=startnode) printf("Distance of node %d from node %d = %d\n",i,startnode,distance[i]);
}

/*
 * Compute single source shortest path using Djiktra's algorithm
 * from an adjacency matrix
 */
void _djikstra(int size, int graph[size][size], int *distance, int src) {

     int dist[size];     // The output array.  dist[i] will hold the shortest
                      // distance from src to i

     bool sptSet[size]; // sptSet[i] will true if vertex i is included in shortest
                     // path tree or shortest distance from src to i is finalized

     // Initialize all distances as INFINITE and stpSet[] as false
     for (int i = 0; i < size; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

     // Distance of source vertex from itself is always 0
     dist[src] = 0;

     // Find shortest path for all vertices
     for (int count = 0; count < size-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to src in first iteration.
       int u = minDistance(size, dist, sptSet);

       // Mark the picked vertex as processed
       sptSet[u] = true;

       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < size; v++) {
         // Update dist[v] only if is not in sptSet, there is an edge from
         // u to v, and total weight of path from src to  v through u is
         // smaller than current value of dist[v]
       	printf("Trying for %d,%d is %s. Current distance is %d. Probable distance is %d\n", u,v, graph[u][v]==0?"not adjacent":"adjacent", dist[v],dist[u]+graph[u][v] );
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u]+graph[u][v] < dist[v])
            dist[v] = dist[u] + graph[u][v];
       }
     }

     printf("----------------------\n");
     for( int i=0; i<size; i++) {
    	 distance[i] = dist[i];
    	 printf("[%d] ", dist[i]);
     }
     printf("\n----------------------\n");
 }


int main() {
	int nodes, edges, channels, i;
	int graph_adjacency_matrix[MAX_NODES][MAX_NODES], graph_weight_matrix[MAX_NODES][MAX_NODES];

	for(int i=0; i<MAX_NODES;i++) for(int j=0; j<MAX_NODES; j++ ) {
		graph_adjacency_matrix[i][j]=0;
		graph_weight_matrix[i][j]=0;
	}

	FILE * fp = fopen("TESTCASE","r");
	if (fp == NULL) {
		printf("Could not find testcase file");
		return -1;
	}
	fscanf(fp, "%d%d%d", &nodes, &edges, &channels);

	for(i=0; i<edges; i++) {
		int from, to, value;
		fscanf(fp,"%d%d%d", &from, &to, &value);
		graph_adjacency_matrix[from][to] = 1;
		graph_adjacency_matrix[to][from] = 1;
		graph_weight_matrix[to][from] = value;
		graph_weight_matrix[from][to] = value;
	}
	fclose(fp);

	// Compute shortest paths
	int shortest_weight_matrix[nodes][nodes];
	int shortest_path_matrix[nodes][nodes];

	for(i=0; i<nodes; i++) {
		djikstra(nodes, graph_adjacency_matrix, (int *)(shortest_path_matrix+i), i);
		djikstra(nodes, graph_weight_matrix,(int *)(shortest_weight_matrix+i), i);
	}

	return 0;
}
