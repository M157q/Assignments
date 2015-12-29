# from http://rosettacode.org/wiki/Vigen%C3%A8re_cipher

import fileinput
from itertools import starmap,cycle


def encrypt(message, key):
    # convert touppercase.
    # strip out non-alphacharacters.
    message = filter(lambda _: _.isalpha(), message.upper())
    # single letter encrpytion.
    def enc(c,k):
        print c, ord(c), k, ord(k), (ord(k)+ord(c))%26
        return chr(((ord(k) + ord(c)) % 26) + ord('A'))
    return "".join(starmap(enc, zip(message,cycle(key))))
def decrypt(message,key):
    # single letter decryption.
    def dec(c,k): return chr(((ord(c) - ord(k)) % 26) + ord('A'))
    return "".join(starmap(dec, zip(message, cycle(key))))

text = ""
for l in fileinput.input():
    text += l

key = "ABCDEF"

encr = encrypt(text, key)

print text
print encr
