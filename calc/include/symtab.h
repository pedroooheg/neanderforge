#ifndef SYMTAB_H
#define SYMTAB_H

// 📍 Adiciona um novo rótulo e seu endereço à tabela
void adicionar_simbolo(char *nome, int endereco);

// 🔍 Procura o índice de um rótulo (retorna -1 se não existir)
int buscar_simbolo(char *nome);

// 🎯 Retorna o endereço final de um rótulo para a tradução
int obter_endereco(char *nome);

#endif