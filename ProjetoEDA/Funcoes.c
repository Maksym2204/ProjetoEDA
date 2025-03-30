/**
 * @file funcoes.c
 * @brief Implementação das funções para manipulação de antenas.
 *
 * @author Maksym Yavorenko
 * @date March 2025
 */

#include "Funcoes.h"

#pragma region Libertação de memmoria
/**
 * @brief Liberta a memória alocada para a lista de antenas.
 */
void deallocate(Node** root) {
    Node* curr = *root;
    while (curr != NULL) {
        Node* aux = curr;
        curr = curr->next;
        free(aux);
    }
    *root = NULL;
}
#pragma endregion

#pragma region Manipulação Antenas
/**
 * @brief Insere uma antena na matriz.
 */
void insert_antenna(Node** root, int x, int y, char type) {
    Node* new_node = malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->x = x;
    new_node->y = y;
    new_node->type = type;
    new_node->resonance = get_frequence(type);

    if (*root == NULL) {
        *root = new_node;
        return;
    }

    Node* curr = *root;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_node;
}

/**
 * @brief Remove uma antena da matriz.
 */
void delete_antenna(Node** root, int x, int y) {
    Node* curr = *root;
    Node* aux = NULL;

    while (curr != NULL && (curr->x != x || curr->y != y)) {
        aux = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Antena não encontrada em (%d, %d).\n", x, y);
        return;
    }

    if (aux == NULL) {
        *root = curr->next;
    }
    else {
        aux->next = curr->next;
    }

    free(curr);
    printf("Antena removida de (%d, %d).\n", x, y);
}

/**
 * Imprime as antenas e as suas coordenadas existentes.
 *
 * \param root Ponteiro para a lista ligada de antenas.
 */
void print_antennas(Node* root) {
    printf("\nAntenas existentes:\n");
    for (Node* curr = root; curr != NULL; curr = curr->next) {
        printf("Antena %c em (%d, %d)\n", curr->type, curr->x + 1, curr->y + 1);
    }
}


/**
 * @brief Obtém a frequência de uma antena com base no seu tipo.
 */
double get_frequence(char type) {
    switch (type) {
    default: return '#';
    }
}
#pragma endregion


#pragma region Manipulação Nefastos
/**
 * @brief Remove antenas "nefastas" da matriz.
 */
void remove_nefasto(Node** root) {
    Node* curr = *root;
    Node* prev = NULL;
    while (curr != NULL) {
        if (curr->type == '#') {
            Node* to_delete = curr;
            curr = curr->next;
            if (prev == NULL) *root = curr;
            else prev->next = curr;
            free(to_delete);
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

/**
 * @brief Deteta e adiciona antenas "nefastas" na matriz.
 */
void detect_nefasto(Node** root) {
    Node* curr = *root;
    Node* temp_list = NULL;
    remove_nefasto(root);

    for (Node* curr = *root; curr != NULL; curr = curr->next) {
        for (Node* curr2 = *root; curr2 != NULL; curr2 = curr2->next) {
            if (curr != curr2 && curr->type == curr2->type && curr->type != '#') {
                int dx = curr->x - curr2->x;
                int dy = curr->y - curr2->y;
                dx = curr->x + dx;
                dy = curr->y + dy;

                Node* check = *root;
                bool exist = false;
                while (check != NULL) {
                    if (check->x == dx && check->y == dy) {
                        exist = true;
                        break;
                    }
                    check = check->next;
                }

                if (!exist) insert_antenna(&temp_list, dx, dy, curr->type);
            }
        }
    }

    if (temp_list != NULL) {
        Node* temp_curr = temp_list;
        while (temp_curr != NULL) {
            insert_antenna(root, temp_curr->x, temp_curr->y, get_frequence(temp_curr->type));
            temp_curr = temp_curr->next;
        }
    }
}
#pragma endregion

#pragma region Manipulação Matrizes
/**
 * @brief Lê uma matriz de um ficheiro de texto e preenche a lista de antenas.
 */
void read_matrix_from_file(const char* filename, Node** root, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir ficheiro: %s\n", filename);
        return;
    }

    char line[1024];
    *rows = 0;
    *cols = 0;

    while (fgets(line, sizeof(line), file)) {
        int x = 0;
        for (x = 0; line[x] != '\n' && line[x] != '\0'; x++) {
            if (line[x] != '.') insert_antenna(root, *rows, x, line[x]);
        }
        if (x > *cols) *cols = x;
        (*rows)++;
    }
    fclose(file);
}

/**
 * @brief Imprime a matriz no terminal.
 */
void print_matrix(Node* root, int rows, int cols) {
    char** grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) grid[i] = (char*)malloc(cols * sizeof(char));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = '.';

    for (Node* curr = root; curr != NULL; curr = curr->next)
        if (curr->x >= 0 && curr->x < rows && curr->y >= 0 && curr->y < cols)
            grid[curr->x][curr->y] = curr->type;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) printf("%c ", grid[i][j]);
        printf("\n");
    }

    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);
}
#pragma endregion
