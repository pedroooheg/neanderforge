#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define MAX_SYMBOLS 256

// Estrutura interna para armazenar os dados
typedef struct {
    char nome[64];
    int endereco;
} simbolo_t;

// Nossa "agenda" de símbolos e o contador de quantos já temos
static simbolo_t tabela[MAX_SYMBOLS];
static int total_simbolos = 0;

// 🔍 1. Busca o índice de um símbolo pelo nome
int buscar_simbolo(char *nome) {
    for (int i = 0; i < total_simbolos; i++) {
        if (strcmp(tabela[i].nome, nome) == 0) {
            return i; // Encontrou! Retorna a posição no array
        }
    }
    return -1; // Não encontrado
}

// 📝 2. Adiciona um novo símbolo (usado na Primeira Passagem)
void adicionar_simbolo(char *nome, int endereco) {
    // Verifica se já existe para evitar duplicatas
    if (buscar_simbolo(nome) != -1) {
        fprintf(stderr, "Erro de Compilação: Rótulo '%s' redefinido.\n", nome);
        exit(1);
    }

    // Verifica se há espaço na tabela
    if (total_simbolos >= MAX_SYMBOLS) {
        fprintf(stderr, "Erro: Limite da tabela de símbolos atingido.\n");
        exit(1);
    }

    // Copia os dados para a nova posição
    strncpy(tabela[total_simbolos].nome, nome, 63);
    tabela[total_simbolos].nome[63] = '\0'; // Garante o fim da string
    tabela[total_simbolos].endereco = endereco;
    
    total_simbolos++;
}

// 3. Retorna o endereço de um símbolo (usado na Segunda Passagem)
int obter_endereco(char *nome) {
    int indice = buscar_simbolo(nome);
    if (indice == -1) {
        fprintf(stderr, "Erro de Compilação: Rótulo '%s' não definido.\n", nome);
        exit(1);
    }
    return tabela[indice].endereco;
}