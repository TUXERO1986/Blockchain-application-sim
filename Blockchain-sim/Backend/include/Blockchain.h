#pragma once

#include <vector>
#include <memory>
#include "Block.h"

class Blockchain{
private:
    std::vector<std::unique_ptr<Block>> chain;
    uint32_t difficulty;
public:
    Blockchain();

    void addBlock(const std::string& data);

    Block* getLastBlock() const;

    bool isChainValid() const;

    Block* getBlockAt(size_t index);
size_t size() const;
};