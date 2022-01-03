#include "StringConversion.h"

void str2md5(char *str, int length, char *output)
{
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char *)malloc(33);

    MD5_Init(&c);

    while (length > 0)
    {
        if (length > 512)
        {
            MD5_Update(&c, str, 512);
        }
        else
        {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n)
    {
        snprintf(&(out[n * 2]), 16 * 2, "%02x", (unsigned int)digest[n]);
    }
    strcpy(output, out);
    free(out);
}

void bytes2md5(const char *data, int len, char *md5buf)
{
    // Based on https://www.openssl.org/docs/manmaster/man3/EVP_DigestUpdate.html
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, len);
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);
    for (i = 0; i < md_len; i++)
    {
        snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
    }
}

void str2uppercase(const char *input_string, const int length, char *output_string)
{
    char *tmp = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; ++i)
    {
        tmp[i] = toupper(input_string[i]);
    }
    memcpy(output_string, tmp, length);
    free(tmp);
}