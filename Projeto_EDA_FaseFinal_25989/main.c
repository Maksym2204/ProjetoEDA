/**
 * @file main.c
 * @brief Programa principal para manipulação de antenas e grafos de uma matriz.
 *
 * @author Maksym Yavorenko
 * @date March 2025
 */

#include "ListHandler.h"
#include "GraphHandler.h"
#define _CRT_SECURE_NO_WARNINGS
 /**
  * @brief Função principal do programa.
  * @return Código de saída do programa.
  */
int main() {
    Node* root = NULL;
    int rows, cols;

    // Inserir antenas na matriz
    insert_antenna(&root, 5, 6, 'A');
    insert_antenna(&root, 5, 4, 'A');
    insert_antenna(&root, 5, 11, 'A');
    insert_antenna(&root, 7, 8, 'C');
    insert_antenna(&root, 9, 9, 'C');

    // Detetar antenas nefastas
    detect_nefasto(&root);
    print_matrix(root, 20, 20);

    // Remover e adicionar antenas
    delete_antenna(&root, 5, 11);
    insert_antenna(&root, 7, 9, 'C');
    detect_nefasto(&root);
    print_matrix(root, 20, 20);
    deallocate(&root);

    // Ler matriz de um ficheiro
    printf("\nMatriz do ficheiro de texto:\n");
    read_matrix_from_file("Mapa.txt", &root, &rows, &cols);
    detect_nefasto(&root);
    print_matrix(root, rows, cols);
    print_antennas(root);

    // Libertar memória
    deallocate(&root);

	// Ler matriz de um ficheiro (visual)
    printf("\nMatriz do ficheiro de texto:\n");
    read_matrix_from_file("Mapa.txt", &root, &rows, &cols);
    print_matrix(root, rows, cols);

	// Criar grafo a partir da matriz de texto
    Graph* graph = read_graph_from_file("Mapa.txt", &rows, &cols);
    print_graph(graph);

     printf("\n\n");
	// Realizar buscas
    dfs(graph, 2, 9); 
    printf("\n");
    bfs(graph, 2, 9); 
    printf("\n\n");
	// Encontrar caminhos e interseções
    find_all_paths(graph, 2, 9, 5, 5); 
    printf("\n");
    find_intersections(graph, 'A', '0', 4);

    // Libertar memória
    deallocate(&root);
	free_graph(graph);
    return 0;
}
