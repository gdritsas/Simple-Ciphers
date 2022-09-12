# Introduction
In this assignment I implemented from scratch, using C, a simple cryptographic
library named simple_crypto. The cryptographic library will provide three basic but fundamental
cryptographic algorithms, (i) One-time pad , (ii) Caesar’s cipher and (iii) Vigenère’s cipher .
The main purpose of this assignment is to offer the opportunity to get familiar with the
implementation and internals of such simple ciphers and help to understand the development
decisions and tricks that developers have to deal with when implementing security critical
functions that, at first, seem trivial to develop.
The simple_crypto library consists of two files. The simple_crypto.h, which contains the C
function declarations and the simple_crypto.c file, containing the implementation of the above algorithms.

# One-time pad
The One-Time-Pad (OTP) algorithm is a very simple but yet very strong algorithm in the sense
that it can not be cracked even with post-quantum techniques. The algorithm pairs each
plaintext with a random secret key (also referred to as a one-time pad). Specifically, each bit or
byte/character of the plaintext is combined with the corresponding bit or byte/character from the
random secret key. One-time pad requires that the secret key is of the same size or longer
than the plaintext.


Implementation details:<br/>
In order to generate a random secret key you will use a pseudorandom generator, such as
/dev/urandom. The pseudorandom generator will read N random characters from /dev/urandom,
where N is the number of bytes/characters found in the plaintext. Then, the algorithm will
encrypt each byte/character of the plaintext by XOR-ing it with the corresponding byte/character
of the random secret key.
Since /dev/urandom will return a new random value upon each read, you will first need to
generate an appropriate sized random secret key and store it in memory in order to successfully
decrypt the encrypted message. For this functionality you can develop your own separate
function or macro. Also, since the usage of /dev/urandom is our suggested pseudorandom
generator, you are advised to use a Linux-based system for the development and testing of the
OTP algorithm. The function(s) encrypting and decrypting the messages should receive as
arguments the plain- or cipher-text as well as the random secret key and should return the result
of the operation. Special characters, such as “!”, “@”, “*”, etc. that are not part of the english
alphabet should be skipped as if the character set only consists of numbers 0-9 followed by
uppercase characters A-Z and lowercase characters a-z. The same applies for all the rest of the
printable and non-printable ASCII characters such as “\n”, “\t”, “\0” etc. Notice that XOR-ing
specific characters together might result in non-printable characters or even “\0”. For this reason
you should think around this problem when handling and printing any results. Also note that
each time you access /dev/urandom you are going to receive a different key. For this reason the
encrypted text deriving from the same plaintext is going to change across executions. Also, for
the same reason, you should store the key used for a message encryption in order to
successfully decrypt it.

# Caesar's cipher
This technique is one of the simplest and most widely known encryption techniques. It is a type
of substitution cipher in which each byte/character of the plaintext is replaced by a
byte/character found at some fixed number of positions down the alphabet/ASCII set. For
example, given the ASCII character set, a shift of 3 will replace the letter “A” of the plaintext
with the letter “D” at the ciphertext. Also, a shift of 4 will encrypt the plaintext “hello” as “lipps”.
The function(s) encrypting and decrypting the messages should receive as arguments the plainor
cipher-text as well as the random secret key and should return the result of the operation.


Implementation details:<br/>
The implementation should support numbers, uppercase and lowercase characters. Special
characters, such as “!”, “@”, “*”, etc. that are not part of the english alphabet should be skipped
as if the character set only consists of numbers 0-9 followed by uppercase characters A-Z and
lowercase characters a-z. The same applies for all the rest of the printable and non-printable
ASCII characters such as “\n”, “\t”, “\0” etc. The function(s) encrypting and decrypting the
messages should receive as arguments the plain- or cipher-text as well as a positive number
indicating the number of shifted positions and should return the result of the operation.

# Vigenère’s cipher
The Vigenère’s cipher encrypts an alphabetic plaintext using a series of interwoven Caesar’s
ciphers. In order to encrypt a message, the algorithm uses a table of alphabets, namely tabula
recta, which has the alphabet written out 26 times in different rows, each alphabet shifted
cyclically to the left compared to the previous alphabet, corresponding to the 26 possible Caesar
ciphers. At different points in the encryption process, the cipher uses a different alphabet from
one of the rows. A visual representation of this table is the following:

![Optimized-189750964-35c0145f-8e9f-41d3-ac72-9ce2b76b4ca4](https://user-images.githubusercontent.com/113385351/189752416-a6200e6d-c944-4277-aa41-6a4a964afe9c.png)

The alphabet used at each point depends on a keyword, repeated in order to make a key that
matches the size of the plain-text. For example, if the plaintext is “ATTACKATDAWN” and the
keyword is “LEMON” then the plaintext and the key are:
Plaintext: ATTACKATDAWN
Key: LEMONLEMONLE
Ciphertext: LXFOPVEFRNHR
In order to produce the ciphertext, the first letter of the plaintext is used as a column indicator
and the first letter of the key is used as a row indicator, thus the first letter of the ciphertext will
be the letter at the point where the selected column meets the selected row. For our example,
following column “A” (due to the first letter of the plaintext) and row “L” (due to the first letter of
the key) we find out that the first letter of the ciphertext is “L”. Performing the same operation for
the second letter of the plaintext and the second letter of the key we find out that the second
ciphertext character is “X”. This process repeats for the entire plaintext, thus generating
“LXFOPVEFRNHR”. Decryption is performed by going to the row in the table corresponding to
the key, finding the position of the ciphertext letter in that row and then using the column's label
as the plaintext.


Implementation details:<br/>
The Vigenère cipher has several Caesar ciphers in sequence with different shift values based
on a secret key. For encryption/decryption the keyword is repeated until it matches the length of
the plaintext, thus generating the key. The characters that can be found in the alphabet (used
for the message and key) should only be the uppercase characters A-Z, thus lowercase
characters a-z, digits 0-9 or any other ASCII characters should not be used. The function(s)
encrypting and decrypting the messages should receive as arguments the plain- or cipher-text
as well as the keyphrase and should return the result of the operation. They keyphrase will be
expanded to match the plaintext or ciphertext length internally, in the corresponding function.


# Demo program
In order to evaluate the library you should develop a simple demo program that utilizes the
implemented functions. The demo program will prompt the user for a plaintext to be encrypted
and a key, in the case of Caesars and Vinegere’s cipher. For each algorithm, the demo program
will first encrypt the user input and print the encrypted message. Then, it will decrypt the
encrypted message and print the plaintext. The format has to be the exact following:<br/>
[OTP] input: "user input"<br/>
[OTP] encrypted: XXXXXX<br/>
[OTP] decrypted: XXXXXX<br/>
[Caesars] input: "user input"<br/>
[Caesars] key: "a number"<br/>
[Caesars] encrypted: XXXXX<br/>
[Caesars] decrypted: XXXXX<br/>
[Vigenere] input: "user input"<br/>
[Vigenere] key: "user input"<br/>
[Vigenere] encrypted: XXXX<br/>
[Vigenere] decrypted: XXXX<br/>

An example execution could be the following.<br/>
[OTP] input: secret<br/>
[OTP] encrypted: w4&=5Q<br/>
[OTP] decrypted: secret<br/>
[Caesars] input: hello<br/>
[Caesars] key: 4<br/>
[Caesars] encrypted: lipps<br/>
[Caesars] decrypted: hello<br/>
[Vigenere] input: ATTACKATDAWN<br/>
[Vigenere] key: LEMON<br/>
[Vigenere] encrypted: LXFOPVEFRNHR<br/>
[Vigenere] decrypted: ATTACKATDAWN<br/>
