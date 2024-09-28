#include "minishell.h"


// 1 - percorrer string procurando $ sem aspas simples aberta;
// 2 - puxar valor da env e pegar o seu tamanho e soma com o len total do input;
// 3 - mallocar de novo com o tamanho total
// 4 - copiar mudando o valor

t_part  find_env(char *w)
{
    int i;
    int quotes;
    t_part  p;

    quotes = 0;
    p = (t_part){0};
    i = 0;
    while (w[i])
    {
        if (w[i] == '\'' && quotes == 0)
            quotes = w[i];
        else if (w[i] == quotes)
            quotes = 0;
        if (w[i] == '$' && !quotes)
        {
            i++;
            p.start = i;
            if (w[i] == '{')
            {
                i++;
                p = (t_part){ .start = i, .end = i };
                while (w[i] && w[i] != '}')
                    i++;
                return (p.end = i, p);
            }
            else if (ft_isalpha(w[i]) || w[i] == '_')
            {
                while (isalnum((int)w[i]) || w[i] == '_')
                    i++;
                return (p.end = i, p);
            }
        }
        i++;
    }
    return (p);
}


// void expand_variable(const char *input) {
//     const char *p = input;  // Ponteiro para percorrer a string
//     while (*p != '\0') {
//         if (*p == '$') {  // Detecta o símbolo de variável
//             p++;  // Move para o próximo caractere

//             // Se houver '{', procuramos por '}'
//             if (*p == '{') {
//                 p++;  // Move após o '{'
//                 const char *start = p;  // Início do nome da variável

//                 // Continuar até encontrar '}'
//                 while (*p != '}' && *p != '\0') {
//                     p++;
//                 }

//                 if (*p == '}') {
//                     // Extraímos a variável entre '{' e '}'
//                     char var_name[256];
//                     strncpy(var_name, start, p - start);
//                     var_name[p - start] = '\0';  // Adiciona o terminador nulo

//                     printf("Variável encontrada: %s\n", var_name);
//                     p++;  // Move após '}'
//                 } else {
//                     printf("Erro: Falta '}' para fechar a variável.\n");
//                     return;
//                 }
//             } 
//             // Caso sem '{}', lemos o nome da variável diretamente
//             else if (isalpha(*p) || *p == '_') {  // Nome de variável válido começa com letra ou '_'
//                 const char *start = p;  // Início do nome da variável
                
//                 // Continuar até encontrar um caractere inválido
//                 while (isalnum(*p) || *p == '_') {
//                     p++;
//                 }

//                 // Extraímos o nome da variável
//                 char var_name[256];
//                 strncpy(var_name, start, p - start);
//                 var_name[p - start] = '\0';  // Adiciona o terminador nulo

//                 printf("Variável encontrada: %s\n", var_name);
//             } 
//             // Se o caractere após o '$' não for válido
//             else {
//                 printf("Erro: Variável inválida após '$'.\n");
//             }
//         } else {
//             p++;  // Move para o próximo caractere
//         }
//     }
// }