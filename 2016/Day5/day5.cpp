#include <openssl/evp.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// pour compiler le code il faut ouvrir un terminal dans linux et utiliser "g++ -o day5 day5.cpp -lssl -lcrypto"
// ensuite toujours dans le terminal linux "./day5" pour exécuter

std::string md5(const std::string& str){
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_md5(), nullptr);
    EVP_DigestUpdate(context, str.c_str(), str.size());
    EVP_DigestFinal_ex(context, digest, &digest_len);
    EVP_MD_CTX_free(context);

    std::ostringstream oss;
    for(unsigned int i = 0; i < digest_len; ++i){
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return oss.str();
}

int main(){
    std::string password;
    std::string stringRep{"ugkcyxxp"};
    int numericalPart{0};
    while(password.length() < 8){
        std::string input{stringRep + std::to_string(numericalPart)};
        std::string output = md5(input);
        if(output.substr(0, 5) == "00000"){
            password += output[5];
        }
        numericalPart++;
    }
    std::cout << password << "\n";
    return 0;
}