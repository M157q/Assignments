#/usr/bin/env python3

while True:
    try:
        kw = input()
    except:
        break
    else:
        print('{0:<20s} return {1};'.format('{'+'kw'+kw.title()+'}', kw.upper()))
        #print('kw{0:<15s} "{1}"'.format(kw.title(), kw))
