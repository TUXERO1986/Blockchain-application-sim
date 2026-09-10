#include "Blockchain.h"

Blockchain::Blockchain(){
    difficulty=4;
    chain.push_back(std::make_unique<Block>(0, "Genesis Block", std::string(64, '0')));
}

void Blockchain::addBlock(const std::string& data){
    std::string prevHash = getLastBlock()->getHash();

    auto newBlock = std::make_unique<Block>(chain.size(), data, prevHash);

    newBlock->mineBlock(difficulty);

    chain.push_back(std::move(newBlock));
}

Block* Blockchain::getLastBlock() const {
    return chain.back().get();
}

bool Blockchain::isChainValid() const{
    const std::string target(difficulty, '0');

    // Empezamos en i=1: el génesis no tiene predecesor y no está minado
    for(size_t i = 1; i < chain.size(); i++){
        const Block* currentBlock  = chain[i].get();
        const Block* previousBlock = chain[i-1].get();

        // 1. Integridad interna: los datos no fueron alterados
        if(currentBlock->getHash() != currentBlock->calculateHash())
            return false;

        // 2. Encadenamiento: el eslabón apunta al anterior
        if(currentBlock->getPreviousHash() != previousBlock->getHash())
            return false;

        // 3. Proof of Work: el bloque hizo el trabajo
        if(currentBlock->getHash().substr(0, difficulty) != target)
            return false;
    }
    return true;
}

Block* Blockchain::getBlockAt(size_t index) {
    if (index >= chain.size()) return nullptr;
    return chain[index].get();
}

size_t Blockchain::size() const { return chain.size(); }

