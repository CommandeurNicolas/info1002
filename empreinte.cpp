#include <stdio.h>
#include <string.h>

typedef unsigned char byte;         // facultatif

#include <openssl/md5.h>
void hash_MD5(const char* s, byte* empreinte)
{
    MD5((unsigned char*)s, strlen(s), empreinte);
}

///////////////////////////////////////////////////////

#include <openssl/sha.h>
void hash_SHA1(const char* s, byte* empreinte)
{
    SHA1((unsigned char*)s, strlen(s), empreinte);
}