#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura Aluno
typedef struct {
    char nome[100];
    char telefone[15];
    char curso[100];
    float nota1;
    float nota2;
} Aluno;

// Função para calcular a média de duas notas
float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}

// Função para determinar a situação do aluno
const char *determinarSituacao(float media) {
    return (media >= 7.0) ? "APROVADO" : "REPROVADO";
}

int main() {
    // Abertura do arquivo de saída para escrita
    FILE *saida = fopen("SituacaoFinal.csv", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    // Escreve o cabeçalho no arquivo de saída
    fprintf(saida, "Nome,Nota Média,Situação\n");

    // Solicita os dados do aluno ao usuário
    Aluno aluno;
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, sizeof(aluno.nome), stdin);

    printf("Digite o telefone do aluno: ");
    fgets(aluno.telefone, sizeof(aluno.telefone), stdin);

    printf("Digite o curso do aluno: ");
    fgets(aluno.curso, sizeof(aluno.curso), stdin);

    printf("Digite a nota 1 do aluno: ");
    scanf("%f", &aluno.nota1);

    printf("Digite a nota 2 do aluno: ");
    scanf("%f", &aluno.nota2);

    // Calcula a média das notas do aluno e determina a situação
    float media = calcularMedia(aluno.nota1, aluno.nota2);
    const char *situacao = determinarSituacao(media);

    // Escreve os dados no arquivo de saída
    fprintf(saida, "%s,%.2f,%s\n", aluno.nome, media, situacao);

    // Fecha o arquivo de saída
    fclose(saida);

    printf("Processamento concluído. Resultados salvos em SituacaoFinal.csv\n");

    return 0;
}
