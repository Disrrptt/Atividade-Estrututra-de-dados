#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[100];
    char telefone[15];
    char curso[100];
    float nota1;
    float nota2;
} Aluno;

float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}

const char *determinarSituacao(float media) {
    return (media >= 7.0) ? "APROVADO" : "REPROVADO";
}

int obterTelefoneNumerico(char *telefone, int tamanho) {
    printf("Digite o telefone do aluno (apenas números): ");
    fgets(telefone, tamanho, stdin);
    telefone[strcspn(telefone, "\n")] = '\0'; // Remove a quebra de linha

    // Validação do telefone - garantindo que todos os caracteres sejam dígitos
    int len = strlen(telefone);
    for (int i = 0; i < len; i++) {
        if (!isdigit(telefone[i])) {
            return 0; // Retorna 0 para indicar erro
        }
    }
    return 1; // Retorna 1 para indicar sucesso
}

int obterNota(float *nota, const char *nomeDaNota) {
    char notaStr[10]; // Usado para armazenar temporariamente a entrada das notas

    while (1) {
        printf("Digite a %s do aluno: ", nomeDaNota);
        fgets(notaStr, sizeof(notaStr), stdin);
        notaStr[strcspn(notaStr, "\n")] = '\0'; // Remove a quebra de linha

        if (sscanf(notaStr, "%f", nota) == 1) {
            if (*nota >= 0 && *nota <= 10) {
                return 1; // Retorna 1 para indicar sucesso
            } else {
                printf("Nota inválida. Deve estar no intervalo de 0 a 10.\n");
            }
        } else {
            printf("Nota inválida. Use apenas números.\n");
        }
    }
}

int main() {
    FILE *saida = fopen("SituacaoFinal.csv", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    fprintf(saida, "Nome,Telefone,Curso,Nota Média,Situação\n");

    Aluno aluno;
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; // Remove a quebra de linha

    while (!obterTelefoneNumerico(aluno.telefone, sizeof(aluno.telefone))) {
        printf("Telefone inválido. Use apenas números.\n");
    }

    printf("Digite o curso do aluno: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0'; // Remove a quebra de linha

    while (!obterNota(&aluno.nota1, "nota 1"));
    while (!obterNota(&aluno.nota2, "nota 2"));

    float media = calcularMedia(aluno.nota1, aluno.nota2);
    const char *situacao = determinarSituacao(media);

    fprintf(saida, "%s,%s,%s,%.2f,%s\n", aluno.nome, aluno.telefone, aluno.curso, media, situacao);

    fclose(saida);

    printf("Processamento concluído. Resultados salvos em SituacaoFinal.csv\n");

    return 0;
}
