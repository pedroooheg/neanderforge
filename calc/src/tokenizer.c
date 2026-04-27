#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tokenizer.h"

// Pula espaços, tabs e quebras de linha
void skip_whitespace(tokenizer_t *tk) {
    while (tk->str[tk->cursor] != '\0' && isspace(tk->str[tk->cursor])) {
        tk->cursor++;
    }
}

// Função principal para capturar o próximo token
token_t* get_next_token(tokenizer_t *tk) {
    skip_whitespace(tk);

    // 1. Fim de arquivo (EOF) 🏁
    if (tk->str[tk->cursor] == '\0') {
        return create_token(TOKEN_EOF, NULL, 0);
    }

    char *current_pos = &tk->str[tk->cursor];

    // 2. Captura de Números
    if (isdigit(*current_pos)) {
        char *endptr;
        long val = strtol(current_pos, &endptr, 10);
        tk->cursor += (endptr - current_pos); // Avança o cursor para após o número
        return create_token(TOKEN_NUMBER, NULL, val);
    }

    // 3. Captura de Identificadores (Instruções ou Rótulos)
    if (isalpha(*current_pos)) {
        int start = tk->cursor;
        
        // Avança enquanto for letra ou número (ex: VAR1)
        while (isalnum(tk->str[tk->cursor])) {
            tk->cursor++;
        }

        // Extrai o lexema (a palavra em si)
        int length = tk->cursor - start;
        char *lexeme = malloc(length + 1);
        strncpy(lexeme, &tk->str[start], length);
        lexeme[length] = '\0';

        // Verifica se é uma definição de rótulo (ex: "SOMA:")
        if (tk->str[tk->cursor] == ':') {
            tk->cursor++; // Pula o ':'
            return create_token(TOKEN_LABEL_DEF, lexeme, 0);
        }

        // Aqui, na integração, verificaríamos se o lexeme é instrução (LDA, etc)
        // Por enquanto, retornamos como um identificador genérico
        return create_token(TOKEN_IDENTIFIER, lexeme, 0);
    }

    // 4. Erro de Caractere Inválido
    tk->cursor++; 
    return create_token(TOKEN_ERROR, NULL, 0);
}