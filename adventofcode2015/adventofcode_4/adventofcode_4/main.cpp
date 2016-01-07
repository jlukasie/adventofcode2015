#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <Wincrypt.h>
#include <cassert>
#include <string>

using namespace std;

#define MD5LEN  16

int main()
{
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    string base = "bgvyzdsv";
    unsigned long long num = 1;
    BYTE rgbHash[MD5LEN];
    char hexHash[MD5LEN*2 + 1];
    char tmp[5];
    DWORD cbHash = 0;
    CHAR rgbDigits[] = "0123456789abcdef";

    if (!CryptAcquireContext(&hProv,
        NULL,
        NULL,
        PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT))
    {
        assert(!"CryptAcquireContext failed!\n");
        return -1;
    }

    while(1)
    {
        string hash_string = base + to_string(num);

        if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
        {
            assert(!"CryptCreateHash failed!\n");
            return -1;
        }

        if (!CryptHashData(hHash, (BYTE *)hash_string.c_str(), hash_string.length(), 0))
        {
            assert(!"CryptHashData failed!\n");
            return -1;
        }

        cbHash = MD5LEN;
        if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
        {
           // printf("MD5 hash of buffer %s is: ", hash_string.c_str());
            char *ptr = hexHash;
            for (DWORD i = 0; i < cbHash; i++)
            {
                sprintf_s(tmp,"%c%c", rgbDigits[rgbHash[i] >> 4],
                    rgbDigits[rgbHash[i] & 0xf]);

                memcpy(ptr, tmp, 3);
                ptr += 2;
            }

            //cout << hexHash << endl;

            if (hexHash[0] == '0' &&
                hexHash[1] == '0' &&
                hexHash[2] == '0' &&
                hexHash[3] == '0' &&
                hexHash[4] == '0' &&
                hexHash[5] == '0')
            {
                cout << "hash string: " << hash_string << " hashed to: " << hexHash << endl;
                cin >> cbHash;
                break;
            }

            ptr++;
        }
        else
        {
            assert(!"CryptGetHashParam failed!\n");
            return -1;
        }
        CryptDestroyHash(hHash);
        num++;
    }

    CryptReleaseContext(hProv, 0);

    return 0;
}