/**
 * @file main.c
 * @brief Programa principal para manipulação de antenas numa matriz.
 *
 * @author Maksym Yavorenko
 * @date March 2025
 */

#include "Funcoes.h"

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

    // Detetar e remover antenas nefastas
    detect_nefasto(&root);
    print_matrix(root, 20, 20);

    // Remover e adicionar antenas
    delete_antenna(&root, 5, 11);
    insert_antenna(&root, 7, 9, 'C');
    detect_nefasto(&root);
    print_matrix(root, 20, 20);
    deallocate(&root);

    // Ler matriz de um ficheiro
    printf("Matriz do ficheiro de texto:\n");
    read_matrix_from_file("Mapa.txt", &root, &rows, &cols);
    detect_nefasto(&root);
    print_matrix(root, 14, 13);
    print_antennas(root);

    // Remover antena e atualizar matriz
    delete_antenna(&root, 9, 9);
    detect_nefasto(&root);
    print_matrix(root, rows, cols);



    // Libertar memória
    deallocate(&root);
    return 0;
}
