#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include "manzano.h"

using namespace std;

struct {                     // DEFINI��O DA CLASSE
    char cargo[11];                   // PARA SABER SE O CADASTRO EST� OU N�O ATIVO
    char nome[41];                 // NOME DA PESSOA
    char cpf[12];                 // DATA DE NASCIMENTO DA PESSOA
    char telefone[16];
    char endereco[60];
    char status[2];

} funcionario;

char pnome[41];

void pausa(short status) {                         // PARA PAUSAR PROGRAMA E EXIBIR MENSAGEM
    if (status)                                     // PARA ESCREVER A MENSAGEM ADICIONAL
        cout << " Concluido com sucesso. ";          // MENSAGEM ADICIONAL
    cout << "Pressione <Enter> para continuar... "; // MENSAGEM PADR�O
    cin.get();                                      // SOLICITA LEITURA DE CARACTERE PARA PAUSAR EXECU��O
}

char upper(char e) {                        // TRANSFORMA CARACTERE MIN�SCULO EM MAI�SCULO
    // SE 97 <= CARACTERE <= 122 ENT�O ELE � MIN�SCULO\
                                            // DIMINUINDO 32 CARACTERES DELE, � RETORNADA SUA VERS�O\
                                            // MAI�SCULA CORRESPONDENTE NA TABELA ASCII
    return (97 <= e && e <= 122) ? e-32 : e;
}

void lerstr(char *s) {          // CORRIGE A ENTRADA PARA CARACTERES MAI�SCULOS
    char c;                      // USADA PARA CADA CARACTERE LIDO
    int pos = 0;                 // QUANTIDADE DE CARACTERES LIDOS
    do {
        c = upper(getch());       // ARMAZENA O CARACTERE LIDO NA VARI�VEL c
        if (isprint(c)) {         // SE c FOR UM CARACTERE QUE PODE SER IMPRESSO
            cout << c;             // IMPRIME c NA TELA
            *s++ = c;              // ADICIONA c NA POSIS�O ATUAL DO PONTEIRO E VAI PARA PR�XIMA POSI��O
            ++pos;                 // AUMENTA A QUANTIDADE DE CARACTERES LIDOS
        }
        else if (c == 8 && pos) { // SE c FOR A TECLA <BACKSPACE>
            cout << "\b \b";       // APAGA O CARACTERE ANTERIOR
            --pos;                 // DIMINUI A QUANTIDADE DE CARACTERES LIDOS
            --s;                   // VOLTA UMA POSIÇÃO DO PONTEIRO
        }
    } while (c != 13);           // LER ENQUANTO O <Enter> NÃO FOR ACIONADO
    *s = '\0';                   // CARACTERE DE FINALIZAÇÃO DE UMA STRING
}

int encontraPosicao(char *pesq) {                                              // RETORNA A POSI��O DO REGISTRO NO ARQUIVO
    fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);              // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
    unsigned int pos = -1, contador = 0;                                        // POSI��O DO REGISTRO PROCURADO E QUANTIDADE DE REGISTROS NO ARQUIVO
    bool acha = false;                                                          // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
    while (not arquivo.eof() and not acha) {                                    // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
        arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(funcionario));  // INSERE OS DADOS DE UM REGISTRO NO OBJETO
        if (strcmp(pesq, funcionario.nome) == 0 and funcionario.status[0] == '1') { // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
            acha = true;                                                          // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
            pos = contador;                                                       // ARMAZENA A POSICAO DO REGISTRO
        }
        contador++;                                                              // INCREMENTA A QUANTIDADE DE REGISTROS
    }
    arquivo.flush();                                                            // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                            // FECHA O ARQUIVO
    return pos;                                                                 // RETORNA A POSI��O NA QUAL O REGISTRO EST� LOCALIZADO
}

void excluirPessoa(int pos) {                                                    // "EXCLUI" UM REGISTRO
    /// NA REALIDADE O REGISTRO N�O � EXCLU�DO, APENAS TEM O STATUS ALTERADO:
    strcpy(funcionario.status, "0");
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BIN�RIO
    arquivo.seekp(pos * sizeof(funcionario));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&funcionario), sizeof(funcionario));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

void alteraNome(int pos) {                                                        // ALTERA O NOME DE UM REGISTRO
    lerstr(pnome);                                                                // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
    strcpy(funcionario.nome, pnome);
    fstream arquivo("banco.dbc",ios_base::in | ios_base::out | ios_base::binary); // ABERTURA DO ARQUIVO PARA LEITURA E ESCRITA DE DADOS EM BIN�RIO
    arquivo.seekp(pos * sizeof(funcionario));                                          // POSICIONA O PONTEIRO NA POSICAO DO REGISTRO SOLICITADO
    arquivo.write(reinterpret_cast<char*>(&funcionario), sizeof(funcionario));      // GRAVA OS DADOS NO ARQUIVO NA POSI��O SELECIONADA
    arquivo.flush();                                                              // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                              // FECHA O ARQUIVO
}

bool buscaNome(char *pesq) {                                                  // INFORMA DE EXISTE UM NOME PESQUISADO
    fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
    bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
    while (not arquivo.eof() and not acha) {                                   // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
        arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(funcionario)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
        if (strcmp(pesq, funcionario.nome) == 0 and funcionario.status[0] == '1')  // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
            acha = true;                                                         // "LEVANTA A FLAG" POIS ENCONTROU O REGISTRO
    }
    arquivo.flush();                                                           // ESVAZIA O BUFFER DE SA�DA PARA O ARQUIVO
    arquivo.close();                                                           // FECHA O ARQUIVO
    return acha;                                                               // RETORNA SE ACHOU OU N�O O REGISTRO PROCURADO
}

void pesquisarNome(void) {                                               // PESQUISA POR NOME E EXIBE O REGISTRO
    limpa();                                                              // LIMPA A TELA E POSICIONA O CURSOR

    cout << " Pesquisar registro por nome\n\n\n\n";
    cout << " Entre com o nome .......: ";
    lerstr(pnome);                                                        // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
    cout << "\n\n";
    if (buscaNome(pnome)) {                                               // SE ENCONTROU O REGISTRO
    cout << "Nome Funcionário: " << endl;
    cout << funcionario.nome << endl;
    cout << "Cargo:" << endl;
    cout << funcionario.cargo;
    cout << "Numero de telefone: " <<endl;
    cout << funcionario.telefone << endl;
    cout << "CPF: " << endl;
    cout << funcionario.cpf << endl;
    cout << "Endereço: " << endl;
    cout << funcionario.endereco << endl;
    }
    else                                                                  // SE N�O ENCONTROU O REGISTRO
        cout << "\n\n Registro nao encontrado. ";
    pausa(0);                                                             // PAUSA SEM MENSAGEM ADICIONAL
}

void registrar(void) {
    int opcargo;

    cout << " Cadastrar registro\n\n\n";
    cout << " Entre com o nome:\n ";
    lerstr(funcionario.nome);
    cout << "\n\n";
    cout << "Entre com o CPF: "; //verificação cpf
    cin >> funcionario.cpf;
    cout << "Entre com o telefone: ";
    cin >> funcionario.telefone;
    cout << "Entre com o endereco: ";
    lerstr(funcionario.endereco);
    cout << " Entre com o cargo:\n ";
    cout << " [1] Gerente " << endl;
    cout << " [2] Supervisor " << endl;
    cout << " [3] Atendente " << endl;
    cin >> opcargo;

    switch (opcargo) {
        case 1:
            strcpy(funcionario.cargo, "GERENTE"); break;
        case 2:
            strcpy(funcionario.cargo, "SUPERVISOR"); break;
        case 3:
            strcpy(funcionario.cargo, "ATENDENTE"); break;
    }

    funcionario.status[0] = '1';

    fstream arquivo;
    arquivo.open("banco.dbc", ios_base::out | ios_base::app |
                              ios_base::binary);
    arquivo.seekp(0,
                  ios::end);
    arquivo.write(reinterpret_cast<char *>(&funcionario),
                  sizeof(funcionario));
    arquivo.flush();
    arquivo.close();
    cout << "\n\n";
    pausa(1);
}

void remover(void) {                                                           // REMOVE UM REGISTRO
    limpa();                                                                    // LIMPA A TELA E POSICIONA O CURSOR
    char opcao;                                                                 // ARMAZENA A OPCAO DO MENU
    cout << " Remover registro\n\n\n\n";
    cout << " Entre com o nome .......: ";
    lerstr(pnome);                                                              // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
    cout << "\n\n";
    if (buscaNome(pnome)) {                                                     // SE ENCONTROU O REGISTRO
        cout << " Telefone .....: " << funcionario.telefone << "\n\n\n\n"; // ESCREVE A DATA DE NASCIMENTO
        cout << " Remover cadastro [S]im ou [N]ao: ";
        cin >> opcao;                                                            // LEITURA DA OP��O DESEJADA
        cin.ignore(80, '\n');                                                    // LIMPA BUFFER DO TECLADO
        if (opcao == 'S' or opcao == 's') {                                      // SE FOR [S/s]IM
            excluirPessoa(encontraPosicao(pnome));                                // CHAMADA DA SUB-ROTINA PARA EXCLUS�O
            cout << "\n\n\n Cadastro removido. ";
        }
        else                                                                     // SE FOR QUALQUER OUTRO CARACTERE
            cout << "\n\n\n Cadastro nao removido. ";
    }
    else                                                                        // SE N�O ENCONTROU O REGISTRO
        cout << "\n\n Registro nao encontrado. ";
    pausa(0);                                                                   // PAUSA SEM MENSAGEM ADICIONAL
}

void alterar(void) {
    short opcao;
    string selecao;
    do {
//        limpa();
        cout << " Alterar registro\n\n\n";
        cout << " Selecione a opcao:\n\n";
        cout << " [1] - Alterar nome.\n\n";
        cout << " [2] - Alterar data de nascimento.\n\n\n";
        cout << " Entre a opcao desejada: ";
        cin >> opcao;                                                     // LEITURA DA OP��O DESEJADA
        cin.ignore(80, '\n');                                             // LIMPA BUFFER DO TECLADO
    } while (opcao != 1 and opcao != 2);                                 // EVITA OPC�O INEXISTENTE
    if (opcao == 1) selecao = "nome";                                    // PERSONALIZA OP��O PARA ALTERA��O DE NOME
    else selecao = "data";                                               // PERSONALIZA OP��O PARA ALTERA��O DE DATA
//    limpa();                                                             // LIMPA A TELA E POSICIONA O CURSOR
    cout << " Alterar " << selecao << " do registro\n\n\n";
    cout << endl;
    cout << " Entre com o nome:\n ";
    lerstr(pnome);                                                       // ENTRADA FORMATADA PARA CARACTERES MAI�SCULOS
    cout << "\n\n";
    if (buscaNome(pnome)) {                                              // SE ENCONTROU O REGISTRO
        /// NESSE MOMENTO OS DADOS CORRETOS EST�O NOS ATRIBUTOS DO OBJETO
        if (opcao == 1) {                                                 // SE FOI SOLICITADA A ALTERA��O DE NOME
            cout << " Telefone:\n ";
            cout << funcionario.telefone << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
            cout << " Entre o novo nome:\n ";
            alteraNome(encontraPosicao(pnome));                            // EFETUA A ALTERA��O DO NOME
        } else {                                                          // SE FOI SOLICITADA A ALTERA��O DE NOME
//            cout << " Telefone::\n ";
//            cout << funcionario.telefone << "\n\n";                            // EXIBE A DATA DE NASCIMENTO
//            cout << " Entre a nova data de nascimento:\n ";
//            alteraData(encontraPosicao(pnome));                            // EFETUA A ALTERA��O DA DATA
        }
        cout << "\n\n\n\n";
        pausa(1);                                                         // PAUSA COM MENSAGEM ADICIONAL
    }
    else {                                                               // SE N�O ENCONTROU O REGISTRO
        cout << endl << "\n Registro nao encontrado. ";
        pausa(0);                                                         // PAUSA SEM MENSAGEM ADICIONAL
    }
}