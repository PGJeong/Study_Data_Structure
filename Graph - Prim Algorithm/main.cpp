#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) // 최소 dist[v] 값을 갖는 정점을 반환
{
	int v, i;
	for (i = 0; i < n; i++)
		if (selected[i] == FALSE) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (selected[i] == FALSE && (distance[i] < distance[v])) v = i;
	return (v);
}

GraphType prim(GraphType* g, int s)
{
	int i, u, v;
	GraphType MST;

	// MST 초기화
	MST.n = g->n;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				MST.weight[i][j] = 0;
			else
				MST.weight[i][j] = INF;
		}
	}

	// distance(거리) 배열 초기화
	for (u = 0; u < g->n; u++)
		distance[u] = INF; // 나머지 노드는 무한대로 초기화
	distance[s] = 0; // 시작노드는 0으로 초기화

	// MST 만들기
	int prev = s;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // MST에 추가되지 않은 정점들 중 최소 dist[v] 값을 갖는 정점을 반환
		selected[u] = TRUE;
		if (distance[u] == INF) return MST; // 오류
		printf(" %c >", u + 'a');
		MST.weight[prev][u] = MST.weight[u][prev] = distance[u]; // ★ 추가
		prev = u; // ★ 추가

		// 현재 정점(u)의 인접정점 distance 업데이트
		// distance는 MST의 시작부분에서 각 정점까지의 거리
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (selected[v] == FALSE && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
				}
			}
		}
	}

	return MST;
}

void printGraph(GraphType* g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			if (g->weight[i][j] == INF)
				printf("INF\t");
			else
				printf("%d\t", g->weight[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	GraphType g = { 7,
	{{ 0, 29, INF, INF, INF, 10, INF },
	{ 29,  0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, INF },
	{ INF, INF, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ INF, 15, INF, 18, 25, INF, 0 } }
	};

	GraphType MST = prim(&g, 0);

	printf("\n\n[ Graph ]\n\n");
	printGraph(&g);

	printf("\n\n[ MST ]\n\n");
	printGraph(&MST);

	return 0;
}