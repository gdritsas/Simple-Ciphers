#include <stdio.h>
#include <stdlib.h>
#include "simple_crypto.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

	
int main() 
{

	/////////////////////////VARIABLES - POINTERS////////////////////////////////

    int keyC;
	char *message, *key;	

    char* ptr;													
	ptr = (char*)malloc(sizeof(char));
	message = ptr;

	char* ptr1;
	ptr1 = (char*)malloc(sizeof(char));
	key = ptr1;

	//////////////////////////////OTP MAIN//////////////////////////////////////

	printf("[OTP] input: ");
	scanf("%s",message);

	otpEncDec(message);

	/////////////////////////////CAESARS MAIN///////////////////////////////////

	printf("[Caesars] input: ");
	scanf("%s", message);

	printf("[Caesars] key: ");
	scanf("%d", &keyC);

	caesarsEncryption (message, keyC);
	printf("[Caesars] encrypted: %s\n", message);

    caesarsDecryption (message, keyC);
    printf("[Caesars] decrypted: %s\n", message);

    ///////////////////////////VIGENERE MAIN////////////////////////////////////

	printf("[Vigenere] input: ");
    scanf("%s", message);

    printf("[Vigenere] key: ");
    scanf("%s", key);

    char *r_key = vigenereKeyExpand(message, key);
    char *en_msg = vigenereEncryption(message, r_key);
    vigenereDecryption(message, r_key, en_msg);

    free(ptr);

    return 0;
}