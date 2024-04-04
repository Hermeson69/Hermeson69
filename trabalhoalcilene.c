#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// DEFENINDO TODOS OS TAMANHOS DO STRUCT UTILIZANDO O DEFINE.
#define MAX_MEDICAMENTOS 200
#define MAX_NOME 100
#define MAX_DATA 12
#define USE 100
#define MAX_USE 100
#define MAX_SENHA 8
#define MAX_HISTORICO_SAIDA 500
// STRUCT PRINCIPAL
struct Medicamento
{
    char nome[MAX_NOME];
    int lote;
    char fabricacao[MAX_DATA];
    char vencimento[MAX_DATA];
    int quantidade;
};

struct usuario
{
    char nome_use[MAX_USE];
    int senha[MAX_SENHA];
};

struct HistoricoSaida
{
    char nome[MAX_NOME];
    int lote;
    char data[MAX_DATA];
    int quantidadeRetirada; // Quantidade retirada
    int quantidadeInicial;  // Quantidade inicial antes da retirada
    int quantidadeFinal;
};


void limparBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}



// Função para cadastrar um novo usuário
void cadastrarUsuario(struct usuario *usuarios, int *numUsuarios)
{
    if (*numUsuarios < MAX_USE)
    {
        printf("Cadastro de Novo Usuário:\n");

        printf("Nome: ");
        fgets(usuarios[*numUsuarios].nome_use, sizeof(usuarios[*numUsuarios].nome_use), stdin);
        limparBuffer();

        printf("Senha: ");
        fgets(usuarios[*numUsuarios].senha, sizeof(usuarios[*numUsuarios].senha), stdin);
        limparBuffer();

        (*numUsuarios)++;
        printf("Usuário cadastrado com sucesso!\n");
    }
    else
    {
        printf("Limite de usuários atingido!\n");
    }
}


// Função para remover um usuário
void removerUsuario(struct usuario *usuarios, int *numUsuarios)
{
    // SOLICITA O NOME DO MEDICAMENTO A SER REMOVIDO
    char nomeBusca[MAX_USE];
    printf("Digite o nome do Usuario a buscar:\n");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparBuffer();

    // BUSCA NA LISTA
    for (int i = 0; i < *numUsuarios; i++)
    {
        // CASO FOR EMCONTRADO
        if (strcmp(usuarios[i].nome_use, nomeBusca) == 0)
        {
            // REMOVE O MEDICAMENTO MOVENDO TODOS OS ELEMENTOS PARA NÃO FICAR ESPAÇO VAZIO NA LISTA
            for (int j = i; j < *numUsuarios - 1; j++)
            {
                usuarios[j] = usuarios[j + 1];
            }
            // REDUZ O numUsuarios DA LISTA
            (*numUsuarios)--;
            return;
        }
    }
}

// FUNÇÃO PARA EXIBIR O MENU
void exibirMenu()
{
    printf("----------------------------------------------\n");
    printf("Sistema de Cadastro de Medicamentos\n");
    printf("----------------------------------------------\n");
    printf("1 - Cadastrar medicamento\n");
    printf("2 - Listar medicamentos\n");
    printf("3 - Buscar medicamento\n");
    printf("4 - Alterar Informacoes\n");
    printf("5 - Pegar Produto\n");
    printf("6 - Excluir Porduto\n");
    printf("7 - Lista de saida de produto\n");
    printf("8 - Cadastro de novo usuario\n");
    printf("9 - Remover Usuario\n");
    printf("10 - Sair\n");
}
// MENSAGEM DE CADASTRO
void mensagemCadastroSucesso()
{
    printf("Medicamento cadastrado com sucesso!\n");
}
// MENSAGEM DE SUCESSO AO EXCLUIR
void mensagemExclusaoSucesso()
{
    printf("Medicamento excluido com sucesso!\n");
}
// MENSAGEM DE MEDICAMENTO NÃO EMCONTRADO
void mensagemNaoEncontrado()
{
    printf("Medicamento nao encontrado!\n");
}

// Função para validar a data
int validarData(int ano, int mes, int dia)
{
    time_t t = time(NULL);
    struct tm hoje = *localtime(&t);

    if (ano < hoje.tm_year + 1900)
        return 0;

    if (ano == hoje.tm_year + 1900 && mes < hoje.tm_mon + 1)
        return 0;

    if (ano == hoje.tm_year + 1900 && mes == hoje.tm_mon + 1 && dia < hoje.tm_mday)
        return 0;

    return 1;
}

// Função de cadastro de medicamento
void cadastrarMedicamento(struct Medicamento *medicamentos, int *tamanho)
{
    if (*tamanho < MAX_MEDICAMENTOS)
    {
        printf("Cadastro de um Novo Medicamento:\n");
        printf("Nome: ");
        fgets(medicamentos[*tamanho].nome, sizeof(medicamentos[*tamanho].nome), stdin);
        limparBuffer();
        printf("Lote: ");
        scanf("%d", &medicamentos[*tamanho].lote);
        limparBuffer();

        // Solicitar e validar a data de fabricação
        do
        {
            printf("Fabricacao (AAAA-MM-DD): ");
            scanf("%10s", medicamentos[*tamanho].fabricacao);
            
        } while (!validarData(atoi(medicamentos[*tamanho].fabricacao), atoi(medicamentos[*tamanho].fabricacao + 5), atoi(medicamentos[*tamanho].fabricacao + 8)));
        limparBuffer();

        // Solicitar e validar a data de vencimento
        do
        {
            printf("Vencimento (AAAA-MM-DD): ");
            scanf("%10s", medicamentos[*tamanho].vencimento);
           
        } while (!validarData(atoi(medicamentos[*tamanho].vencimento), atoi(medicamentos[*tamanho].vencimento + 5), atoi(medicamentos[*tamanho].vencimento + 8)));
        limparBuffer();

        printf("Quantidade: ");
        scanf("%d", &medicamentos[*tamanho].quantidade);
        limparBuffer();

        (*tamanho)++;
        printf("Cadastro realizado com sucesso!\n");
    }
    else
    {
        printf("Limite de medicamentos atingido!\n");
    }
}

void listarMedicamentos(struct Medicamento *medicamentos, int tamanho)
{

    // BASICAMENTE VAI PUXAR TODOS OS ITENS CADASTRADOS;
    printf("\nMedicamentos encontrados:\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("Medicamento %d:\n", i + 1);
        printf("Nome: %s\n", medicamentos[i].nome);
        printf("Lote: %d\n", medicamentos[i].lote);
        printf("Fabricacao: %s\n", medicamentos[i].fabricacao);
        printf("Vencimento: %s\n", medicamentos[i].vencimento);
        printf("Quantidade: %d\n\n", medicamentos[i].quantidade);
    }

    if (tamanho == 0)
    {
        printf("Nem um Produto Cadastrado! \n");
    }
}

void buscarMedicamento(struct Medicamento *medicamentos, int tamanho)
{
    // NESSA PRIMEIRA PARTE O ÚSUARIO VAI DIGITAR UM NOME E CASO NO STRUCT TENHA ALGO COM O MESMO NOME SERA PUXADO PARA A TELA;
    char nomeBusca[MAX_NOME];
    printf("Digite o nome do medicamento a buscar:\n");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparBuffer();

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(medicamentos[i].nome, nomeBusca) == 0)
        {
            printf("Medicamento encontrado:\n");
            printf("Nome: %s\n", medicamentos[i].nome);
            printf("Lote: %d\n", medicamentos[i].lote);
            printf("Fabricacao: %s\n", medicamentos[i].fabricacao);
            printf("Vencimento: %s\n", medicamentos[i].vencimento);
            printf("Quantidade: %d\n\n", medicamentos[i].quantidade);
            return;
        }
    }
    // CASO O NOME DIGITADO NÃO EXISTA NO STRUCT, EXIBE ESSA IMAGEM;
    mensagemNaoEncontrado();
}

void alterarMedicamento(struct Medicamento *medicamentos, int tamanho)
{
    // SEGUIE A MESMA LOGICA DA FUNÇÃO ACIMA, O ÚSUARIO VAI DIGITAR UM NOME E CASO ELE SEJA EMCONTRADO VAI EXIBIR UM MENU DE ALTERÇÃO
    // OMDE PODE-SE MUDAR QUALQUER INFORMAÇÃO DO PRODUTO;
    char nomeBusca[MAX_NOME];
    printf("Digite o nome do medicamento a buscar:\n");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparBuffer();

    for (int i = 0; i < tamanho; i++)
    {
        if (strcmp(medicamentos[i].nome, nomeBusca) == 0)
        {
            printf("----------------------------------------------\n");
            printf("Alterar Cadastro do Medicamneto: %s", medicamentos[i].nome);
            printf("\n----------------------------------------------\n");
            printf("1 - Nome\n");
            printf("2 - Lote\n");
            printf("3 - Fabricacao\n");
            printf("4 - Vencimento\n");
            printf("5 - Quantidade\n");
            int opcao;
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao)
            {
            case 1:
                printf("Digite o novo nome: ");
                fgets(medicamentos[i].nome, sizeof(medicamentos[i].nome), stdin);
                limparBuffer();
                break;
            case 2:
                printf("Digite o novo lote: ");
                scanf("%d", &medicamentos[i].lote);
                limparBuffer();
                break;
            case 3:
                printf("Digite a nova data de fabricacao: ");
                scanf("%9s", medicamentos[i].fabricacao);
                limparBuffer();
                break;
            case 4:
                printf("Digite a nova data de vencimento: ");
                scanf("%9s", medicamentos[i].vencimento);
                limparBuffer();
                break;
            case 5:
                printf("Digite a nova quantidade: ");
                scanf("%d", &medicamentos[i].quantidade);
                limparBuffer();
                break;
            default:
                printf("Opcao invalida!\n");
            }

            mensagemCadastroSucesso();
            return;
        }
    }

    mensagemNaoEncontrado();
}

// Função para pegar produto
void pegarProduto(struct Medicamento *medicamentos, int tamanho, struct HistoricoSaida *historicoSaida, int *tamanhoHistoricoSaida)
{
    char nomeProcurado[MAX_NOME];
    int quantidadeRetirar;

    printf("Digite o nome do produto que deseja pegar: ");
    fgets(nomeProcurado, sizeof(nomeProcurado), stdin);
    int i;

    for (i = 0; i < tamanho; i++)
    {
        if (strcmp(medicamentos[i].nome, nomeProcurado) == 0)
        {
            printf("Informacoes do Produto:\n");
            printf("Nome: %s\n", medicamentos[i].nome);
            printf("Lote: %d\n", medicamentos[i].lote);
            printf("Fabricacao: %s\n", medicamentos[i].fabricacao);
            printf("Vencimento: %s\n", medicamentos[i].vencimento);
            printf("Quantidade disponivel: %d\n", medicamentos[i].quantidade);

            // Solicita a quantidade a ser retirada
            printf("Digite a quantidade que deseja pegar: ");
            scanf("%d", &quantidadeRetirar);
            getchar(); // Limpar o caractere de nova linha do buffer.

            // Verifica se há quantidade suficiente para retirar
            if (quantidadeRetirar <= medicamentos[i].quantidade && quantidadeRetirar > 0)
            {
                // Preenche o histórico de saída
                strcpy(historicoSaida[*tamanhoHistoricoSaida].nome, nomeProcurado);
                historicoSaida[*tamanhoHistoricoSaida].lote = medicamentos[i].lote;
                strcpy(historicoSaida[*tamanhoHistoricoSaida].data, "18/01/2024"); // Você pode substituir pela data atual real
                historicoSaida[*tamanhoHistoricoSaida].quantidadeRetirada = quantidadeRetirar;
                historicoSaida[*tamanhoHistoricoSaida].quantidadeInicial = medicamentos[i].quantidade;
                historicoSaida[*tamanhoHistoricoSaida].quantidadeFinal = historicoSaida[*tamanhoHistoricoSaida].quantidadeInicial - historicoSaida[*tamanhoHistoricoSaida].quantidadeRetirada;
                (*tamanhoHistoricoSaida)++;

                // Atualiza a quantidade no estoque
                medicamentos[i].quantidade -= quantidadeRetirar;
                printf("Produto retirado com sucesso!\n");
            }
            else
            {
                printf("Quantidade inválida ou insuficiente!\n");
            }

            return; // Encerra a função após o processamento do produto encontrado
        }
    }

    // Se o loop for concluído e nenhum produto correspondente for encontrado
    printf("Produto não encontrado!\n");
}

void registrarSaida(struct HistoricoSaida *historicoSaida, int tamanhoHistoricoSaida)
{
    printf("\nHistorico de Saida:\n");
    for (int i = 0; i < tamanhoHistoricoSaida; i++)
    {
        printf("Produto: %s\nLote: %d\nData: %s\nQuantidade Retirada: %d\nQuantidade Inicial: %d\nQuantidade Final: %d\n\n",
               historicoSaida[i].nome, historicoSaida[i].lote, historicoSaida[i].data,
               historicoSaida[i].quantidadeRetirada, historicoSaida[i].quantidadeInicial, historicoSaida[i].quantidadeFinal);
    }

    if (tamanhoHistoricoSaida == 0)
    {
        printf("Nenhuma saída registrada.\n");
    }
}
void removerMedicamento(struct Medicamento *medicamentos, int *tamanho)
{
    // SOLICITA O NOME DO MEDICAMENTO A SER REMOVIDO
    char nomeBusca[MAX_NOME];
    printf("Digite o nome do medicamento a buscar:\n");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    limparBuffer();

    // BUSCA NA LISTA
    for (int i = 0; i < *tamanho; i++)
    {
        // CASO FOR EMCONTRADO
        if (strcmp(medicamentos[i].nome, nomeBusca) == 0)
        {
            // REMOVE O MEDICAMENTO MOVENDO TODOS OS ELEMENTOS PARA NÃO FICAR ESPAÇO VAZIO NA LISTA
            for (int j = i; j < *tamanho - 1; j++)
            {
                medicamentos[j] = medicamentos[j + 1];
            }
            // REDUZ O TAMANHO DA LISTA
            (*tamanho)--;
            mensagemExclusaoSucesso();
            return;
        }
    }
    // CASO O MEDICAMENTO NÃO FOR EMCONTRADO, EXIBE ESSA MENDAGEM.
    mensagemNaoEncontrado();
}

int main()
{
    struct Medicamento listaMedicamentos[MAX_MEDICAMENTOS];
    struct usuario listause[MAX_USE];
    struct HistoricoSaida historicoSaida[MAX_HISTORICO_SAIDA];
    int opcao, tamanhoMedicamentos = 0, tamanhoUsuarios = 0, tamanhoHistoricoSaida = 0;
    char name_manager[100];

    printf("Manager: ");
    fgets(name_manager, sizeof(name_manager), stdin);
    system("cls||clear");

    do
    {

        printf("%s", name_manager);

        exibirMenu();
        printf("Quantidade de medicamentos cadastrados: %d\n", tamanhoMedicamentos);
        printf("Escolha a opcao:\n");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            system("cls||clear");
            cadastrarMedicamento(listaMedicamentos, &tamanhoMedicamentos);
            system("PAUSE");
            system("cls||clear");
            break;
        case 2:
            system("cls||clear");
            listarMedicamentos(listaMedicamentos, tamanhoMedicamentos);
            system("PAUSE");
            system("cls||clear");
            break;
        case 3:
            system("cls||clear");
            buscarMedicamento(listaMedicamentos, tamanhoMedicamentos);
            system("PAUSE");
            system("cls||clear");
            break;
        case 4:
            system("cls||clear");
            alterarMedicamento(listaMedicamentos, tamanhoMedicamentos);
            system("PAUSE");
            system("cls||clear");
            break;
        case 5:
            system("cls||clear");
            pegarProduto(listaMedicamentos, tamanhoMedicamentos, historicoSaida, &tamanhoHistoricoSaida);
            system("PAUSE");
            system("cls||clear");
            break;
        case 6:
            system("cls||clear");
            removerMedicamento(listaMedicamentos, &tamanhoMedicamentos);
            system("PAUSE");
            system("cls||clear");
            break;
        case 7:
            system("cls||clear");
            registrarSaida(historicoSaida, tamanhoHistoricoSaida);
            system("PAUSE");
            system("cls||clear");
            break;
        case 8:
            system("cls||clear");
            cadastrarUsuario(listause, &tamanhoUsuarios);
            system("PAUSE");
            system("cls||clear");
            break;
        case 9:
            system("cls||clear");
            removerUsuario(listause, &tamanhoUsuarios);
            system("PAUSE");
            break;
        case 10:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida tente novamente\n");
        }

    } while (opcao != 10);

    return 0;
}