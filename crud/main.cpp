#include <iostream>
#include <fstream>
#include "menu.h"
#include "registro.h"
using namespace std;

int main(void) {

   short funcaoMenu;

   fstream banco("empresa.dbc", ios_base::in | ios_base::binary);

   if(banco.fail())
      criarArquivo();
   do {
      funcaoMenu = menu();
      switch(funcaoMenu) {
          case 0: return 0;              break;
          case 1: registrar();           break;
          case 2: pesquisarNome();       break;
          case 3: pesquisarCpf();        break;
          case 4: remover();             break;
          case 5: alterar();             break;
      }
   } while (funcaoMenu);

   banco.close();
   return 0;
}
