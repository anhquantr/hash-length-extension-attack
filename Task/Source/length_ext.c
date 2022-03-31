//Task 3

/* length_ext.c */
#include <stdio.h>
#include <arpa/inet.h>
#include <openssl/sha.h>

int main(int argc, const char *argv[])
{
    int i;
    unsigned char buffer[SHA256_DIGEST_LENGTH];
    SHA256_CTX c;

    SHA256_Init(&c);
    for(i=0; i<64; i++){
        SHA256_Update(&c, "*", 1);
    }

    // MAC of the original message M (padded)
    c.h[0] = htole32(0xd0b4460c);
    c.h[1] = htole32(0xabb862d1);
    c.h[2] = htole32(0xe3e53775);
    c.h[3] = htole32(0xd084fc8a);
    c.h[4] = htole32(0xa4ac1214);
    c.h[5] = htole32(0x4d62dcd3);
    c.h[6] = htole32(0x1b0643d8);
    c.h[7] = htole32(0x78faeac1);

    // Append additional message
    SHA256_Update(&c,"&download=secret.txt",20);
    SHA256_Final(buffer, &c);
    
    for(i = 0; i < 32; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
    return 0; 
}