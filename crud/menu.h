#include <iostream>
using namespace std;

short menu(void) {
   short opcao;
   do {
//      limpa();
      cout << " Menu Principal\n\n\n";
      cout << " [1] - Cadastrar registro.\n\n";
      cout << " [2] - Pesquisar registro por nome.\n\n";
      cout << " [3] - Pesquisar registro por CPF. \n\n";
      cout << " [4] - Remover registro.\n\n";
      cout << " [5] - Alterar registro.\n\n";
      cout << " [0] - Sair.\n\n";
      cout << " Entre a opcao desejada: ";
      cin >> opcao;
      cin.ignore(80, '\n');
   } while (opcao < 0 or 5 < opcao);
   return opcao;
}
