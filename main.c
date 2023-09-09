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

    printf("Digite o telefone do aluno (apenas números): ");
    fgets(aluno.telefone, sizeof(aluno.telefone), stdin);
    aluno.telefone[strcspn(aluno.telefone, "\n")] = '\0'; // Remove a quebra de linha

    // Validação do telefone - garantindo que todos os caracteres sejam dígitos
    int len = strlen(aluno.telefone);
    for (int i = 0; i < len; i++) {
        if (!isdigit(aluno.telefone[i])) {
            printf("Telefone inválido. Use apenas números.\n");
            fclose(saida);
            return 1;
        }
    }

    printf("Digite o curso do aluno: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = '\0'; // Remove a quebra de linha

    char notaStr[10]; // Usado para armazenar temporariamente a entrada das notas

    printf("Digite a nota 1 do aluno: ");
    fgets(notaStr, sizeof(notaStr), stdin);
    if (sscanf(notaStr, "%f", &aluno.nota1) != 1) {
        printf("Nota 1 inválida. Use apenas números.\n");
        fclose(saida);
        return 1;
    }

    printf("Digite a nota 2 do aluno: ");
    fgets(notaStr, sizeof(notaStr), stdin);
    if (sscanf(notaStr, "%f", &aluno.nota2) != 1) {
        printf("Nota 2 inválida. Use apenas números.\n");
        fclose(saida);
        return 1;
    }

    float media = calcularMedia(aluno.nota1, aluno.nota2);
    const char *situacao = determinarSituacao(media);

    fprintf(saida, "%s,%s,%s,%.2f,%s\n", aluno.nome, aluno.telefone, aluno.curso, media, situacao);

    fclose(saida);

    printf("Processamento concluído. Resultados salvos em SituacaoFinal.csv\n");

    return 0;
}
