#ifndef USAGE_H_
#define USAGE_H_

#include <iostream>

const std::string kHelpText =
    "\n./main -- Sistemas de recomendación. Modelos Basados en el Contenido \n\
  Modo de uso: ./main \n\
    => ./main: Fichero main donde se encuentra las operaciones del modelo.\n";

void Usage(int argc, char *argv[]);

#endif