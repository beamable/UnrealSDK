// compact25519 v1.1.0
// Source: https://github.com/DavyLandman/compact25519
// Licensed under CC0-1.0
// Based on Daniel Beer's Public Domain c25519 implementation
// https://www.dlbeer.co.nz/oss/c25519.html version: 2017-10-05

#ifndef __COMPACT_25519_H
#define __COMPACT_25519_H
#if defined(__cplusplus)
extern "C" {
#endif

// provide your own decl specificier like -DCOMPACT_25519_DECL=ICACHE_RAM_ATTR
#ifndef COMPACT_25519_DECL
#define COMPACT_25519_DECL
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/*
    Try to wipe contents of a buffer, as best as we can.
    (memset can be ignored by the compiler)

    Use this to clear private key data if you do not need it anymore.

    returns the data pointer, makes for easier chaining
*/
COMPACT_25519_DECL void *compact_wipe(void *data, size_t length);

#ifndef COMPACT_DISABLE_X25519
/* 
 X25519 is a DH key exchange over Curve25519.
 
 Two parties can share their public keys over an open channel and agree upon 
 a shared secret, that a third party cannot derive.
 
 Security concern: if a third party can intercept and change your connection in 
 some way, then X25519 is not enough. The third party could for example run 
 two X25519 sessions, one between themselfs and you, and another one between 
 themselfs and the server. X25519 has no protection against this.
 
 A possible solution is to use Ed25519 to sign the public keys exchanged, with a 
 special set of keys that is known before hand. Depending on your scenario, this 
 either means embedding a set of long-term keys in your application or setting up 
 some kind of Public Key Infrastructure (PKI).
 
 If that sounds to complicated or would not work for your case, checkout 
 the Noise framework. It is a bit less compact than X25519 + Ed25519 but much 
 more flexible in the kind of session setup styles.
*/

#define X25519_KEY_SIZE (32)
#define X25519_SHARED_SIZE (32)

/*
 Calculate public & private keypair for X25519 key exchange. 
 Never transmit the private_key!
 
 input:
     - random_seed = random bytes that need to be filled from a good source of 
         random entropy, PLEASE research the options on your platform!
 
 output:
     - private_key = resulting private key, never share this with the other party
     - public_key = public key to be shared with the other party
*/
COMPACT_25519_DECL void compact_x25519_keygen(
    uint8_t private_key[X25519_KEY_SIZE], 
    uint8_t public_key[X25519_KEY_SIZE],
    uint8_t random_seed[X25519_KEY_SIZE]
);

/*
 Calculate shared secret based on the others side public key.
 The shared secret does not have a uniform distribution so common advice 
 is to avoid using it directly as a key. You can use 
 compact_x25519_derive_encryption_key to get a more suitable encryption 
 key out of this shared secret
 
 input:
     - my_private_key = private key that came out of compact_x25519_keygen
     - their_public_key = public key that was shared by the other party
 
 output:
     - shared_secret = X25519_SHARED_SIZE bytes that both sides now share 
*/
COMPACT_25519_DECL void compact_x25519_shared(
    uint8_t shared_secret[X25519_SHARED_SIZE], 
    const uint8_t my_private_key[X25519_KEY_SIZE], 
    const uint8_t their_public_key[X25519_KEY_SIZE]
);

#ifndef COMPACT_DISABLE_X25519_DERIVE
/*
 Derive an more suitable encryption key from the shared secret.
 This is not part of the normal X25519 specification, but the specifications 
 does warn that the shared secret is less suited as symmetric encryption key.
 
 The encryption key is the result of 
 sha512(concat(shared_secret, public_key1, public_key2))[0..key_size]
 
 You have to make sure both parties agree which public key goes in first.
 
 input:
     - key_size = number between 1 and 64, of how big your encryption_key 
         needs to be, make sure there is enough room where 
         the encryption_key points to
     - shared_secret = result of compact_x25519_shared
     - public_key1 = first public key to mix in with the key
     - public_key2 = second public key to mix in with the key
 
 output:
     - encryption_key = supplied buffer is filled with a encryption key
*/
COMPACT_25519_DECL void compact_x25519_derive_encryption_key(
    uint8_t *encryption_key, 
    size_t key_size, 
    const uint8_t shared_secret[X25519_SHARED_SIZE], 
    const uint8_t public_key1[X25519_KEY_SIZE], 
    const uint8_t public_key2[X25519_KEY_SIZE]
);
#endif
#endif

#ifndef COMPACT_DISABLE_ED25519
/*
 Ed25519 signs messages using Curve25519.
 
 After pre-sharing a public key, it allows two parties to verify the other side
 is who they say they are and that the communication is not altered.
 
 A signature is a ED25519_SIGNATURE_SIZE size byte array that can be only be 
 generated when you have the private key, but can be verified if you have 
 the public key. 
 
 As an example: two parties want to have rotating keys for their encryption.
 The only thing they need to know about eachother is their long term Ed25519
 public key. Per session they perform a X25519 key exchange, but sign their 
 "Ephemeral" public key with their long-term Ed25519 private key. Now they can 
 share this public key (and the signature) over a cleartext channel, nobody can
 alter of impersonate this exchange.
 
 (this is roughly how TLS works)
*/

#define ED25519_SEED_SIZE (32)
#define ED25519_PUBLIC_KEY_SIZE (32)
#define ED25519_PRIVATE_KEY_SIZE (64)
#define ED25519_SIGNATURE_SIZE (64)

/*
 Generate a private signing key from a random seed.
 
 input:
     - random_seed = random bytes that need to be filled from a good source of 
         random entropy, PLEASE research the options on your platform!
 
 output:
     - private_key = signing key than can be used for compact_ed25519_sign
     - public_key = key to share with other parties 
 
 (internally the format of the private key is the seed + public key, 
 this makes it compatible with keys coming from libsodium, golang, and 
 implentations that derive from SUPERCOP/ref10)
*/
COMPACT_25519_DECL void compact_ed25519_keygen(
    uint8_t private_key[ED25519_PRIVATE_KEY_SIZE], 
    uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    uint8_t random_seed[ED25519_SEED_SIZE]
);

/*
 Extract public key from private key
 
 input:
     - private_key = signing key generated with compact_ed25519_keygen
 
 output:
     - public_key = public key corresponding to this private key, share with
         interested parties
*/
COMPACT_25519_DECL void compact_ed25519_calc_public_key(
    uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    const uint8_t private_key[ED25519_PRIVATE_KEY_SIZE]
);

/*
 Sign a message with the private key.
 
 input:
     - private_key = signing key generated with compact_ed25519_keygen or from a
         compatible source
     - message = pointer to the data that needs to be signed
     - msg_length = how many bytes to read from the start of the message pointer
 output:
     - signature = the signature that proves you hold the private key and that
         nobody tried to change the message. (the second property only holds
         if the attacker cannot change the size of the message)
*/
COMPACT_25519_DECL void compact_ed25519_sign(
    uint8_t signature[ED25519_SIGNATURE_SIZE], 
    const uint8_t private_key[ED25519_PRIVATE_KEY_SIZE], 
    const void *message, 
    size_t msg_length
);

/*
 Verify a signature against a public key.
 
 input:
     - signature = which signature to verify
     - public_key = the public key that it should be verified against 
         (should not have been part of the message that contained the signature)
     - message = message to verify
     - msg_length = size of the message to verify
 
 returns:
     true if verified
*/
COMPACT_25519_DECL bool compact_ed25519_verify(
    const uint8_t signature[ED25519_SIGNATURE_SIZE], 
    const uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    const void *message, 
    size_t msg_length
);
#endif

#if defined(__cplusplus)
}
#endif
#endif
