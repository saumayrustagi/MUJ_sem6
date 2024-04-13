import rsa

# Generate public and private keys with rsa.newkeys method
# The key length should be at least 16
publicKey, privateKey = rsa.newkeys(512)

# This is the string that we will be encrypting
message = input()

# rsa.encrypt method is used to encrypt string with public key
# String should be encoded to byte string before encryption with encode method
encMessage = int.from_bytes(rsa.encrypt(message.encode(), publicKey), byteorder='big')

print(encMessage)
