#!/usr/sbin/python2
# shebang for python2 on linux1.cs
# -*- coding: utf-8 -*-
# written in python2
# 0016043 shunyi

statical_prob = {
    'A' : 0.08167,
    'B' : 0.01492,
    'C' : 0.02782,
    'D' : 0.04253,
    'E' : 0.12702,
    'F' : 0.02228,
    'G' : 0.02015,
    'H' : 0.06094,
    'I' : 0.06966,
    'J' : 0.00153,
    'K' : 0.00772,
    'L' : 0.04025,
    'M' : 0.02406,
    'N' : 0.06749,
    'O' : 0.07507,
    'P' : 0.01929,
    'Q' : 0.00095,
    'R' : 0.05987,
    'S' : 0.06327,
    'T' : 0.09056,
    'U' : 0.02758,
    'V' : 0.00978,
    'W' : 0.02360,
    'X' : 0.00150,
    'Y' : 0.01974,
    'Z' : 0.00074,
}

def Index_c (s):
    result, i = 0, 0
    n = len(s)
    while i < 26:
        f = float(s.count(chr(ord('A')+i)))
        result += (f*(f-1)) / (n*(n-1))
        i += 1
    return result


def find_key (s):
    f, i = [], 0
    n = len(s)
    while i < 26:
        f.append(float(s.count(chr(ord('A')+i))))
        i += 1

    M, g = [], 0
    while g < 26:
        result, j = 0, 0
        while j < 26:
            result += statical_prob[chr(ord('A')+j)]*f[(j+g)%26] / n
            j += 1
        M.append(result)
        g += 1

    return chr(ord('A') + M.index(max(M)))


def decrypt_key (s):
    m = 1
    l_avg = []
    Y = []
    while m <= 20:
        j = 0
        l = []
        y = []
        while j < m:
            y.append(s[j::m])
            l.append(Index_c(s[j::m]))
            j += 1

        l_avg.append(sum(l)/len(l))
        Y.append(y)
        m += 1


    i, key = 0, []
    while i <= l_avg.index(max(l_avg)):
        key.append(find_key(Y[l_avg.index(max(l_avg))][i]))
        i += 1

    return "".join(key)

def find_plaintext (c, k):
    p = ""
    for i in range(len(c)):
             p += chr((ord(c[i]) - ord(k[i%(len(k))]))%26 + ord('A'))
    return p

def main():
    cipher_text = raw_input()
    c = "".join(cipher_text.upper().split())

    key = decrypt_key(c)
    plaintext = find_plaintext(c, key)

    print key
    print plaintext

if __name__ == "__main__":
    main()
