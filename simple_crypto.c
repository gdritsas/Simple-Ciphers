#include <stdio.h>
#include <stdlib.h>
#include "simple_crypto.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void caesarsEncryption (char *message_en, int key_en) {

    char ch, full_alphabet[62], temp = '\0';
    int j,i,k=0,n;

    for (i=48; i<=57; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }
    for (i=65; i<=90; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }
    for (i=97; i<=122; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }


    for (j=0; message_en[j] != '\0'; j++){
        ch = message_en[j];

        for (n=0; temp == 0; n++){
            if (full_alphabet[n] == ch){
                    if (n+key_en >= 62){
                        ch = full_alphabet[(n+key_en)%62];
                        temp = ch;
                    }
                    else {
                        ch = full_alphabet[n+key_en];
                        temp = ch;
                    }
            }
        }

        message_en[j] = ch;
        temp = '\0';
    }
}

void caesarsDecryption (char *message_dc, int key_dc) {

    char ch, full_alphabet[62], temp = '\0';
    int j,i,k=0,n;

    for (i=48; i<=57; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }
    for (i=65; i<=90; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }
    for (i=97; i<=122; i++) {
        full_alphabet[k] = i;
        k=k+1;
    }


    for (j=0; message_dc[j] != '\0'; j++){
        ch = message_dc[j];

        for (n=0; temp == 0; n++){
            if (full_alphabet[n] == ch){
                    if (key_dc%62 - n >= 0){
                        ch = full_alphabet[62-((key_dc%62)-n)];
                        temp = ch;
                    }
                    else {
                        ch = full_alphabet[n-(key_dc%62)];
                        temp = ch;
                    }
            }
        }

        message_dc[j] = ch;
        temp = '\0';
    }
}

char *vigenereKeyExpand (char *msg, char *kex) {

    int i, j=0, k=0;
	char *act_key;																						
    char* ptr2;
	ptr2 = (char*)malloc(sizeof(char));
	act_key = ptr2;


    for (i=0; msg[i] != '\0'; i++){
        if (kex[i-k] != '\0'){
            act_key[i] = kex[i];
            j = j + 1;
        }
        if (kex[i-k] == '\0') {
            act_key[i] = act_key[i-j];
            k = k + 1;
        }
    }

    return act_key;
}

char *vigenereEncryption (char *msg, char *n_key){

    char *enc_msg;																						
    char* ptr2;
	ptr2 = (char*)malloc(sizeof(char));
	enc_msg = ptr2;
	int k = strlen(msg), i;

    for(i = 0; i < k; ++i){
        enc_msg[i] = ((msg[i] + n_key[i]) % 26) + 'A';
    }

    enc_msg[i] = '\0';

    printf("[Vigenere] encrypted: %s", enc_msg);

    return enc_msg;

    free (ptr2);
}

void vigenereDecryption (char *msg, char *n_key, char *e_msg){

    char *dec_msg;																						
	int k = strlen(msg), i;

    for(i = 0; i < k; i++){
        dec_msg[i] = (((e_msg[i] - n_key[i]) + 26) % 26) + 'A';
    }

    dec_msg[i] = '\0';

    printf("\n[Vigenere] decrypted: %s\n", dec_msg);
}

void otpEncDec (char *msg) {

		int i;
		int bc = strlen(msg);
        char key[bc],h_key;

		FILE *pointer;
        pointer = fopen("/dev/urandom", "r");

        for (i = 0; i < bc; i++){
            char temp[bc];

                do{
                    temp[i] = msg[i]; //setting temp = msg so for i=0 temp[0] = first msg letter

                    fread(&h_key, 1, 1, pointer); //generating only 1 char/byte and storing it at [0] of h_key
                    temp[i] = temp[i] ^ h_key; //XORing message's 1st char with the random generated char

                } while ((temp[i] < 33) || (temp[i] == 127)); //accepting the result only if xor-ed char is printable

            msg[i] = temp[i];
            key[i] = h_key;
        }

        fclose(pointer);

        
        printf("[OTP] encrypted: ");
        for(i = 0; i < bc; i++){
       		printf("%c", msg[i]);
        }
        printf("\n");

    
        printf("[OTP] decrypted: ");
        for(i = 0; i < bc; i++){
            msg[i] = msg[i] ^ key[i];
            printf("%c",msg[i]);
        }
        printf("\n");
}