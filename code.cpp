#include <cstdio>
#include <vector>

#define INFINITY -1

using namespace std;

/*
 * Floyd Warshall all-pair shortest distance algorithm
 * Runtime complexity: O(n^3)
 */
void all_pair_shortest_path(int **weight_matrix, int ** shortest_weight_matrix, int size) {
	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			shortest_weight_matrix[i][j] = INFINITY;
		}
	}
	for(int i=0; i<size; i++) {
		shortest_weight_matrix[i][i]=0;
	}
	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			shortest_weight_matrix[i][j] = weight_matrix[i][j];
		}
	}
	for(int k=0; k<size; k++) {
		for(int i=0; i<size; i++) {
			for(int j=0; j<size; j++) {
				if (shortest_weight_matrix[i][j] > shortest_weight_matrix[i][k] + shortest_weight_matrix[k][j]) {
					shortest_weight_matrix[i][j] = shortest_weight_matrix[i][k] + shortest_weight_matrix[k][j];
				}
			}
		}
	}
}

int main() {
	int nodes, edges, channels;
	scanf("%d%d%d", &nodes, &edges, &channels);
	int graph_adjacency_matrix[nodes][nodes], graph_weight_matrix[nodes][nodes];
	for(int i=0; i<edges, i++) {
		int from, to, value;
		scanf("%d%d%d", &from, &to, &value);
		graph_adjacency_matrix[from][to] = 1;
		graph_adjacency_matrix[to][from] = 1;
		graph_weight_matrix[to][from] = value;
		graph_weight_matrix[from][to] = value;
	}

	// Compute shortest paths
	int shortest_weight_matrix[nodes][nodes];
	int shortest_path_matrix[nodes][nodes];
	all_pair_shortest_path(&graph_adjacency_matrix, shortest_path_matrix, nodes);
	all_pair_shortest_path(&graph_weight_matrix, shortest_weight_matrix, nodes);

	//
	return 0;
}