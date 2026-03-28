#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Agrupa informações relacionadas a um território do jogo War
struct Territorio {
    char nome[30];      // Nome do território (ex: "Brasil", "Argentina")
    char cor[10];       // Cor do exército dono (ex: "Vermelho", "Azul")
    int tropas;         // Quantidade de tropas no território
};

int main() {
    // Vetor de 5 territórios
    struct Territorio territorios[5];
    
    printf("=== CADASTRO DE TERRITORIOS - WAR ===\n\n");
    
    // ====================== CADASTRO DOS TERRITÓRIOS ======================
    for(int i = 0; i < 5; i++) {
        printf("--- Territorio %d de 5 ---\n", i+1);
        
        // Limpa o buffer do teclado antes de ler strings
        getchar();  // importante para evitar problemas com fgets após scanf
        
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        // Remove o '\n' que o fgets deixa no final
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';
        
        printf("Digite a cor do exercito (ex: Vermelho, Azul, Verde): ");
        scanf("%s", territorios[i].cor);
        
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
    
    // ====================== EXIBIÇÃO DOS DADOS ======================
    printf("========================================\n");
    printf("          TERRITORIOS CADASTRADOS       \n");
    printf("========================================\n\n");
    
    for(int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i+1);
        printf("  Nome      : %s\n", territorios[i].nome);
        printf("  Cor       : %s\n", territorios[i].cor);
        printf("  Tropas    : %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }
    
    printf("\nCadastro finalizado com sucesso!\n");
    
    return 0;
}
