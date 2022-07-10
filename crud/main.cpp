#include <iostream>
#include <fstream>
#include "menu.h"
#include "registro.h"
using namespace std;

int main(void) {
   short opcao;

//   fstream arquivo("banco.dbc", ios_base::in | ios_base::binary);

//   if(arquivo.fail())
//      criarArquivo();
   do {
      opcao = menu();
      switch(opcao) {
         case 1: registrar();    break;
         case 2: pesquisarNome();       break;
         case 3: return 0;       break;
         case 4: return 0;       break;
         case 5: return 0;       break;
      }
   } while (opcao);

//   arquivo.close();
   return 0;
}
