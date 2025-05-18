/**
 * @file GraphHandler.h
 * @brief Declara��o das estruturas e fun��es para manipula��o de grafos de antenas.
 *
 * @author Maksym Yavorenko
 * @date May 2025
 */

#ifndef GRAPH_HANDLER_H
#define GRAPH_HANDLER_H

#include <stdbool.h>

#pragma region Structs



 /**
  * @struct Vertex
  * @brief Estrutura que representa uma antena como v�rtice no grafo.
  */
typedef struct Vertex {
    int id;               /**< Identificador �nico da antena */
    int row, col;         /**< Coordenadas da antena na matriz */
    char type;            /**< Tipo da antena (ex: 'A', '0') */
    struct Vertex* next;  /**< Ponteiro para o pr�ximo v�rtice (lista ligada) */
} Vertex;

/**
 * @struct Edge
 * @brief Estrutura que representa uma aresta de liga��o entre duas antenas.
 */
typedef struct Edge {
    int destId;           /**< ID do v�rtice de destino */
    struct Edge* next;    /**< Pr�xima aresta na lista de adjac�ncia */
} Edge;

/**
 * @struct Graph
 * @brief Estrutura que representa o grafo completo de antenas.
 */
typedef struct Graph {
    int numVertices;      /**< N�mero total de v�rtices no grafo */
    Vertex* vertices;     /**< Lista ligada de v�rtices (antenas) */
    Edge** adjList;       /**< Vetor de listas de adjac�ncia para cada v�rtice */
} Graph;

/**
 * @struct QueueNode
 * @brief Estrutura que representa um n� na fila (para BFS).
 */
typedef struct QueueNode {
    int id;                   /**< ID do v�rtice armazenado na fila */
    struct QueueNode* next;   /**< Pr�ximo n� na fila */
} QueueNode;

/**
 * @struct Queue
 * @brief Estrutura que representa uma fila para buscas em largura.
 */
typedef struct {
    QueueNode* front;     /**< In�cio da fila */
    QueueNode* rear;      /**< Final da fila */
} Queue;

#pragma endregion

#pragma region Fun��es
/**Exercicio 2
 * @brief L� um ficheiro de texto e cria o grafo correspondente com antenas e liga��es.
 */
Graph* read_graph_from_file(const char* filename, int* rows, int* cols);

/**
 * @brief Imprime o grafo na consola (para depura��o).
 */
void print_graph(const Graph* graph);

/**
 * @brief Liberta toda a mem�ria alocada para o grafo.
 */
void free_graph(Graph* graph);

/**Exercicio 3a)
 * @brief Executa uma busca em profundidade (DFS) a partir de uma antena.
 */
void dfs(Graph* graph, int start_row, int start_col);

/**Exercicio 3b)
 * @brief Executa uma busca em largura (BFS) a partir de uma antena.
 */
void bfs(Graph* graph, int start_row, int start_col);

/**Exercicio 3c)
 * @brief Encontra e imprime todos os caminhos poss�veis entre duas antenas.
 */
void find_all_paths(Graph* graph, int start_row, int start_col, int end_row, int end_col);

/**Exercicio 3d)
 * @brief Lista todos os pares de antenas de tipos distintos que est�o dentro de uma dist�ncia limite.
 */
void find_intersections(Graph* graph, char typeA, char typeB, int maxDistance);

#pragma endregion

#endif
