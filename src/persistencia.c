#include "../include/persistencia.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Uma coisa muito engraçada que eu encontrei enquanto testava é que muita das vezes
o programa dava erro por conta de caracteres de nova linha (\n) ou retorno de carro (\r)
que vinham junto com os textos lidos do arquivo. Então essa função remove esses caracteres
do final das strings lidas.
*/
static void limpar_trailing(char *texto) {
    if (!texto) {
        return;
    }
    texto[strcspn(texto, "\r\n")] = '\0';
}

static int garantir_capacidade(void **dados, size_t *capacidade, size_t quantidade, size_t tamanho_item) {
    if (quantidade < *capacidade) {
        return 1;
    }
    size_t nova_capacidade = (*capacidade == 0U) ? 8U : (*capacidade * 2U);
    void *novo = realloc(*dados, nova_capacidade * tamanho_item);
    if (!novo) {
        return 0;
    }
    *dados = novo;
    *capacidade = nova_capacidade;
    return 1;
}

static int carregar_clientes_impl(Cliente **clientes, size_t *quantidade, const char *caminho) {
    if (!clientes || !quantidade) {
        return 0;
    }
    *clientes = NULL;
    *quantidade = 0U;
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        return 1; // se o arquivo nao existe, consideramos lista vazia
    }

    Cliente *buffer = NULL;
    size_t capacidade = 0U;
    size_t usados = 0U;
    char linha[512];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '\0' || linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }
        if (!garantir_capacidade((void **)&buffer, &capacidade, usados, sizeof(Cliente))) {
            free(buffer);
            fclose(arquivo);
            return 0;
        }

        Cliente item;
        memset(&item, 0, sizeof(Cliente));

        char *token = strtok(linha, ";");
        if (!token) {
            continue;
        }
        item.id = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        strncpy(item.nome, token, MAX_NOME - 1);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        strncpy(item.endereco, token, MAX_ENDERECO - 1);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        strncpy(item.telefone, token, MAX_TELEFONE - 1);

        buffer[usados++] = item;
    }

    fclose(arquivo);

    if (usados == 0U) {
        free(buffer);
        buffer = NULL;
    } else {
        Cliente *reduzido = realloc(buffer, usados * sizeof(Cliente));
        if (reduzido) {
            buffer = reduzido;
        }
    }

    *clientes = buffer;
    *quantidade = usados;
    return 1;
}

static int carregar_produtos_impl(Produto **produtos, size_t *quantidade, const char *caminho) {
    if (!produtos || !quantidade) {
        return 0;
    }
    *produtos = NULL;
    *quantidade = 0U;
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        return 1;
    }

    Produto *buffer = NULL;
    size_t capacidade = 0U;
    size_t usados = 0U;
    char linha[512];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '\0' || linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }
        if (!garantir_capacidade((void **)&buffer, &capacidade, usados, sizeof(Produto))) {
            free(buffer);
            fclose(arquivo);
            return 0;
        }

        Produto item;
        memset(&item, 0, sizeof(Produto));

        char *token = strtok(linha, ";");
        if (!token) {
            continue;
        }
        item.id = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        strncpy(item.nome, token, MAX_NOME - 1);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        item.preco = strtod(token, NULL);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        item.estoque = (int)strtol(token, NULL, 10);

        buffer[usados++] = item;
    }

    fclose(arquivo);

    if (usados == 0U) {
        free(buffer);
        buffer = NULL;
    } else {
        Produto *reduzido = realloc(buffer, usados * sizeof(Produto));
        if (reduzido) {
            buffer = reduzido;
        }
    }

    *produtos = buffer;
    *quantidade = usados;
    return 1;
}

static int carregar_pedidos_impl(Pedido **pedidos, size_t *quantidade, const char *caminho) {
    if (!pedidos || !quantidade) {
        return 0;
    }
    *pedidos = NULL;
    *quantidade = 0U;
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        return 1;
    }

    Pedido *buffer = NULL;
    size_t capacidade = 0U;
    size_t usados = 0U;
    char linha[512];

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '\0' || linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }
        if (!garantir_capacidade((void **)&buffer, &capacidade, usados, sizeof(Pedido))) {
            free(buffer);
            fclose(arquivo);
            return 0;
        }

        Pedido item;
        memset(&item, 0, sizeof(Pedido));

        char *token = strtok(linha, ";");
        if (!token) {
            continue;
        }
        item.id = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        item.clienteId = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        item.produtoId = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        item.quantidade = (int)strtol(token, NULL, 10);

        token = strtok(NULL, ";");
        if (!token) {
            continue;
        }
        limpar_trailing(token);
        strncpy(item.status, token, MAX_STATUS - 1);

        buffer[usados++] = item;
    }

    fclose(arquivo);

    if (usados == 0U) {
        free(buffer);
        buffer = NULL;
    } else {
        Pedido *reduzido = realloc(buffer, usados * sizeof(Pedido));
        if (reduzido) {
            buffer = reduzido;
        }
    }

    *pedidos = buffer;
    *quantidade = usados;
    return 1;
}

int salvar_clientes(const Cliente *clientes, size_t quantidade) {
    if (!clientes && quantidade > 0U) {
        return 0;
    }
    FILE *arquivo = fopen(ARQ_CLIENTES, "w");
    if (!arquivo) {
        return 0;
    }
    for (size_t i = 0U; i < quantidade; ++i) {
        if (fprintf(arquivo, "%d;%s;%s;%s\n",
                    clientes[i].id,
                    clientes[i].nome,
                    clientes[i].endereco,
                    clientes[i].telefone) < 0) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

int carregar_clientes(Cliente **clientes, size_t *quantidade) {
    return carregar_clientes_impl(clientes, quantidade, ARQ_CLIENTES);
}

int salvar_produtos(const Produto *produtos, size_t quantidade) {
    if (!produtos && quantidade > 0U) {
        return 0;
    }
    FILE *arquivo = fopen(ARQ_PRODUTOS, "w");
    if (!arquivo) {
        return 0;
    }
    for (size_t i = 0U; i < quantidade; ++i) {
        if (fprintf(arquivo, "%d;%s;%.2f;%d\n",
                    produtos[i].id,
                    produtos[i].nome,
                    produtos[i].preco,
                    produtos[i].estoque) < 0) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

int carregar_produtos(Produto **produtos, size_t *quantidade) {
    return carregar_produtos_impl(produtos, quantidade, ARQ_PRODUTOS);
}

int salvar_pedidos(const Pedido *pedidos, size_t quantidade) {
    if (!pedidos && quantidade > 0U) {
        return 0;
    }
    FILE *arquivo = fopen(ARQ_PEDIDOS, "w");
    if (!arquivo) {
        return 0;
    }
    for (size_t i = 0U; i < quantidade; ++i) {
        if (fprintf(arquivo, "%d;%d;%d;%d;%s\n",
                    pedidos[i].id,
                    pedidos[i].clienteId,
                    pedidos[i].produtoId,
                    pedidos[i].quantidade,
                    pedidos[i].status) < 0) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

int carregar_pedidos(Pedido **pedidos, size_t *quantidade) {
    return carregar_pedidos_impl(pedidos, quantidade, ARQ_PEDIDOS);
}
