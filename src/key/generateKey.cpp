#include "../ed25519/src/ed25519.h"
#include "generateKey.hpp"
#include <sstream>
#include <iomanip>
#include <fstream>

Key::Key() {}

std::string Key::toHexString(const unsigned char* data, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)data[i];
    }
    return ss.str();
}

void Key::savePrivateKey(const unsigned char* private_key) {
    std::ofstream privFile("private_key.hex");
    privFile << toHexString(private_key, 64); // 64 байти приватного ключа
    privFile.close();
}

std::string Key::createPairKey() {
    unsigned char public_key[32], private_key[64], seed[32];
    ed25519_create_seed(seed);
    ed25519_create_keypair(public_key, private_key, seed);

    savePrivateKey(private_key);

    std::string savePublicKey = toHexString(public_key, sizeof(public_key));
    std::ofstream pubFile("public_key.hex");
    pubFile << savePublicKey;
    pubFile.close();

    return savePublicKey; // Можна повертати публічний ключ у hex
}