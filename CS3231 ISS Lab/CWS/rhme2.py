# sample hashes from rhme2
'''
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
dfd0f4a25b7d529e89ac030c2b681e93831e95a8186823b9 | cat.txt
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
f2bca35d472116dc6d5bebe96f1a3af249be78c63219a0dc | cat.txt:finances.csv
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
7eed666977d3861dbaefd16b2ed7dc5b639e51853ca6e7b3 | cat.txt:finances.csv:joke.txt
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
51d915246394ce976f8768cf3300087cb5b9958bbec30f9c | cat.txt:joke.txt
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
ae2a5a38b4d03f0103bce59874e41a0df19cb39b328b02fa | finances.csv
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
c66b5e48f5e600982724eca3804fb59b7b0f395a6e17e1ce | finances.csv:joke.txt
897703036b2e18116b36353d92ac3dd978845fc99a735b8a |
3a3a9b3cc5239fdf4572157296903a0237a4aaeeaa8f3d15 | joke.txt
'''

from hashlib import sha1
from ecdsa.curves import NIST192p
from ecdsa.numbertheory import inverse_mod
from ecdsa import SigningKey

n = NIST192p.order

r1_str = '897703036b2e18116b36353d92ac3dd978845fc99a735b8a'
s1_str = 'dfd0f4a25b7d529e89ac030c2b681e93831e95a8186823b9'

r1 = int(r1_str, 16)
s1 = int(s1_str, 16)
m1 = 'cat.txt'.encode('utf-8')
z1 = int(sha1(m1).hexdigest(), 16)

r2_str = '897703036b2e18116b36353d92ac3dd978845fc99a735b8a'
s2_str = '3a3a9b3cc5239fdf4572157296903a0237a4aaeeaa8f3d15'

r2 = int(r2_str, 16)
s2 = int(s2_str, 16)
m2 = 'joke.txt'.encode('utf-8')
z2 = int(sha1(m2).hexdigest(), 16)

if r1 == r2:
    print('Vulnerable ECDSA signature!')

k = (((z1 - z2) % n) * inverse_mod(s1 - s2, n)) % n

print(f'Got k: 0x{k:x}') 

dA = ((((s1 * k) % n) - z1) * inverse_mod(r1, n)) % n

print(f'Got dA: 0x{dA:x}') 

sk = SigningKey.from_secret_exponent(dA)
sig = sk.sign(m1, k=k)
print('fake:', bytes.hex(sig))
print('orig:', r1_str+s1_str)
