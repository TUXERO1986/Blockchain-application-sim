#include <iostream>
#include <iomanip>
#include "Blockchain.h"

void imprimirCadena(const Blockchain& bc, Blockchain& bcRef) {
    std::cout << "\n--- ESTADO DE LA CADENA ---\n";
    for (size_t i = 0; i < bcRef.size(); i++) {
        const Block* b = bcRef.getBlockAt(i);
        std::cout << "Bloque #" << b->getIndex() << "\n";
        std::cout << "  Data  : " << b->getData() << "\n";
        std::cout << "  Nonce : " << b->getNonce() << "\n";
        std::cout << "  Prev  : " << b->getPreviousHash().substr(0, 16) << "...\n";
        std::cout << "  Hash  : " << b->getHash().substr(0, 16) << "...\n\n";
    }
}

void verificar(const Blockchain& bc) {
    std::cout << ">> isChainValid() = "
              << (bc.isChainValid() ? "TRUE  (cadena intacta)"
                                    : "FALSE (manipulacion detectada)")
              << "\n";
}

int main() {

    std::cout << "=== FASE A: construccion de la cadena ===\n";

    Blockchain bc;
    std::cout << "Genesis creado.\n";

    std::cout << "Minando bloque 1...\n";
    bc.addBlock("{\"lote\":\"HP-2201\",\"planta\":\"Chimbote\",\"kg\":12500}");

    std::cout << "Minando bloque 2...\n";
    bc.addBlock("{\"lote\":\"HP-2202\",\"planta\":\"Chimbote\",\"kg\":9800}");

    imprimirCadena(bc, bc);
    verificar(bc);


    std::cout << "\n=== FASE B: ataque de manipulacion de datos ===\n";
    std::cout << "Un atacante altera los kilos del bloque 1...\n";

    Block* victima = bc.getBlockAt(1);
    std::cout << "  ANTES : " << victima->getData() << "\n";

    victima->tamperData("{\"lote\":\"HP-2201\",\"planta\":\"Chimbote\",\"kg\":99999}");

    std::cout << "  AHORA : " << victima->getData() << "\n";
    std::cout << "  El hash guardado NO cambio: "
              << victima->getHash().substr(0, 16) << "...\n";
    std::cout << "  El hash recalculado ES    : "
              << victima->calculateHash().substr(0, 16) << "...\n\n";

    verificar(bc);

    return 0;
}