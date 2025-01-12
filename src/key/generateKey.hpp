#ifndef KEY
#define KEY

#include <string>

class Key
{
public:
    Key();
    std::string createPairKey();
private:
    std::string toHexString(const unsigned char* data, size_t length);
    void savePrivateKey(const unsigned char* private_key);
};

#endif