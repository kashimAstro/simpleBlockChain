#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <fstream>
#include "sha256.h"

using namespace std;

class Block {
 public:
    string sHash;
    string sPrevHash;    
    uint32_t index;
    uint32_t nonce;
    time_t timer;
    string data;
    
    void write_file(const std::string& name, const std::string& content, bool append = false) {
       std::ofstream outfile;
       if (append)
          outfile.open(name, std::ios_base::app);
       else
          outfile.open(name);
       outfile << content;
       outfile.close();
    }
    
    Block(uint32_t nIndexIn, const string &sDataIn) : index(nIndexIn), data(sDataIn)
    {
       nonce = 0;
       timer = time(nullptr);
       sHash = calculate_hash();
    }

    void mine_block(uint32_t nDifficulty)
    {
       char cstr[nDifficulty + 1];
       for (uint32_t i = 0; i < nDifficulty; ++i){
          cstr[i] = '0';
       }
       cstr[nDifficulty] = '\0';
       string str(cstr);
       while (sHash.substr(0, nDifficulty) != str) {
          nonce++;
          sHash = calculate_hash();
       }
       cout << "Block mined: " << sHash << " difficult: " << nDifficulty << endl;
       write_file("hash.store", sHash+"\n", true);
       
    }
    
    inline string calculate_hash() const
    {
       stringstream ss;
       ss << index << sPrevHash << timer << data << nonce;
       return sha256(ss.str());
    }
};

class Blockchain {
 public:
    uint32_t difficulty;
    vector<Block> chain;
    
    Blockchain(uint32_t _diff)
    {
       chain.emplace_back(Block(0, "Genesis Block"));
       difficulty = _diff;
    }

    void add(Block _block)
    {
       _block.sPrevHash = _get_last_block().sHash;       
       _block.mine_block(difficulty);
       chain.push_back(_block);
    }

    Block _get_last_block() const
    {
       return chain.back();
    }
};

#endif
