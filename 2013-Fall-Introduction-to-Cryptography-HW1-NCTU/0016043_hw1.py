#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# written in python3
# 0016043 shunyi

import fileinput
import string

statical_prob = {
    'a': 0.08167,
    'b': 0.01492,
    'c': 0.02782,
    'd': 0.04253,
    'e': 0.12702,
    'f': 0.02228,
    'g': 0.02015,
    'h': 0.06094,
    'i': 0.06966,
    'j': 0.00153,
    'k': 0.00772,
    'l': 0.04025,
    'm': 0.02406,
    'n': 0.06749,
    'o': 0.07507,
    'p': 0.01929,
    'q': 0.00095,
    'r': 0.05987,
    's': 0.06327,
    't': 0.09056,
    'u': 0.02758,
    'v': 0.00978,
    'w': 0.02360,
    'x': 0.00150,
    'y': 0.01974,
    'z': 0.00074,
}

def Index_c(s):
    result, i = 0, 0
    n = len(s)
    if n > 1:
        while i < 26:
            f = float(s.count(chr(ord('a')+i)))
            result += (f*(f-1)) / (n*(n-1))
            i += 1

    return result


def find_key(s):
    f, i = [], 0
    n = len(s)
    while i < 26:
        f.append(float(s.count(chr(ord('a')+i))))
        i += 1

    M, g = [], 0
    while g < 26:
        result, j = 0, 0
        while j < 26:
            result += statical_prob[chr(ord('a')+j)]*f[(j+g)%26] / n
            j += 1
        M.append(result)
        g += 1

    return chr(ord('a') + M.index(max(M)))


def decrypt_key(s):
    prob_keys = []
    m = 1
    while m <= len(s):
        j = 0
        l = []
        y = []
        while j < m:
            y.append(s[j::m])
            l.append(Index_c(s[j::m]))
            j += 1

        if 0.068-0.008 <= sum(l)/len(l) <= 0.068+0.008:
            i, key = 0, []
            while i < m:
                key.append(find_key(y[i]))
                i += 1

            yield ''.join(key)
        m += 1


def find_plaintext(c, k):
    p = ''
    offset = 0

    for i in range(len(c)):
        if c[i].isupper():
            p += chr((ord(c[i]) - ord(k[(i-offset)%(len(k))].upper()))%26 + ord('A'))
        elif c[i].islower():
            p += chr((ord(c[i]) - ord(k[(i-offset)%(len(k))]))%26 + ord('a'))
        else:
            p += c[i]
            offset += 1

    print('='*40)
    print('key length')
    print(len(k))
    print('-'*40)
    print('key')
    print(k)
    print('-'*40)
    print('plaintext')
    print(p)
    print('='*40)
    print()


def main():
    f = fileinput.input()
    cipher_text = ''
    for l in f:
        cipher_text += l

    c = ''.join([x.lower() for x in cipher_text if x in string.ascii_letters])
    keys = decrypt_key(c)

    for i, key in enumerate(keys):
        print('No.{}'.format(i+1))
        find_plaintext(cipher_text, key)
    else:
        print('No more possible key found.')



if __name__ == "__main__":
    main()
