#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

int get_min_vertex(int n) // �ּ� dist[v] ���� ���� ������ ��ȯ
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

	// MST �ʱ�ȭ
	MST.n = g->n;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				MST.weight[i][j] = 0;
			else
				MST.weight[i][j] = INF;
		}
	}

	// distance(�Ÿ�) �迭 �ʱ�ȭ
	for (u = 0; u < g->n; u++)
		distance[u] = INF; // ������ ���� ���Ѵ�� �ʱ�ȭ
	distance[s] = 0; // ���۳��� 0���� �ʱ�ȭ

	// MST �����
	int prev = s;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // MST�� �߰����� ���� ������ �� �ּ� dist[v] ���� ���� ������ ��ȯ
		selected[u] = TRUE;
		if (distance[u] == INF) return MST; // ����
		printf(" %c >", u + 'a');
		MST.weight[prev][u] = MST.weight[u][prev] = distance[u]; // �� �߰�
		prev = u; // �� �߰�

		// ���� ����(u)�� �������� distance ������Ʈ
		// distance�� MST�� ���ۺκп��� �� ���������� �Ÿ�
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