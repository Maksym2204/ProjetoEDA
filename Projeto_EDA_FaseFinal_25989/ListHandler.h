#pragma once
/**
 * @file funcoes.h
 * @brief Declara��o das fun��es e estrutura para manipula��o de antenas.
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
    double resonance;/**< Frequ�ncia de resson�ncia */
    struct Node* next; /**< Ponteiro para o pr�ximo n� */
} Node;

// Structure to represent a node in the adjacency list
struct NodeAdj {
    int vertex;
    struct NodeAdj* next;
};



#pragma endregion

#pragma region Funcoes
/**
 * @brief Obt�m a frequ�ncia de uma antena com base no seu tipo.
 * @param type Tipo da antena.
 * @return Frequ�ncia da antena.
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
 * @brief Liberta a mem�ria alocada para a lista de antenas.
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
 * @brief L� uma matriz de um ficheiro de texto e preenche a lista de antenas.
 * @param filename Nome do ficheiro.
 * @param root Ponteiro para a raiz da lista.
 * @param rows Ponteiro para armazenar o n�mero de linhas.
 * @param cols Ponteiro para armazenar o n�mero de colunas.
 */
void read_matrix_from_file(const char* filename, Node** root, int* rows, int* cols);

/**
 * @brief Imprime a matriz no terminal.
 * @param root Ponteiro para a raiz da lista.
 * @param rows N�mero de linhas.
 * @param cols N�mero de colunas.
 */
void print_matrix(Node* root, int rows, int cols);

/** Exercicio 3d)
 * @brief Imprime as antenas existentes e suas coordenadas.
 * @param root Ponteiro para a raiz da lista.
 */
void print_antennas(Node* root);
#pragma endregion


#endif