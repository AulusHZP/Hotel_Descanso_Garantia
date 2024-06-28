# Hotel Descanso Garantido

Hotel Descanso Garantido é um software desenvolvido para gerenciar as operações de um hotel, incluindo o cadastro de clientes, funcionários, quartos e estadias. O objetivo é substituir o uso de planilhas e cadernos, proporcionando uma solução mais eficiente e organizada.

## Funcionalidades

- **Cadastro de Clientes**: Inclui informações como código, nome, endereço e telefone.
- **Cadastro de Funcionários**: Inclui informações como código, nome, telefone, cargo e salário.
- **Cadastro de Quartos**: Inclui informações como número do quarto, quantidade de hóspedes, valor da diária e status (ocupado/desocupado).
- **Cadastro de Estadias**: Inclui informações como código da estadia, data de entrada, data de saída, quantidade de diárias, código do cliente e número do quarto.
- **Validação de Reservas**: Garante que quartos ocupados não possam ser reservados novamente no mesmo período.

## Estrutura do Projeto

- `hotel_management.h`: Cabeçalhos e definições de estruturas e funções.
- `hotel_management.c`: Implementação das funções de gerenciamento do hotel.
- `hotel_tests.c`: Testes automatizados utilizando a biblioteca `munit`.
- `munit.h` e `munit.c`: Biblioteca de testes unitários.

## Pré-requisitos

- GCC (GNU Compiler Collection)
- Biblioteca `munit` (incluída no projeto)

## Compilação

### Programa Principal

Para compilar o programa principal:

```bash
gcc -o hotel_program hotel_management.c -DRUN_MAIN
