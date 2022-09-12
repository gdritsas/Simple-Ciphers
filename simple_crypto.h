void caesarsEncryption (char *message_en, int key_en);
void caesarsDecryption (char *message_dc, int key_dc);
char *vigenereKeyExpand (char *msg, char *kex);
char *vigenereEncryption (char *msg, char *n_key);
void vigenereDecryption (char *msg, char *n_key, char *e_msg);
void otpEncDec(char *msg);