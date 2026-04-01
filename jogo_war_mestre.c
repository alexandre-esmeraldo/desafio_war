#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================================================
// Struct Territorio
// ================================================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos
void cadastrarTerritorios(Territorio* mapa, int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missao);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void exibirMissao(char* missao);

// ================================================
// MAIN
// ================================================
int main() {
    int quantidade;
    Territorio* mapa = NULL;

    srand(time(NULL));

    printf("=== WAR COM MISSOES ===\n\n");

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    if(quantidade < 2) {
        printf("Minimo de 2 territorios!\n");
        return 1;
    }

    mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    if(mapa == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    // ================= MISSÕES =================
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar exercito Vermelho",
        "Acumular 10 tropas",
        "Conquistar 1 territorio",
        "Dominar metade do mapa"
    };

    int totalMissoes = 5;

    char* missaoJogador = (char*) malloc(100);
    if(missaoJogador == NULL) {
        printf("Erro ao alocar missao!\n");
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    // ================= MENU =================
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            exibirTerritorios(mapa, quantidade);
        }

        else if(opcao == 2) {
            int a, d;

            exibirTerritorios(mapa, quantidade);

            printf("Atacante: ");
            scanf("%d", &a);
            printf("Defensor: ");
            scanf("%d", &d);

            a--; d--;

            if(a < 0 || a >= quantidade || d < 0 || d >= quantidade) {
                printf("Indices invalidos!\n");
                continue;
            }

            if(a == d) {
                printf("Nao pode atacar a si mesmo!\n");
                continue;
            }

            if(strcmp(mapa[a].cor, mapa[d].cor) == 0) {
                printf("Mesmo exercito!\n");
                continue;
            }

            if(mapa[a].tropas <= 1) {
                printf("Tropas insuficientes!\n");
                continue;
            }

            atacar(&mapa[a], &mapa[d]);

            printf("\n--- MAPA ATUAL ---\n");
            exibirTerritorios(mapa, quantidade);

            // 🔍 Verifica missão
            if(verificarMissao(missaoJogador, mapa, quantidade)) {
                printf("\n🏆 MISSÃO CUMPRIDA!\n");
                printf("VOCE VENCEU O JOGO!\n");
                break;
            }
        }

    } while(opcao != 3);

    liberarMemoria(mapa, missaoJogador);

    printf("\nFim do jogo.\n");
    return 0;
}

// ================================================
// CADASTRO
// ================================================
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for(int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d\n", i+1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor: ");
        scanf(" %9s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);

        if(mapa[i].tropas < 1)
            mapa[i].tropas = 1;
    }
}

// ================================================
// EXIBIÇÃO
// ================================================
void exibirTerritorios(Territorio* mapa, int quantidade) {
    for(int i = 0; i < quantidade; i++) {
        printf("%d - %s (%s) Tropas: %d\n",
               i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ================================================
// ATAQUE
// ================================================
void atacar(Territorio* atacante, Territorio* defensor) {

    int dadoA = rand()%6 + 1;
    int dadoD = rand()%6 + 1;

    printf("\nAtaque: %d vs %d\n", dadoA, dadoD);

    if(dadoA > dadoD) {
        printf("Ataque venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int mover = atacante->tropas / 2;
        if(mover < 1) mover = 1;

        if(mover >= atacante->tropas)
            mover = atacante->tropas - 1;

        defensor->tropas = mover;
        atacante->tropas -= mover;
    }
    else {
        printf("Defensor venceu!\n");
        atacante->tropas--;

        if(atacante->tropas < 1)
            atacante->tropas = 1;
    }
}

// ================================================
// MISSÃO
// ================================================
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

void exibirMissao(char* missao) {
    printf("\n=== MISSÃO ===\n%s\n", missao);
}

int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    if(strcmp(missao, "Conquistar 3 territorios") == 0) {
        int count = 0;
        for(int i = 0; i < tamanho; i++)
            if(strcmp(mapa[i].cor, "Azul") == 0)
                count++;
        return count >= 3;
    }

    if(strcmp(missao, "Eliminar exercito Vermelho") == 0) {
        for(int i = 0; i < tamanho; i++)
            if(strcmp(mapa[i].cor, "Vermelho") == 0)
                return 0;
        return 1;
    }

    if(strcmp(missao, "Acumular 10 tropas") == 0) {
        int total = 0;
        for(int i = 0; i < tamanho; i++)
            if(strcmp(mapa[i].cor, "Azul") == 0)
                total += mapa[i].tropas;
        return total >= 10;
    }

    if(strcmp(missao, "Conquistar 1 territorio") == 0) {
        return 1;
    }

    if(strcmp(missao, "Dominar metade do mapa") == 0) {
        int count = 0;
        for(int i = 0; i < tamanho; i++)
            if(strcmp(mapa[i].cor, "Azul") == 0)
                count++;
        return count >= tamanho/2;
    }

    return 0;
}

// ================================================
// LIBERAR MEMÓRIA
// ================================================
void liberarMemoria(Territorio* mapa, char* missao) {
    if(mapa != NULL) free(mapa);
    if(missao != NULL) free(missao);
}
