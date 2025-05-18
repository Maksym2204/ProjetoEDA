#pragma once
/**
 * @file funcoes.h
 * @brief Declaração das funções e estrutura para manipulação de antenas.
 *
 * @author Maksym Yavorenko
 * @date March 2025
 */

#ifndef LISTHANDLER_H
#define LISTHANDLER_H
#define M 40

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#pragma region Struct
 /** Exercicio 1
  * @struct Node
  * @brief Estrutura que representa uma antena na matriz.
  */
typedef struct Node {
    int x, y;        /**< Coordenadas da antena */
    char type;       /**< Tipo da antena */
    double resonance;/**< Frequência de ressonância */
    struct Node* next; /**< Ponteiro para o próximo nó */
} Node;

// Structure to represent a node in the adjacency list
struct NodeAdj {
    int vertex;
    struct NodeAdj* next;
};



#pragma endregion

#pragma region Funcoes
/**
 * @brief Obtém a frequência de uma antena com base no seu tipo.
 * @param type Tipo da antena.
 * @return Frequência da antena.
 */
double get_frequence(char type);

/** Exercicio 3a)
 * @brief Insere uma antena na matriz.
 * @param root Ponteiro para a raiz da lista.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 * @param type Tipo da antena.
 */
void insert_antenna(Node** root, int x, int y, char type);

/** Exercicio 3b)
 * @brief Remove uma antena da matriz.
 * @param root Ponteiro para a raiz da lista.
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void delete_antenna(Node** root, int x, int y);

/**
 * @brief Liberta a memória alocada para a lista de antenas.
 * @param root Ponteiro para a raiz da lista.
 */
void deallocate(Node** root);

/**
 * @brief Remove antenas "nefastas" da matriz.
 * @param root Ponteiro para a raiz da lista.
 */
void remove_nefasto(Node** root);

/** Exercicio 3c)
 * @brief Deteta e adiciona antenas "nefastas" na matriz.
 * @param root Ponteiro para a raiz da lista.
 */
void detect_nefasto(Node** root);

/** Exercicio 2
 * @brief Lê uma matriz de um ficheiro de texto e preenche a lista de antenas.
 * @param filename Nome do ficheiro.
 * @param root Ponteiro para a raiz da lista.
 * @param rows Ponteiro para armazenar o número de linhas.
 * @param cols Ponteiro para armazenar o número de colunas.
 */
void read_matrix_from_file(const char* filename, Node** root, int* rows, int* cols);

/**
 * @brief Imprime a matriz no terminal.
 * @param root Ponteiro para a raiz da lista.
 * @param rows Número de linhas.
 * @param cols Número de colunas.
 */
void print_matrix(Node* root, int rows, int cols);

/** Exercicio 3d)
 * @brief Imprime as antenas existentes e suas coordenadas.
 * @param root Ponteiro para a raiz da lista.
 */
void print_antennas(Node* root);
#pragma endregion


#endif