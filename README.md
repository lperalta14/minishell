![Demo](putaminishell.gif)

minishell/
├── src/
│   ├── main.c
│   ├── lexer/          # Tokenización
│   ├── parser/         # Análisis sintáctico
│   ├── expander/       # Expansión de variables
│   ├── executor/       # Ejecución
│   ├── builtins/       # Comandos internos
│   └── utils/          # Utilidades
├── include/
└── Makefile

Pipeline de Ejecución

Input → Lexer → Parser → Expander → Executor

tokenizacion jerarquía; comillas dobles ("..."), comillas simples ('...') y sin comillas (Expansión normal).

TIPOS DE TOKENS;
WORD;   
PIPE;   |
REDIRECTION IN;
REDIRECTION OUT;
APPEND;
HEREDOC;
OPARENT;
CPARENT;


