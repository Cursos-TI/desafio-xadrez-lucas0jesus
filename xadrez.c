#include <stdio.h>
#include <string.h>

#define TAM_TABULEIRO 8

// Função para inicializar o tabuleiro com pontos (casas vazias)
void inicializarTabuleiro(char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = '.'; // '.' representa casa vazia
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char peca) {
    printf("\nTabuleiro (posicao da peca %c em (%d,%d)):\n", peca, linha, coluna);
    printf("  0 1 2 3 4 5 6 7\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (i == linha && j == coluna) {
                printf("%c ", peca); // Mostra a peça na posição atual
            } else {
                printf("%c ", tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para mover o Peão (1 casa para cima, simplificado para brancas)
int moverPeao(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    *nova_linha = linha;
    *nova_coluna = coluna;
    printf("Movimento do Peao (%d casa para %s):\n", casas, direcao);
    
    if (strcmp(direcao, "cima") != 0 || casas != 1) {
        return 0; // Peão só move 1 casa para cima
    }
    
    for (int i = 1; i <= casas; i++) {
        (*nova_linha)--;
        if (*nova_linha < 0) return 0; // Fora do tabuleiro
        printf("Cima\n");
    }
    
    tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
    tabuleiro[*nova_linha][*nova_coluna] = 'P'; // Marca a nova posição
    return 1;
}

// Função para mover o Cavalo (movimento em "L")
int moverCavalo(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    if (casas != 1) return 0; // Cavalo move apenas 1 casa por vez
    printf("Movimento do Cavalo (1 casa em %s):\n", direcao);
    
    *nova_linha = linha;
    *nova_coluna = coluna;
    char *direcoes[] = {"2cima-1direita", "2cima-1esquerda", "2baixo-1direita", "2baixo-1esquerda",
                        "1cima-2direita", "1cima-2esquerda", "1baixo-2direita", "1baixo-2esquerda"};
    int deslocamentos[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    
    for (int i = 0; i < 8; i++) {
        if (strcmp(direcao, direcoes[i]) == 0) {
            *nova_linha += deslocamentos[i][0];
            *nova_coluna += deslocamentos[i][1];
            if (*nova_linha >= 0 && *nova_linha < TAM_TABULEIRO && *nova_coluna >= 0 && *nova_coluna < TAM_TABULEIRO) {
                printf("%s\n", direcao);
                tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
                tabuleiro[*nova_linha][*nova_coluna] = 'C'; // Marca a nova posição
                return 1;
            }
            return 0; // Fora do tabuleiro
        }
    }
    return 0; // Direção inválida
}

// Função para mover o Bispo (diagonais)
int moverBispo(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    *nova_linha = linha;
    *nova_coluna = coluna;
    int contador = 1;
    printf("Movimento do Bispo (%d casas na diagonal %s):\n", casas, direcao);
    
    while (contador <= casas) {
        if (strcmp(direcao, "cima-direita") == 0) {
            (*nova_linha)--;
            (*nova_coluna)++;
            printf("Cima Direita\n");
        } else if (strcmp(direcao, "cima-esquerda") == 0) {
            (*nova_linha)--;
            (*nova_coluna)--;
            printf("Cima Esquerda\n");
        } else if (strcmp(direcao, "baixo-direita") == 0) {
            (*nova_linha)++;
            (*nova_coluna)++;
            printf("Baixo Direita\n");
        } else if (strcmp(direcao, "baixo-esquerda") == 0) {
            (*nova_linha)++;
            (*nova_coluna)--;
            printf("Baixo Esquerda\n");
        } else {
            return 0; // Direção inválida
        }
        if (*nova_linha < 0 || *nova_linha >= TAM_TABULEIRO || *nova_coluna < 0 || *nova_coluna >= TAM_TABULEIRO) {
            return 0; // Fora do tabuleiro
        }
        contador++;
    }
    
    tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
    tabuleiro[*nova_linha][*nova_coluna] = 'B'; // Marca a nova posição
    return 1;
}

// Função para mover a Torre (linhas retas)
int moverTorre(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    *nova_linha = linha;
    *nova_coluna = coluna;
    printf("Movimento da Torre (%d casas para %s):\n", casas, direcao);
    
    for (int i = 1; i <= casas; i++) {
        if (strcmp(direcao, "direita") == 0) {
            (*nova_coluna)++;
            printf("Direita\n");
        } else if (strcmp(direcao, "esquerda") == 0) {
            (*nova_coluna)--;
            printf("Esquerda\n");
        } else if (strcmp(direcao, "cima") == 0) {
            (*nova_linha)--;
            printf("Cima\n");
        } else if (strcmp(direcao, "baixo") == 0) {
            (*nova_linha)++;
            printf("Baixo\n");
        } else {
            return 0; // Direção inválida
        }
        if (*nova_linha < 0 || *nova_linha >= TAM_TABULEIRO || *nova_coluna < 0 || *nova_coluna >= TAM_TABULEIRO) {
            return 0; // Fora do tabuleiro
        }
    }
    
    tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
    tabuleiro[*nova_linha][*nova_coluna] = 'T'; // Marca a nova posição
    return 1;
}

// Função para mover a Rainha (qualquer direção)
int moverRainha(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    *nova_linha = linha;
    *nova_coluna = coluna;
    int contador = 1;
    printf("Movimento da Rainha (%d casas para %s):\n", casas, direcao);
    
    do {
        if (strcmp(direcao, "direita") == 0) {
            (*nova_coluna)++;
            printf("Direita\n");
        } else if (strcmp(direcao, "esquerda") == 0) {
            (*nova_coluna)--;
            printf("Esquerda\n");
        } else if (strcmp(direcao, "cima") == 0) {
            (*nova_linha)--;
            printf("Cima\n");
        } else if (strcmp(direcao, "baixo") == 0) {
            (*nova_linha)++;
            printf("Baixo\n");
        } else if (strcmp(direcao, "cima-direita") == 0) {
            (*nova_linha)--;
            (*nova_coluna)++;
            printf("Cima Direita\n");
        } else if (strcmp(direcao, "cima-esquerda") == 0) {
            (*nova_linha)--;
            (*nova_coluna)--;
            printf("Cima Esquerda\n");
        } else if (strcmp(direcao, "baixo-direita") == 0) {
            (*nova_linha)++;
            (*nova_coluna)++;
            printf("Baixo Direita\n");
        } else if (strcmp(direcao, "baixo-esquerda") == 0) {
            (*nova_linha)++;
            (*nova_coluna)--;
            printf("Baixo Esquerda\n");
        } else {
            return 0; // Direção inválida
        }
        if (*nova_linha <  0 || *nova_linha >= TAM_TABULEIRO || *nova_coluna < 0 || *nova_coluna >= TAM_TABULEIRO) {
            return 0; // Fora do tabuleiro
        }
        contador++;
    } while (contador <= casas);
    
    tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
    tabuleiro[*nova_linha][*nova_coluna] = 'R'; // Marca a nova posição
    return 1;
}

// Função para mover o Rei (1 casa em qualquer direção)
int moverRei(int linha, int coluna, char *direcao, int casas, char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int *nova_linha, int *nova_coluna) {
    if (casas != 1) return 0; // Rei move apenas 1 casa
    printf("Movimento do Rei (1 casa para %s):\n", direcao);
    
    *nova_linha = linha;
    *nova_coluna = coluna;
    for (int i = 1; i <= casas; i++) {
        if (strcmp(direcao, "direita") == 0) {
            (*nova_coluna)++;
            printf("Direita\n");
        } else if (strcmp(direcao, "esquerda") == 0) {
            (*nova_coluna)--;
            printf("Esquerda\n");
        } else if (strcmp(direcao, "cima") == 0) {
            (*nova_linha)--;
            printf("Cima\n");
        } else if (strcmp(direcao, "baixo") == 0) {
            (*nova_linha)++;
            printf("Baixo\n");
        } else if (strcmp(direcao, "cima-direita") == 0) {
            (*nova_linha)--;
            (*nova_coluna)++;
            printf("Cima Direita\n");
        } else if (strcmp(direcao, "cima-esquerda") == 0) {
            (*nova_linha)--;
            (*nova_coluna)--;
            printf("Cima Esquerda\n");
        } else if (strcmp(direcao, "baixo-direita") == 0) {
            (*nova_linha)++;
            (*nova_coluna)++;
            printf("Baixo Direita\n");
        } else if (strcmp(direcao, "baixo-esquerda") == 0) {
            (*nova_linha)++;
            (*nova_coluna)--;
            printf("Baixo Esquerda\n");
        } else {
            return 0; // Direção inválida
        }
        if (*nova_linha < 0 || *nova_linha >= TAM_TABULEIRO || *nova_coluna < 0 || *nova_coluna >= TAM_TABULEIRO) {
            return 0; // Fora do tabuleiro
        }
    }
    
    tabuleiro[linha][coluna] = '.'; // Limpa a posição inicial
    tabuleiro[*nova_linha][*nova_coluna] = 'K'; // Marca a nova posição
    return 1;
}

int main() {
    char tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);
    
    // Ordem fixa das peças
    char *pecas[] = {"Peao", "Cavalo", "Bispo", "Torre", "Rainha", "Rei"};
    char peca[10], direcao[20];
    int linha, coluna, casas, nova_linha, nova_coluna;
    
    // Loop para mover cada peça na ordem especificada
    for (int p = 0; p < 6; p++) {
        strcpy(peca, pecas[p]);
        printf("\nMover %s:\n", peca);
        
        // Solicita a posição inicial
        printf("Digite a linha inicial (0-7): ");
        scanf("%d", &linha);
        printf("Digite a coluna inicial (0-7): ");
        scanf("%d", &coluna);
        
        // Valida a posição inicial
        if (linha < 0 || linha >= TAM_TABULEIRO || coluna < 0 || coluna >= TAM_TABULEIRO) {
            printf("Erro: Posicao inicial invalida!\n");
            return 1;
        }
        
        // Solicita a direção
        printf("Digite a direcao (ex: direita, cima-direita, 2cima-1direita, etc.): ");
        scanf("%s", direcao);
        
        // Solicita o número de casas
        printf("Digite o numero de casas a mover: ");
        scanf("%d", &casas);
        
        // Executa o movimento com base na peça
        int movimento_valido = 0;
        if (strcmp(peca, "Peao") == 0) {
            movimento_valido = moverPeao(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        } else if (strcmp(peca, "Cavalo") == 0) {
            movimento_valido = moverCavalo(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        } else if (strcmp(peca, "Bispo") == 0) {
            movimento_valido = moverBispo(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        } else if (strcmp(peca, "Torre") == 0) {
            movimento_valido = moverTorre(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        } else if (strcmp(peca, "Rainha") == 0) {
            movimento_valido = moverRainha(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        } else if (strcmp(peca, "Rei") == 0) {
            movimento_valido = moverRei(linha, coluna, direcao, casas, tabuleiro, &nova_linha, &nova_coluna);
        }
        
        // Verifica se o movimento foi válido
        if (!movimento_valido) {
            printf("Erro: Movimento invalido para %s ou fora do tabuleiro!\n", peca);
            return 1;
        }
        
        // Exibe o tabuleiro com a posição final
        exibirTabuleiro(tabuleiro, nova_linha, nova_coluna, peca[0]);
    }
    
    printf("Todas蒀as pecas foram movidas!\n");
    return 0;
}
