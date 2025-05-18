/**
 * @file GraphHandler.c
 * @brief Implementação das funções para manipulação de grafos.
 *
 * @author Maksym Yavorenko
 * @date May 2025
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "GraphHandler.h"


#define _CRT_SECURE_NO_WARNINGS

#pragma region Calculos de distancia
/**
 * Funcao para calcular a distancia de Manhattan entre dois pontos.
 * 
 * \param x1 - coordenada x do primeiro ponto
 * \param y1 - coordenada y do primeiro ponto
 * \param x2 - coordenada x do segundo ponto
 * \param y2 - coordenada y do segundo ponto
 * \return 
 */
static int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

/**
 * Funcao para criar um novo vertice.
 * 
 * \param id - ID do vertice
 * \param row - linha do vertice
 * \param col - coluna do vertice
 * \param type - tipo do vertice ('A' ou '0')
 * \return 
 */
#pragma endregion

#pragma region Criacao de grafo

static Vertex* create_vertex(int id, int row, int col, char type) {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    vertex->id = id;
    vertex->row = row;
    vertex->col = col;
    vertex->type = type;
    vertex->next = NULL;
    return vertex;
}

/**
 * Funcao para criar uma nova aresta.
 * 
 * \param destId - ID do vertice de destino
 * \return 
 */
static Edge* create_edge(int destId) {
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    edge->destId = destId;
    edge->next = NULL;
    return edge;
}
/**
 * Funcao para ler um grafo de um ficheiro.
 * 
 * \param filename - nome do ficheiro
 * \param rows - ponteiro para o numero de linhas
 * \param cols - ponteiro para o numero de colunas
 * \return 
 */
Graph* read_graph_from_file(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir ficheiro: %s\n", filename);
        return NULL;
    }

    char line[100];
    int row = 0, colCount = 0;
    int id = 0;

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = 0;
    graph->vertices = NULL;
    graph->adjList = NULL;

    Vertex* tail = NULL;

    // First pass: build vertex list
    while (fgets(line, sizeof(line), file)) {
        int col;
        for (col = 0; line[col] != '\n' && line[col] != '\0'; col++) {
            if (line[col] != '.') {
                Vertex* newVertex = create_vertex(id++, row, col, line[col]);
                if (graph->vertices == NULL) {
                    graph->vertices = newVertex;
                    tail = newVertex;
                }
                else {
                    tail->next = newVertex;
                    tail = newVertex;
                }
                graph->numVertices++;
            }
        }
        if (col > colCount) colCount = col;
        row++;
    }
    fclose(file);

    *rows = row;
    *cols = colCount;

    // Allocate adjacency list
    graph->adjList = (Edge**)malloc(sizeof(Edge*) * graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++)
        graph->adjList[i] = NULL;

    // Second pass: build edges using Manhattan rule
    Vertex* source = graph->vertices;
    while (source != NULL) {
        Vertex* target = graph->vertices;
        while (target != NULL) {
            if (source != target && source->type == target->type) {
                int dist = manhattan_distance(source->row, source->col, target->row, target->col);
                if (dist <= 4) {    
                    Edge* newEdge = create_edge(target->id);
                    newEdge->next = graph->adjList[source->id];
                    graph->adjList[source->id] = newEdge;
                }
            }
            target = target->next;
        }
        source = source->next;
    }

    return graph;
}
/**
 * Funcao para imprimir o grafo.
 * 
 * \param graph - ponteiro para o grafo
 */
void print_graph(const Graph* graph) {
    Vertex* v = graph->vertices;
    while (v != NULL) {
        printf("Antenna %d [%c] at (%d, %d): ", v->id, v->type, v->row+1, v->col+1);
        Edge* e = graph->adjList[v->id];
        while (e != NULL) {
            printf("-> %d ", e->destId);
            e = e->next;
        }
        printf("\n");
        v = v->next;
    }
}

#pragma endregion

#pragma region Libertação de memoria

/**
 * Funcao para libertar a memoria do grafo.
 * 
 * \param graph
 */
void free_graph(Graph* graph) {
    if (!graph) return;

    // Free edges
    for (int i = 0; i < graph->numVertices; i++) {
        Edge* edge = graph->adjList[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph->adjList);

    // Free vertices
    Vertex* vertex = graph->vertices;
    while (vertex != NULL) {
        Vertex* temp = vertex;
        vertex = vertex->next;
        free(temp);
    }

    free(graph);
}

#pragma endregion

#pragma region Busca por Profundidade e Largura



/**
 * Funcao para realizar DFS a partir de um vertice.
 * 
 * \param graph - ponteiro para o grafo
 * \param id - ID do vertice
 * \param visited - array de visitados
 * \param skip_row - linha a ignorar
 * \param skip_col - coluna a ignorar
 */
void dfs_from(Graph* graph, int id, bool* visited, int skip_row, int skip_col) {
    if (visited[id]) return;
    visited[id] = true;

    Vertex* vertex = graph->vertices;
    while (vertex != NULL && vertex->id != id)
        vertex = vertex->next;

    if (!vertex) return;

    if (!(vertex->row == skip_row && vertex->col == skip_col)) {
        printf("Antenna at (%d, %d) of type %c\n", vertex->row + 1, vertex->col + 1, vertex->type);
    }

    Edge* edge = graph->adjList[id];
    while (edge) {
        if (!visited[edge->destId]) {
            dfs_from(graph, edge->destId, visited, skip_row, skip_col);
        }
        edge = edge->next;
    }
}

/**
 * Funcao para realizar DFS a partir de um vertice especifico.
 * 
 * \param graph - ponteiro para o grafo
 * \param start_row - linha de inicio 
 * \param start_col - coluna de inicio
 */
void dfs(Graph* graph, int start_row, int start_col) {
	start_col--; 
	start_row--; 
    Vertex* vertex = graph->vertices;
    while (vertex != NULL) {
        if (vertex->row == start_row && vertex->col == start_col)
            break;
        vertex = vertex->next;
    }

    if (!vertex) {
        printf("No antenna found at (%d, %d)\n", start_row+1 , start_col+1 );
        return;
    }

    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    printf("DFS from antenna at (%d, %d):\n", start_row+1, start_col+1);
    dfs_from(graph, vertex->id, visited, start_row, start_col);
    free(visited);
}


/**
 * Funcao para criar uma fila.
 * 
 * \param queue - ponteiro para a fila
 * \param id - ID do vertice
 */
void enqueue(Queue* queue, int id) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->id = id;
    newNode->next = NULL;

    if (!queue->rear) {
        queue->front = queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

/**
 * Funcao para remover um elemento da fila.
 *
 * \param queue - ponteiro para a fila
 * \return
 */
int dequeue(Queue* queue) {
    if (!queue->front) return -1;

    QueueNode* temp = queue->front;
    int id = temp->id;
    queue->front = queue->front->next;
    if (!queue->front) queue->rear = NULL;
    free(temp);
    return id;
}
/**
 * Funcao para verificar se a fila esta vazia.
 *
 * \param queue - ponteiro para a fila
 * \return
 */
bool is_empty(Queue* queue) {
    return queue->front == NULL;
}
/**
 * Funcao para realizar BFS a partir de um vertice.
 *
 * \param graph - ponteiro para o grafo
 * \param startId - ID do vertice
 * \param visited - array de visitados
 * \param skip_row - linha a ignorar
 * \param skip_col - coluna a ignorar
 */
void bfs_from(Graph* graph, int startId, bool* visited, int skip_row, int skip_col) {
    Queue queue = { NULL, NULL };
    enqueue(&queue, startId);
    visited[startId] = true;

    while (!is_empty(&queue)) {
        int currentId = dequeue(&queue);

        Vertex* vertex = graph->vertices;
        while (vertex && vertex->id != currentId)
            vertex = vertex->next;

        if (vertex && !(vertex->row == skip_row && vertex->col == skip_col)) {
            printf("Antenna at (%d, %d) of type %c\n", vertex->row+1, vertex->col+1, vertex->type);
        }

        Edge* edge = graph->adjList[currentId];
        while (edge) {
            if (!visited[edge->destId]) {
                visited[edge->destId] = true;
                enqueue(&queue, edge->destId);
            }
            edge = edge->next;
        }
    }
}

/**
 * Funcao para realizar BFS a partir de um vertice especifico.
 *
 * \param graph - ponteiro para o grafo
 * \param start_row - linha de inicio
 * \param start_col - coluna de inicio
 */
void bfs(Graph* graph, int start_row, int start_col) {
	start_col--;
	start_row--;
    Vertex* vertex = graph->vertices;
    while (vertex) {
        if (vertex->row == start_row && vertex->col == start_col)
            break;
        vertex = vertex->next;
    }

    if (!vertex) {
        printf("No antenna found at (%d, %d)\n", start_row+1 , start_col+1 );
        return;
    }

    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    printf("BFS from antenna at (%d, %d):\n", start_row+1 , start_col+1);
    bfs_from(graph, vertex->id, visited, start_row, start_col);
    free(visited);
}

#pragma endregion

#pragma region de Busca de Caminhos

/**
 * Funcao para encontrar o ID de um vertice com base nas suas coordenadas.
 *
 * \param graph - ponteiro para o grafo
 * \param row - linha do vertice
 * \param col - coluna do vertice
 * \return
 */
int find_vertex_id(Graph* graph, int row, int col) {
    Vertex* vertex = graph->vertices;
    while (vertex != NULL) {
        if (vertex->row == row && vertex->col == col) {
            return vertex->id;
        }
        vertex = vertex->next;
    }
    return -1; 
}

#pragma endregion

#pragma region Busca de Caminhos
/**
 * Funcao para encontrar todos os caminhos entre dois vertices.
 *
 * \param graph - ponteiro para o grafo
 * \param currentId - ID do vertice atual
 * \param endId - ID do vertice de destino
 * \param visited - array de visitados
 * \param path - array de caminhos
 * \param pathLen - comprimento do caminho
 */
void dfs_all_paths(Graph* graph, int currentId, int endId, bool* visited, int* path, int pathLen) {
    visited[currentId] = true;
    path[pathLen++] = currentId;

    if (currentId == endId) {
        // Print current path
        printf("Path: ");
        for (int i = 0; i < pathLen; i++) {
            Vertex* vertex = graph->vertices;
            while (vertex && vertex->id != path[i]) vertex = vertex->next;
            if (vertex) printf("(%d,%d)%s", vertex->row + 1, vertex->col + 1, i == pathLen - 1 ? "" : " -> ");
        }
        printf("\n");
    }
    else {
        Edge* edge = graph->adjList[currentId];
        while (edge) {
            if (!visited[edge->destId]) {
                dfs_all_paths(graph, edge->destId, endId, visited, path, pathLen);
            }
            edge = edge->next;
        }
    }

    visited[currentId] = false; // backtrack
}
/**
 * Funcao para encontrar todos os caminhos entre dois vertices.
 *
 * \param graph - ponteiro para o grafo
 * \param start_row - linha de inicio
 * \param start_col - coluna de inicio
 * \param end_row - linha de destino
 * \param end_col - coluna de destino
 */
void find_all_paths(Graph* graph, int start_row, int start_col, int end_row, int end_col) {
	start_col--;
	start_row--;
	end_col--;
	end_row--;
    int startId = find_vertex_id(graph, start_row, start_col);
    int endId = find_vertex_id(graph, end_row, end_col);

    if (startId == -1 || endId == -1) {
        printf("One or both antennas not found.\n");
        return;
    }

    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    int* path = (int*)malloc(graph->numVertices * sizeof(int));

    printf("All paths from (%d,%d) to (%d,%d):\n", start_row + 1, start_col + 1, end_row + 1, end_col + 1);
    dfs_all_paths(graph, startId, endId, visited, path, 0);

    free(visited);
    free(path);
}
/**
 * Funcao para encontrar interseccoes entre dois tipos de antenas.
 *
 * \param graph - ponteiro para o grafo
 * \param typeA - tipo da antena A
 * \param typeB - tipo da antena B
 * \param maxDistance - distancia maxima
 */

#pragma endregion

#pragma region Intersecoes

void find_intersections(Graph* graph, char typeA, char typeB, int maxDistance) {
    Vertex* source = graph->vertices;

    while (source != NULL) {
        if (source->type == typeA) {
            Vertex* target = graph->vertices;
            while (target != NULL) {
                if (target->type == typeB) {
                    int dist = abs(source->row - target->row) + abs(source->col - target->col);
                    if (dist <= maxDistance) {
                        printf("Intersection found:\n");
                        printf("  %c at (%d,%d)\n", typeA, source->row + 1, source->col + 1);
                        printf("  %c at (%d,%d)\n", typeB, target->row + 1, target->col + 1);
                        printf("  Distance: %d\n\n", dist);
                    }
                }
                target = target->next;
            }
        }
        source = source->next;
    }
}

#pragma endregion
