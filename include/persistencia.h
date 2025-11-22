#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <stddef.h>

#define ARQ_CLIENTES "data/Clientes.csv"
#define ARQ_PRODUTOS "data/Produtos.csv"
#define ARQ_PEDIDOS "data/Pedidos.csv"

#define MAX_NOME 100
#define MAX_ENDERECO 150
#define MAX_TELEFONE 32
#define MAX_STATUS 32

// Eu não gosto da abordagem de usar typedef struct em tudo, but gotta get going
typedef struct {
    int id;
    char nome[MAX_NOME];
    char endereco[MAX_ENDERECO];
    char telefone[MAX_TELEFONE];
} Cliente;

typedef struct {
    int id;
    char nome[MAX_NOME];
    double preco;
    int estoque;
} Produto;

typedef struct {
    int id;
    int clienteId;
    int produtoId;
    int quantidade;
    char status[MAX_STATUS];
} Pedido;

int salvar_clientes(const Cliente *clientes, size_t quantidade);
int carregar_clientes(Cliente **clientes, size_t *quantidade);

int salvar_produtos(const Produto *produtos, size_t quantidade);
int carregar_produtos(Produto **produtos, size_t *quantidade);

int salvar_pedidos(const Pedido *pedidos, size_t quantidade);
int carregar_pedidos(Pedido **pedidos, size_t *quantidade);

#endif
