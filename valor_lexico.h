typedef enum TokenType
{
    IDENTIFIER,
    LITERAL
} TokenType;

typedef struct Valor_lexico
{
    int line_number;
    TokenType type;
    char* token_val;
} Valor_lexico;