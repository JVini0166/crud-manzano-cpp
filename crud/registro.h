#include <iostream>
#include <cstring>
#include <fstream>
#include <conio.h>
#include "manzano.h"

using namespace std;

struct {
    char cargo[11];
    char nome[41];
    char cpf[12];
    char telefone[16];
    char endereco[60];
    char status[2];

} funcionario;

char auxnome[41];
char auxcpf[13];

void criarArquivo(void) {
    fstream arquivo;
    arquivo.open("empresa.db", ios_base::out | ios_base::binary);
    arquivo.close();
}

void pausa(short status) {
    if (status)
        cout << " Concluido com sucesso. ";
    cout << "Pressione <Enter> para continuar... ";
    cin.get();
}

char upper(char e) {


    return (97 <= e && e <= 122) ? e - 32 : e;
}

void lerstr(char *s) {
    char c;
    int pos = 0;
    do {
        c = upper(getch());
        if (isprint(c)) {
            cout << c;
            *s++ = c;
            ++pos;
        } else if (c == 8 && pos) {
            cout << "\b \b";
            --pos;
            --s;
        }
    } while (c != 13);
    *s = '\0';
}

int encontraPosicao(char *pesq) {
    fstream arquivo("empresa.db", ios_base::in | ios_base::binary);
    unsigned int pos = -1, contador = 0;
    bool encontrado = false;
    while (not arquivo.eof() and not encontrado) {
        arquivo.read(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
        if (strcmp(pesq, funcionario.nome) == 0 and funcionario.status[0] == '1') {
            encontrado = true;
            pos = contador;
        }
        contador++;
    }
    arquivo.flush();
    arquivo.close();
    return pos;
}

void excluirPessoa(int pos) {

    strcpy(funcionario.status, "0");
    fstream arquivo("empresa.db", ios_base::in | ios_base::out | ios_base::binary);
    arquivo.seekp(pos * sizeof(funcionario));
    arquivo.write(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
    arquivo.flush();
    arquivo.close();
}

void alteraNome(int pos) {
    lerstr(auxnome);
    strcpy(funcionario.nome, auxnome);
    fstream arquivo("empresa.db", ios_base::in | ios_base::out | ios_base::binary);
    arquivo.seekp(pos * sizeof(funcionario));
    arquivo.write(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
    arquivo.flush();
    arquivo.close();
}

bool buscaNome(char *pesq) {
    fstream arquivo("empresa.db", ios_base::in | ios_base::binary);
    bool encontrado = false;
    while (not arquivo.eof() and not encontrado) {
        arquivo.read(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
        if (strcmp(pesq, funcionario.nome) == 0 and funcionario.status[0] == '1')
            encontrado = true;
    }
    arquivo.flush();
    arquivo.close();
    return encontrado;
}

bool buscaCpf(char *pesq) {
    fstream arquivo("empresa.db", ios_base::in | ios_base::binary);
    bool encontrado = false;
    while (not arquivo.eof() and not encontrado) {
        arquivo.read(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
        if (strcmp(pesq, funcionario.cpf) == 0 and funcionario.status[0] == '1')
            encontrado = true;
    }
    arquivo.flush();
    arquivo.close();
    return encontrado;
}

bool buscaCargo(char *pesq) {
    fstream arquivo("empresa.db", ios_base::in | ios_base::binary);
    bool encontrado = false;
    while (not arquivo.eof() and not encontrado) {
        arquivo.read(reinterpret_cast<char *>(&funcionario), sizeof(funcionario));
        if (strcmp(pesq, funcionario.cargo) == 0 and funcionario.status[0] == '1')
            encontrado = true;
    }
    arquivo.flush();
    arquivo.close();
    return encontrado;
}

void pesquisarNome(void) {
    limpa();

    cout << " Pesquisar registro por nome\n\n\n\n";
    cout << " Entre com o nome .......: ";
    lerstr(auxnome);
    cout << "\n\n";
    if (buscaNome(auxnome)) {
        cout << "Nome Funcionário: " << endl;
        cout << funcionario.nome << endl;
        cout << "Cargo: " << endl;
        cout << funcionario.cargo;
        cout << "Numero de telefone: " << endl;
        cout << funcionario.telefone << endl;
        cout << "CPF: " << endl;
        cout << funcionario.cpf << endl;
        cout << "Endereço: " << endl;
        cout << funcionario.endereco << endl;
    } else
        cout << "\n\n Registro nao encontrado. ";
    pausa(0);
}

void pesquisarCpf(void) {
    limpa();
    cout << " Pesquisar registro por CPF\n\n\n\n";
    cout << " Entre com o CPF (apenas numeros) .......: ";
    lerstr(auxcpf);
    cout << "\n\n";
    if (buscaCpf(auxcpf)) {
        cout << "Nome Funcionário: " << endl;
        cout << funcionario.nome << endl;
        cout << "Cargo:" << endl;
        cout << funcionario.cargo;
        cout << "Numero de telefone: " << endl;
        cout << funcionario.telefone << endl;
        cout << "CPF: " << endl;
        cout << funcionario.cpf << endl;
        cout << "Endereço: " << endl;
        cout << funcionario.endereco << endl;
    } else
        cout << "\n\n Registro nao encontrado. ";
    pausa(0);
}

void registrar(void) {
    int opcargo;
    bool existeHierarquia;

    cout << " Cadastrar registro\n\n\n";
    cout << " Entre com o nome:\n ";
    lerstr(funcionario.nome);
    cout << "\n\n";
    cout << "Entre com o CPF (apenas numeros): ";
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
            existeHierarquia = true;
            strcpy(funcionario.cargo, "GERENTE");
            break;
        case 2:
            if (buscaCargo("GERENTE")) {
                existeHierarquia = true;
                strcpy(funcionario.cargo, "SUPERVISOR");
            } else {
                cout << "\n\nNecessario cadastrar um GERENTE para poder cadastrar um SUPERVISOR" << endl;
            }
            break;
        case 3:
            if (buscaCargo("SUPERVISOR")) {
                existeHierarquia = true;
                strcpy(funcionario.cargo, "ATENDENTE");
            } else {
                cout << "\n\nNecessario cadastrar um SUPERVISOR para poder cadastrar um ATENDENTE" << endl;
            }
            break;
    }

    funcionario.status[0] = '1';
    if (existeHierarquia) {
        fstream arquivo;
        arquivo.open("empresa.db", ios_base::out | ios_base::app |
                                  ios_base::binary);
        arquivo.seekp(0,
                      ios::end);
        arquivo.write(reinterpret_cast<char *>(&funcionario),
                      sizeof(funcionario));
        arquivo.flush();
        arquivo.close();
        cout << "\n\n";
        pausa(1);
    } else {
        pausa(0);
    }
}

void remover(void) {
    limpa();
    char opcao;
    cout << " Remover registro\n\n\n\n";
    cout << " Entre com o nome .......: ";
    lerstr(auxnome);
    cout << "\n\n";
    if (buscaNome(auxnome)) {
        cout << " Telefone .....: " << funcionario.telefone << "\n\n\n\n";
        cout << " Remover cadastro [S]im ou [N]ao: ";
        cin >> opcao;
        cin.ignore(80, '\n');
        if (opcao == 'S' or opcao == 's') {
            excluirPessoa(encontraPosicao(auxnome));
            cout << "\n\n\n Cadastro removido. ";
        } else
            cout << "\n\n\n Cadastro nao removido. ";
    } else
        cout << "\n\n Registro nao encontrado. ";
    pausa(0);
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
        cin >> opcao;
        cin.ignore(80, '\n');
    } while (opcao != 1 and opcao != 2);
    if (opcao == 1) selecao = "nome";
    else selecao = "data";
//        limpa();
    cout << " Alterar " << selecao << " do registro\n\n\n";
    cout << endl;
    cout << " Entre com o nome:\n ";
    lerstr(auxnome);
    cout << "\n\n";
    if (buscaNome(auxnome)) {

        if (opcao == 1) {
            cout << " Telefone:\n ";
            cout << funcionario.telefone << "\n\n";
            cout << " Entre o novo nome:\n ";
            alteraNome(encontraPosicao(auxnome));
        } else {


        }
        cout << "\n\n\n\n";
        pausa(1);
    } else {
        cout << endl << "\n Registro nao encontrado. ";
        pausa(0);
    }
}
