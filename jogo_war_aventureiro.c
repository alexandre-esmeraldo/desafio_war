#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================================================
// Struct Territorio
// ================================================
typedef struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// ================================================
// Função principal
// ================================================
int main() {
    int quantidade;
    Territorio* mapa = NULL;
    
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    
    printf("=== JOGO WAR - FASE 2: ATAQUES ===\n\n");
    
    // Alocação dinâmica de memória
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    if(quantidade < 2) {
        printf("E necessario pelo menos 2 territorios para ataques!\n");
        return 1;
    }
    
    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    if(mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    
    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);
    
    // Menu principal de interatividade
    int opcao;
    do {
        printf("\n=== MENU DE ATAQUE ===\n");
        printf("1 - Exibir todos os territorios\n");
        printf("2 - Realizar um ataque\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if(opcao == 1) {
            exibirTerritorios(mapa, quantidade);
        }
        else if(opcao == 2) {
            int idxAtacante, idxDefensor;
            
            exibirTerritorios(mapa, quantidade);
            
            printf("\nDigite o numero do territorio ATACANTE: ");
            scanf("%d", &idxAtacante);
            idxAtacante--;  // Ajuste para índice do vetor (0-based)
            
            printf("Digite o numero do territorio DEFENSOR: ");
            scanf("%d", &idxDefensor);
            idxDefensor--;
            
            // Validações
            if(idxAtacante < 0 || idxAtacante >= quantidade || 
               idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("Indices invalidos!\n");
                continue;
            }
            
            if(strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("Nao e permitido atacar um territorio da mesma cor!\n");
                continue;
            }
            
            if(mapa[idxAtacante].tropas <= 1) {
                printf("O territorio atacante precisa de pelo menos 2 tropas!\n");
                continue;
            }
            
            // Realiza o ataque usando ponteiros
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
            
            // Exibe resultado após o ataque
            printf("\n--- Resultado do ataque ---\n");
            exibirTerritorios(mapa, quantidade);
        }
        
    } while(opcao != 3);
    
    liberarMemoria(mapa);
    printf("\nJogo encerrado. Memoria liberada.\n");
    
    return 0;
}

// ================================================
// Função para cadastrar territórios
// ================================================
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    
    for(int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i+1);
        
        printf("Nome do territorio: ");
        scanf(" %29[^\n]", mapa[i].nome);
        
        printf("Cor do exercito: ");
        scanf(" %9s", mapa[i].cor);
        
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        // Garantir que tenha pelo menos 1 tropa
        if(mapa[i].tropas < 1) mapa[i].tropas = 1;
    }
}

// ================================================
// Função para exibir todos os territórios
// ================================================
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== MAPA DE TERRITORIOS ===\n");
    for(int i = 0; i < quantidade; i++) {
        printf("%2d - %s | Cor: %s | Tropas: %d\n", 
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ================================================
// Função de Ataque (usando ponteiros)
// ================================================
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) atacando %s (%s)...\n", 
           atacante->nome, atacante->cor, 
           defensor->nome, defensor->cor);
    
    // Simulação de dados de batalha (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    
    printf("Dado do Atacante: %d | Dado do Defensor: %d\n", dadoAtacante, dadoDefensor);
    
    if(dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("ATAQUE BEM SUCEDIDO!\n");
        
        // Conquista o território
        strcpy(defensor->cor, atacante->cor);
        
        // Move metade das tropas do atacante para o defensor (aproximado)
        int tropasMover = atacante->tropas / 2;
        if(tropasMover < 1) tropasMover = 1;
        
        defensor->tropas = tropasMover;
        atacante->tropas -= tropasMover;
        
        printf("%s conquistou %s!\n", atacante->nome, defensor->nome);
    }
    else {
        // Defensor vence
        printf("ATAQUE REPELIDO!\n");
        atacante->tropas--;  // Atacante perde 1 tropa
        if(atacante->tropas < 1) atacante->tropas = 1;
    }
}

// ================================================
// Libera a memória alocada dinamicamente
// ================================================
void liberarMemoria(Territorio* mapa) {
    if(mapa != NULL) {
        free(mapa);
    }
}
