#ifndef HOTEL_MANAGEMENT_H
#define HOTEL_MANAGEMENT_H

#include <stdbool.h>
#include <time.h>

// Definição das estruturas
typedef struct {
    int codigo;
    char nome[100];
    char endereco[150];
    char telefone[15];
} Cliente;

typedef struct {
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct {
    int numero;
    int quantidade_hospedes;
    float valor_diaria;
    char status[10]; // "ocupado" ou "desocupado"
} Quarto;

typedef struct {
    int codigo;
    char data_entrada[11];
    char data_saida[11];
    int quantidade_diarias;
    int codigo_cliente;
    int numero_quarto;
} Estadia;

// Declaração dos arrays e contadores
extern Cliente clientes[100];
extern Funcionario funcionarios[50];
extern Quarto quartos[30];
extern Estadia estadias[200];

extern int contador_clientes;
extern int contador_funcionarios;
extern int contador_quartos;
extern int contador_estadias;

// Declaração das funções
int gerar_codigo_cliente();
int gerar_codigo_funcionario();
int gerar_codigo_estadia();
bool cliente_existe(int codigo);
void cadastrar_cliente(char nome[], char endereco[], char telefone[]);
bool funcionario_existe(int codigo);
void cadastrar_funcionario(char nome[], char telefone[], char cargo[], float salario);
bool quarto_disponivel(int numero, char data_entrada[], char data_saida[], int quantidade_hospedes);
char *strptime(const char *s, const char *format, struct tm *tm);
time_t converter_data(const char *data);
int calcular_diarias(char data_entrada[], char data_saida[]);
void cadastrar_estadia(int codigo_cliente, int quantidade_hospedes, char data_entrada[], char data_saida[]);
void salvar_dados();
void carregar_dados();

#endif // HOTEL_MANAGEMENT_H
