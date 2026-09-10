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
    ss << index <<timestamp<<data<<previousHash<<nonce; //concatenamos los atriburtos de la clase block
    std::string input = ss.str(); //La concatenacion anteriormente hecha la pasamos como string a otra variable
    unsigned char hashResult[SHA256_DIGEST_LENGTH]; //Hacemos una cadena de unsigned char de tamaño 32 bytes "unsinged char entiende bits crudos"
    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()),input.length(),hashResult);
    /*SHA256 entiende solo unsigned char como puntero, sin embargo input esta com string, entonces lo convertimos a unsigned char con .c_str()
    pero con retinterpret_cast le decimos al compilador que lo interprete como un const unsigned char*, el segundo parametro le pasamos la cantidad de bytes de input con length
    y el tercer parametro es donde se va a guardar el resultado
    */
   //Una vez haber guardado el hash en bits o bytes, necesitamos mostrarlo exactamente en 32 bytes para el hash en consola

   std::stringstream hexStream;
   for (int i=0; i<SHA256_DIGEST_LENGTH; i++){
    hexStream << std::hex <<std::setfill('0')<<std::setw(2)<<static_cast<int>(hashResult[i]);
    /* hex avisa que el caracter que se devolvera sera en hexadecimal, despues setfill ordena
    qu se complete con 0 si es que falta n nibble mayor, por consiguiente setw fija el ancho minimo
    y con toda esa informacion static_cast<int> convierte en entero el bite en la posicon i
    */
   }
   return hexStream.str();
   //finalmente se imprime la concatenacion de toda eso en u string
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