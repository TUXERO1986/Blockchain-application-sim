#pragma once

#include <string>
#include <ctime>
#include <cstdint>

class Block {
private:
    int index;
    time_t timestamp;
    std::string data;
    std::string previousHash;
    std::string hash;
    uint32_t nonce;

public:
    Block(int index, const std::string& data, const std::string& prevHash);

    std::string calculateHash() const;

    std::string getHash() const;
    std::string getPreviousHash() const;

    void mineBlock(uint32_t difficulty);
    int         getIndex() const;
std::string getData()  const;
uint32_t    getNonce() const;

// Solo para el simulador de ataques: altera los datos SIN recalcular el hash
void tamperData(const std::string& fakeData);
};