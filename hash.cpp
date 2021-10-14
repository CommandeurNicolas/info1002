#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
typedef unsigned char Byte; // facultatif

void hash_MD5(const char *s, Byte *empreinte)
{
    MD5((unsigned char *)s, strlen(s), empreinte);
}

void hash_SHA1(const char *s, Byte *empreinte)
{
    SHA1((unsigned char *)s, strlen(s), empreinte);
}
