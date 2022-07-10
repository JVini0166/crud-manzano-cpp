#include <iostream>
//#include "manzano.h"
using namespace std;

short menu(void) {
   short opcao;
   do {
//      limpa();                                                         // LIMPA A TELA E POSICIONA O CURSOR (SOMENTE WINDOWS)
      cout << " Menu Principal\n\n\n";
      cout << " [1] - Cadastrar registro.\n\n";
      cout << " [2] - Pesquisar registro por nome.\n\n";
      cout << " [3] - Pesquisar registro por cargo.\n\n";
      cout << " [4] - Remover registro.\n\n";
      cout << " [5] - Alterar registro.\n\n";
      cout << " [0] - Sair.\n\n";
      cout << " Entre a opcao desejada: ";
      cin >> opcao;
      cin.ignore(80, '\n');
   } while (opcao < 0 or 5 < opcao);                                   // EVITA OPCÃO INEXISTENTE
   return opcao;
}
