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
    char status;

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

bool buscaNome(char *pesq) {                                                  // INFORMA DE EXISTE UM NOME PESQUISADO
    fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);             // ABERTURA DO ARQUIVO PARA LEITURA DE DADOS EM BIN�RIO
    bool acha = false;                                                         // FLAG "LEVANTADA" QUANDO O REGISTRO � ENCONTRADO
    while (not arquivo.eof() and not acha) {                                   // ENQUANTO N�O CHEGOU AO FINAL DO ARQUIVO E N�O ENCONTROU
        arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(funcionario)); // INSERE OS DADOS DE UM REGISTRO NO OBJETO
        if (strcmp(pesq, funcionario.nome) == 0 and funcionario.status == '1')  // SE O NOME PROCURADO CORRESPONDE AO REGISTRO E ESSE EST� ATIVO
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
        /// NESSE MOMENTO OS DADOS CORRETOS EST�O NOS ATRIBUTOS DO OBJETO
//        cout << " Data de nascimento .....: " << pessoa.getData() << " ("; // ESCREVE A DATA DE NASCIMENTO
//        escreveSemana(pessoa.getData());                                   // ESCREVE O DIA DA SEMANA DA DATA
//        cout << ")\n\n";
//        cout << " Data atual do sistema ..: " << dataAtual() << " (";      // ESCREVE A DATA ATUAL DO SISTEMA
//        escreveSemana(dataAtual());                                        // ESCREVE O DIA DA SEMANA DA DATA
//        cout << ")\n\n";
//        cout << " Idade ..................: ";
//        escreveIdade(calcData(pessoa.getData()));                          // ESCREVE IDADE EM DIA(S), MES(ES) E ANO(S)
//        cout << "\n\n\n\n ";
    cout << "Nome Funcionário: " << endl;
    cout << funcionario.nome;
    cout << funcionario.cargo;
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

    funcionario.status = '1';

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