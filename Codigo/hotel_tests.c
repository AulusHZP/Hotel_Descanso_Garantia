#include "hotel_management.h"
#include "munit.h"

// Funções de configuração e destruição para testes
static void* setup(const MunitParameter params[], void* user_data) {
    // Configuração antes de cada teste
    contador_clientes = 0;
    contador_funcionarios = 0;
    contador_quartos = 0;
    contador_estadias = 0;

    // Dados iniciais para teste
    Quarto q1 = {101, 2, 150.0, "desocupado"};
    Quarto q2 = {102, 3, 200.0, "desocupado"};
    quartos[contador_quartos++] = q1;
    quartos[contador_quartos++] = q2;

    return NULL;
}

static void teardown(void* fixture) {
    // Destruição após cada teste
}

static MunitResult test_cadastrar_cliente(const MunitParameter params[], void* fixture) {
    cadastrar_cliente("João Silva", "Rua A, 123", "99999-9999");
    munit_assert_int(contador_clientes, ==, 1);
    munit_assert_string_equal(clientes[0].nome, "João Silva");
    munit_assert_string_equal(clientes[0].endereco, "Rua A, 123");
    munit_assert_string_equal(clientes[0].telefone, "99999-9999");
    return MUNIT_OK;
}

static MunitResult test_cadastrar_funcionario(const MunitParameter params[], void* fixture) {
    cadastrar_funcionario("Maria Souza", "88888-8888", "Recepcionista", 2000.0);
    munit_assert_int(contador_funcionarios, ==, 1);
    munit_assert_string_equal(funcionarios[0].nome, "Maria Souza");
    munit_assert_string_equal(funcionarios[0].telefone, "88888-8888");
    munit_assert_string_equal(funcionarios[0].cargo, "Recepcionista");
    munit_assert_float(funcionarios[0].salario, ==, 2000.0);
    return MUNIT_OK;
}

static MunitResult test_quarto_disponivel(const MunitParameter params[], void* fixture) {
    bool disponivel = quarto_disponivel(101, "01/07/2024", "03/07/2024", 2);
    munit_assert_true(disponivel);
    return MUNIT_OK;
}

static MunitResult test_cadastrar_estadia(const MunitParameter params[], void* fixture) {
    cadastrar_cliente("João Silva", "Rua A, 123", "99999-9999");
    cadastrar_estadia(1, 2, "01/07/2024", "03/07/2024");
    munit_assert_int(contador_estadias, ==, 1);
    munit_assert_int(estadias[0].codigo_cliente, ==, 1);
    munit_assert_int(estadias[0].numero_quarto, ==, 101);
    munit_assert_string_equal(estadias[0].data_entrada, "01/07/2024");
    munit_assert_string_equal(estadias[0].data_saida, "03/07/2024");
    return MUNIT_OK;
}

static MunitTest tests[] = {
    { "/test_cadastrar_cliente", test_cadastrar_cliente, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_cadastrar_funcionario", test_cadastrar_funcionario, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_quarto_disponivel", test_quarto_disponivel, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { "/test_cadastrar_estadia", test_cadastrar_estadia, setup, teardown, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/hotel_tests", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&suite, NULL, argc, argv);
}
