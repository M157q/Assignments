# -*- coding: utf-8 -*-

print "plz give me the plaintext: "
p = raw_input().upper()

print "plz give me the key: "
k = raw_input().upper()

print "Now do the encryption...\n"

c = ""

for i in xrange(len(p)):
    c += chr((ord(p[i]) + ord(k[i%(len(k))]))%26 + ord('A'))
    #x = ord(p[i]) + ord(k[i%(len(k))]) - ord('a')
    #if x > ord('z'):
    #    c += chr(x - ord('z') + ord('a') - 1)
    #else:
    #    c += chr(x)

print c

