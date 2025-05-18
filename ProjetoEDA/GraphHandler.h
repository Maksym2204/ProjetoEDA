/**
 * @file GraphHandler.h
 * @brief Declaração das estruturas e funções para manipulação de grafos de antenas.
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
  * @brief Estrutura que representa uma antena como vértice no grafo.
  */
typedef struct Vertex {
    int id;               /**< Identificador único da antena */
    int row, col;         /**< Coordenadas da antena na matriz */
    char type;            /**< Tipo da antena (ex: 'A', '0') */
    struct Vertex* next;  /**< Ponteiro para o próximo vértice (lista ligada) */
} Vertex;

/**
 * @struct Edge
 * @brief Estrutura que representa uma aresta de ligação entre duas antenas.
 */
typedef struct Edge {
    int destId;           /**< ID do vértice de destino */
    struct Edge* next;    /**< Próxima aresta na lista de adjacência */
} Edge;

/**
 * @struct Graph
 * @brief Estrutura que representa o grafo completo de antenas.
 */
typedef struct Graph {
    int numVertices;      /**< Número total de vértices no grafo */
    Vertex* vertices;     /**< Lista ligada de vértices (antenas) */
    Edge** adjList;       /**< Vetor de listas de adjacência para cada vértice */
} Graph;

/**
 * @struct QueueNode
 * @brief Estrutura que representa um nó na fila (para BFS).
 */
typedef struct QueueNode {
    int id;                   /**< ID do vértice armazenado na fila */
    struct QueueNode* next;   /**< Próximo nó na fila */
} QueueNode;

/**
 * @struct Queue
 * @brief Estrutura que representa uma fila para buscas em largura.
 */
typedef struct {
    QueueNode* front;     /**< Início da fila */
    QueueNode* rear;      /**< Final da fila */
} Queue;

#pragma endregion

#pragma region Funções
/**Exercicio 2
 * @brief Lê um ficheiro de texto e cria o grafo correspondente com antenas e ligações.
 */
Graph* read_graph_from_file(const char* filename, int* rows, int* cols);

/**
 * @brief Imprime o grafo na consola (para depuração).
 */
void print_graph(const Graph* graph);

/**
 * @brief Liberta toda a memória alocada para o grafo.
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
 * @brief Encontra e imprime todos os caminhos possíveis entre duas antenas.
 */
void find_all_paths(Graph* graph, int start_row, int start_col, int end_row, int end_col);

/**Exercicio 3d)
 * @brief Lista todos os pares de antenas de tipos distintos que estão dentro de uma distância limite.
 */
void find_intersections(Graph* graph, char typeA, char typeB, int maxDistance);

#pragma endregion

#endif
