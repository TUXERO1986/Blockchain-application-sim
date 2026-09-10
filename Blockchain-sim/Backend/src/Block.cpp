#include "Block.h"
#include <iomanip>
#include <openssl/sha.h>

Block::Block(int idx, const std::string& dataIn, const std::string& prevHash)
    : index(idx), data(dataIn), previousHash(prevHash), nonce(0) {
    timestamp = time(nullptr);
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << "|"<<index<< "|" <<timestamp<< "|"<<data<< "|"<<previousHash<< "|"<<nonce;
    std::string input = ss.str();
    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()),input.length(),hashResult);

   std::stringstream hexStream;
   for (int i=0; i<SHA256_DIGEST_LENGTH; i++){
    hexStream << std::hex <<std::setfill('0')<<std::setw(2)<<static_cast<int>(hashResult[i]);
   }
   return hexStream.str();
}

std::string Block::getHash() const {
    return hash;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

void Block::mineBlock(uint32_t difficulty) {
    std::string target(difficulty, '0');
    
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
}

int Block::getIndex() const { return index; }
std::string Block::getData() const { return data; }
uint32_t Block::getNonce() const { return nonce; }

void Block::tamperData(const std::string& fakeData) {
    data = fakeData;   // el hash guardado queda obsoleto a propósito
}