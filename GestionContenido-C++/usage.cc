#include "usage.h"

void Usage(int argc, char* argv[]) {
  if (argc > 1) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    }
    std::cout << "Sistemas de recomendación. Modelos Basados en el Contenido\n\
    Modo de uso: '"
              << argv[0] << "'\n\
    Pruebe " << argv[0]
              << " --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
}