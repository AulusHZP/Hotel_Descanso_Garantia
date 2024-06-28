#include "hotel_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição das variáveis globais
Cliente clientes[100];
Funcionario funcionarios[50];
Quarto quartos[30];
Estadia estadias[200];

int contador_clientes = 0;
int contador_funcionarios = 0;
int contador_quartos = 0;
int contador_estadias = 0;

// Função para gerar código automaticamente
int gerar_codigo_cliente() {
    static int codigo = 1;
    return codigo++;
}

int gerar_codigo_funcionario() {
    static int codigo = 1;
    return codigo++;
}

int gerar_codigo_estadia() {
    static int codigo = 1;
    return codigo++;
}

// Função para verificar se um cliente já existe
bool cliente_existe(int codigo) {
    for (int i = 0; i < contador_clientes; i++) {
        if (clientes[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

// Função para cadastrar cliente
void cadastrar_cliente(char nome[], char endereco[], char telefone[]) {
    int codigo = gerar_codigo_cliente();
    if (cliente_existe(codigo)) {
        printf("Cliente com código %d já existe.\n", codigo);
        return;
    }
    Cliente novo_cliente;
    novo_cliente.codigo = codigo;
    strcpy(novo_cliente.nome, nome);
    strcpy(novo_cliente.endereco, endereco);
    strcpy(novo_cliente.telefone, telefone);
    clientes[contador_clientes++] = novo_cliente;
    printf("Cliente cadastrado com sucesso. Código: %d\n", codigo);
}

// Função para verificar se um funcionário já existe
bool funcionario_existe(int codigo) {
    for (int i = 0; i < contador_funcionarios; i++) {
        if (funcionarios[i].codigo == codigo) {
            return true;
        }
    }
    return false;
}

// Função para cadastrar funcionário
void cadastrar_funcionario(char nome[], char telefone[], char cargo[], float salario) {
    int codigo = gerar_codigo_funcionario();
    if (funcionario_existe(codigo)) {
        printf("Funcionário com código %d já existe.\n", codigo);
        return;
    }
    Funcionario novo_funcionario;
    novo_funcionario.codigo = codigo;
    strcpy(novo_funcionario.nome, nome);
    strcpy(novo_funcionario.telefone, telefone);
    strcpy(novo_funcionario.cargo, cargo);
    novo_funcionario.salario = salario;
    funcionarios[contador_funcionarios++] = novo_funcionario;
    printf("Funcionário cadastrado com sucesso. Código: %d\n", codigo);
}

// Função para verificar se um quarto está disponível
bool quarto_disponivel(int numero, char data_entrada[], char data_saida[], int quantidade_hospedes) {
    for (int i = 0; i < contador_quartos; i++) {
        if (quartos[i].numero == numero && strcmp(quartos[i].status, "desocupado") == 0 && quartos[i].quantidade_hospedes >= quantidade_hospedes) {
            for (int j = 0; j < contador_estadias; j++) {
                if (estadias[j].numero_quarto == numero && strcmp(estadias[j].data_entrada, data_entrada) == 0 && strcmp(estadias[j].data_saida, data_saida) == 0) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

// Definição da função strptime para compatibilidade
char *strptime(const char *s, const char *format, struct tm *tm) {
    char *p = (char *)s;
    sscanf(p, "%2d/%2d/%4d", &tm->tm_mday, &tm->tm_mon, &tm->tm_year);
    tm->tm_mon -= 1;
    tm->tm_year -= 1900;
    tm->tm_hour = 0;
    tm->tm_min = 0;
    tm->tm_sec = 0;
    return p + strlen(p);
}

// Função auxiliar para converter string de data para time_t
time_t converter_data(const char *data) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strptime(data, "%d/%m/%Y", &tm);
    return mktime(&tm);
}

// Função para calcular quantidade de diárias
int calcular_diarias(char data_entrada[], char data_saida[]) {
    time_t entrada = converter_data(data_entrada);
    time_t saida = converter_data(data_saida);
    double diff = difftime(saida, entrada) / (60 * 60 * 24);
    return (int) diff;
}

// Função para cadastrar estadia
void cadastrar_estadia(int codigo_cliente, int quantidade_hospedes, char data_entrada[], char data_saida[]) {
    if (!cliente_existe(codigo_cliente)) {
        printf("Cliente com código %d não existe.\n", codigo_cliente);
        return;
    }
    for (int i = 0; i < contador_quartos; i++) {
        if (quarto_disponivel(quartos[i].numero, data_entrada, data_saida, quantidade_hospedes)) {
            int codigo = gerar_codigo_estadia();
            Estadia nova_estadia;
            nova_estadia.codigo = codigo;
            strcpy(nova_estadia.data_entrada, data_entrada);
            strcpy(nova_estadia.data_saida, data_saida);
            nova_estadia.quantidade_diarias = calcular_diarias(data_entrada, data_saida);
            nova_estadia.codigo_cliente = codigo_cliente;
            nova_estadia.numero_quarto = quartos[i].numero;
            estadias[contador_estadias++] = nova_estadia;
            strcpy(quartos[i].status, "ocupado");
            printf("Estadia cadastrada com sucesso. Código: %d\n", codigo);
            return;
        }
    }
    printf("Não há quartos disponíveis para a quantidade de hospedes desejada.\n");
}

// Funções para salvar e carregar dados
void salvar_dados() {
    FILE *file;

    file = fopen("clientes.dat", "wb");
    fwrite(&contador_clientes, sizeof(int), 1, file);
    fwrite(clientes, sizeof(Cliente), contador_clientes, file);
    fclose(file);

    file = fopen("funcionarios.dat", "wb");
    fwrite(&contador_funcionarios, sizeof(int), 1, file);
    fwrite(funcionarios, sizeof(Funcionario), contador_funcionarios, file);
    fclose(file);

    file = fopen("quartos.dat", "wb");
    fwrite(&contador_quartos, sizeof(int), 1, file);
    fwrite(quartos, sizeof(Quarto), contador_quartos, file);
    fclose(file);

    file = fopen("estadias.dat", "wb");
    fwrite(&contador_estadias, sizeof(int), 1, file);
    fwrite(estadias, sizeof(Estadia), contador_estadias, file);
    fclose(file);

    printf("Dados salvos com sucesso.\n");
}

void carregar_dados() {
    FILE *file;

    file = fopen("clientes.dat", "rb");
    if (file != NULL) {
        fread(&contador_clientes, sizeof(int), 1, file);
        fread(clientes, sizeof(Cliente), contador_clientes, file);
        fclose(file);
    }

    file = fopen("funcionarios.dat", "rb");
    if (file != NULL) {
        fread(&contador_funcionarios, sizeof(int), 1, file);
        fread(funcionarios, sizeof(Funcionario), contador_funcionarios, file);
        fclose(file);
    }

    file = fopen("quartos.dat", "rb");
    if (file != NULL) {
        fread(&contador_quartos, sizeof(int), 1, file);
        fread(quartos, sizeof(Quarto), contador_quartos, file);
        fclose(file);
    }

    file = fopen("estadias.dat", "rb");
    if (file != NULL) {
        fread(&contador_estadias, sizeof(int), 1, file);
        fread(estadias, sizeof(Estadia), contador_estadias, file);
        fclose(file);
    }

    printf("Dados carregados com sucesso.\n");
}

// Função de menu
void menu() {
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Funcionario\n");
    printf("3. Cadastrar Estadia\n");
    printf("4. Salvar Dados\n");
    printf("5. Carregar Dados\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

#ifdef RUN_MAIN
int main() {
    int opcao;
    char nome[100], endereco[150], telefone[15], cargo[50], data_entrada[11], data_saida[11];
    float salario;
    int codigo_cliente, quantidade_hospedes;

    carregar_dados();

    // Dados iniciais para teste
    Quarto q1 = {101, 2, 150.0, "desocupado"};
    Quarto q2 = {102, 3, 200.0, "desocupado"};
    quartos[contador_quartos++] = q1;
    quartos[contador_quartos++] = q2;

    while (1) {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Endereço: ");
                scanf(" %[^\n]", endereco);
                printf("Telefone: ");
                scanf(" %[^\n]", telefone);
                cadastrar_cliente(nome, endereco, telefone);
                break;
            case 2:
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Telefone: ");
                scanf(" %[^\n]", telefone);
                printf("Cargo: ");
                scanf(" %[^\n]", cargo);
                printf("Salário: ");
                scanf("%f", &salario);
                cadastrar_funcionario(nome, telefone, cargo, salario);
                break;
            case 3:
                printf("Código do Cliente: ");
                scanf("%d", &codigo_cliente);
                printf("Quantidade de Hospedes: ");
                scanf("%d", &quantidade_hospedes);
                printf("Data de Entrada (dd/mm/yyyy): ");
                scanf(" %[^\n]", data_entrada);
                printf("Data de Saída (dd/mm/yyyy): ");
                scanf(" %[^\n]", data_saida);
                cadastrar_estadia(codigo_cliente, quantidade_hospedes, data_entrada, data_saida);
                break;
            case 4:
                salvar_dados();
                break;
            case 5:
                carregar_dados();
                break;
            case 6:
                salvar_dados();
                exit(0);
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
#endif
