// compact25519 v1.1.0
// Source: https://github.com/DavyLandman/compact25519
// Licensed under CC0-1.0
// Based on Daniel Beer's Public Domain c25519 implementation
// https://www.dlbeer.co.nz/oss/c25519.html version: 2017-10-05

#include "compact25519.h"

// ******* BEGIN: c25519/f25519.h ********
/* Arithmetic mod p = 2^255-19
 * Daniel Beer <dlbeer@gmail.com>, 8 Jan 2014
 *
 * This file is in the public domain.
 */

#include <stdint.h>
#include <string.h>

/* Field elements are represented as little-endian byte strings. All
 * operations have timings which are independent of input data, so they
 * can be safely used for cryptography.
 *
 * Computation is performed on un-normalized elements. These are byte
 * strings which fall into the range 0 <= x < 2p. Use f25519_normalize()
 * to convert to a value 0 <= x < p.
 *
 * Elements received from the outside may greater even than 2p.
 * f25519_normalize() will correctly deal with these numbers too.
 */
#define F25519_SIZE  32

/* Identity constants */
#ifdef FULL_C25519_CODE
COMPACT_25519_DECL extern const uint8_t f25519_zero[F25519_SIZE];
#endif
COMPACT_25519_DECL extern const uint8_t f25519_one[F25519_SIZE];

/* Load a small constant */
static COMPACT_25519_DECL void f25519_load(uint8_t *x, uint32_t c);

/* Copy two points */
static COMPACT_25519_DECL inline void f25519_copy(uint8_t *x, const uint8_t *a)
{
	memcpy(x, a, F25519_SIZE);
}

/* Normalize a field point x < 2*p by subtracting p if necessary */
static COMPACT_25519_DECL void f25519_normalize(uint8_t *x);

/* Compare two field points in constant time. Return one if equal, zero
 * otherwise. This should be performed only on normalized values.
 */
static COMPACT_25519_DECL uint8_t f25519_eq(const uint8_t *x, const uint8_t *y);

/* Conditional copy. If condition == 0, then zero is copied to dst. If
 * condition == 1, then one is copied to dst. Any other value results in
 * undefined behaviour.
 */
static COMPACT_25519_DECL void f25519_select(uint8_t *dst,
		   const uint8_t *zero, const uint8_t *one,
		   uint8_t condition);

/* Add/subtract two field points. The three pointers are not required to
 * be distinct.
 */
static COMPACT_25519_DECL void f25519_add(uint8_t *r, const uint8_t *a, const uint8_t *b);
static COMPACT_25519_DECL void f25519_sub(uint8_t *r, const uint8_t *a, const uint8_t *b);

/* Unary negation */
static COMPACT_25519_DECL void f25519_neg(uint8_t *r, const uint8_t *a);

/* Multiply two field points. The __distinct variant is used when r is
 * known to be in a different location to a and b.
 */
#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void f25519_mul(uint8_t *r, const uint8_t *a, const uint8_t *b);
#endif
static COMPACT_25519_DECL void f25519_mul__distinct(uint8_t *r, const uint8_t *a, const uint8_t *b);

/* Multiply a point by a small constant. The two pointers are not
 * required to be distinct.
 *
 * The constant must be less than 2^24.
 */
static COMPACT_25519_DECL void f25519_mul_c(uint8_t *r, const uint8_t *a, uint32_t b);

/* Take the reciprocal of a field point. The __distinct variant is used
 * when r is known to be in a different location to x.
 */
#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void f25519_inv(uint8_t *r, const uint8_t *x);
#endif
static COMPACT_25519_DECL void f25519_inv__distinct(uint8_t *r, const uint8_t *x);

/* Compute one of the square roots of the field element, if the element
 * is square. The other square is -r.
 *
 * If the input is not square, the returned value is a valid field
 * element, but not the correct answer. If you don't already know that
 * your element is square, you should square the return value and test.
 */
static COMPACT_25519_DECL void f25519_sqrt(uint8_t *r, const uint8_t *x);

// ******* END:   c25519/f25519.h ********
// ******* BEGIN: c25519/fprime.h ********
/* Arithmetic in prime fields
 * Daniel Beer <dlbeer@gmail.com>, 10 Jan 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519
#include <stdint.h>
#include <string.h>

/* Maximum size of a field element (or a prime). Field elements are
 * always manipulated and stored in normalized form, with 0 <= x < p.
 * You can use normalize() to convert a denormalized bitstring to normal
 * form.
 *
 * Operations are constant with respect to the value of field elements,
 * but not with respect to the modulus.
 *
 * The modulus is a number p, such that 2p-1 fits in FPRIME_SIZE bytes.
 */
#define FPRIME_SIZE  32

#ifdef FULL_C25519_CODE
/* Useful constants */
COMPACT_25519_DECL extern const uint8_t fprime_zero[FPRIME_SIZE];
COMPACT_25519_DECL extern const uint8_t fprime_one[FPRIME_SIZE];
#endif

#ifdef FULL_C25519_CODE
/* Load a small constant */
static COMPACT_25519_DECL void fprime_load(uint8_t *x, uint32_t c);
#endif

/* Load a large constant */
static COMPACT_25519_DECL void fprime_from_bytes(uint8_t *n,
		       const uint8_t *x, size_t len,
		       const uint8_t *modulus);

/* Copy an element */
static COMPACT_25519_DECL inline void fprime_copy(uint8_t *x, const uint8_t *a)
{
	memcpy(x, a, FPRIME_SIZE);
}

#ifdef FULL_C25519_CODE
/* Normalize a field element */
static COMPACT_25519_DECL void fprime_normalize(uint8_t *x, const uint8_t *modulus);

/* Compare two field points in constant time. Return one if equal, zero
 * otherwise. This should be performed only on normalized values.
 */
static COMPACT_25519_DECL uint8_t fprime_eq(const uint8_t *x, const uint8_t *y);

#endif
/* Conditional copy. If condition == 0, then zero is copied to dst. If
 * condition == 1, then one is copied to dst. Any other value results in
 * undefined behaviour.
 */
static COMPACT_25519_DECL void fprime_select(uint8_t *dst,
		   const uint8_t *zero, const uint8_t *one,
		   uint8_t condition);

/* Add one value to another. The two pointers must be distinct. */
static COMPACT_25519_DECL void fprime_add(uint8_t *r, const uint8_t *a, const uint8_t *modulus);
#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void fprime_sub(uint8_t *r, const uint8_t *a, const uint8_t *modulus);
#endif

/* Multiply two values to get a third. r must be distinct from a and b */
static COMPACT_25519_DECL void fprime_mul(uint8_t *r, const uint8_t *a, const uint8_t *b,
		const uint8_t *modulus);

#ifdef FULL_C25519_CODE
/* Compute multiplicative inverse. r must be distinct from a */
static COMPACT_25519_DECL void fprime_inv(uint8_t *r, const uint8_t *a, const uint8_t *modulus);
#endif
#endif
// ******* END:   c25519/fprime.h ********
// ******* BEGIN: c25519/sha512.h ********
/* SHA512
 * Daniel Beer <dlbeer@gmail.com>, 22 Apr 2014
 *
 * This file is in the public domain.
 */

#if !defined(COMPACT_DISABLE_ED25519) || !defined(COMPACT_DISABLE_X25519_DERIVE)
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* SHA512 state. State is updated as data is fed in, and then the final
 * hash can be read out in slices.
 *
 * Data is fed in as a sequence of full blocks terminated by a single
 * partial block.
 */
struct sha512_state {
	uint64_t  h[8];
};

/* Initial state */
COMPACT_25519_DECL extern const struct sha512_state sha512_initial_state;

/* Set up a new context */
static COMPACT_25519_DECL inline void sha512_init(struct sha512_state *s)
{
	memcpy(s, &sha512_initial_state, sizeof(*s));
}

/* Feed a full block in */
#define SHA512_BLOCK_SIZE  128

static COMPACT_25519_DECL void sha512_block(struct sha512_state *s, const uint8_t *blk);

/* Feed the last partial block in. The total stream size must be
 * specified. The size of the block given is assumed to be (total_size %
 * SHA512_BLOCK_SIZE). This might be zero, but you still need to call
 * this function to terminate the stream.
 */
static COMPACT_25519_DECL void sha512_final(struct sha512_state *s, const uint8_t *blk,
		  size_t total_size);

/* Fetch a slice of the hash result. */
#define SHA512_HASH_SIZE  64

static COMPACT_25519_DECL void sha512_get(const struct sha512_state *s, uint8_t *hash,
		unsigned int offset, unsigned int len);

#endif
// ******* END:   c25519/sha512.h ********
// ******* BEGIN: c25519/c25519.h ********
/* Curve25519 (Montgomery form)
 * Daniel Beer <dlbeer@gmail.com>, 18 Apr 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_X25519
#include <stdint.h>

/* Curve25519 has the equation over F(p = 2^255-19):
 *
 *    y^2 = x^3 + 486662x^2 + x
 *
 * 486662 = 4A+2, where A = 121665. This is a Montgomery curve.
 *
 * For more information, see:
 *
 *    Bernstein, D.J. (2006) "Curve25519: New Diffie-Hellman speed
 *    records". Document ID: 4230efdfa673480fc079449d90f322c0.
 */

/* This is the site of a Curve25519 exponent (private key) */
#define C25519_EXPONENT_SIZE  32

/* Having generated 32 random bytes, you should call this function to
 * finalize the generated key.
 */
static COMPACT_25519_DECL inline void c25519_prepare(uint8_t *key)
{
	key[0] &= 0xf8;
	key[31] &= 0x7f;
	key[31] |= 0x40;
}

/* X-coordinate of the base point */
COMPACT_25519_DECL extern const uint8_t c25519_base_x[F25519_SIZE];

/* X-coordinate scalar multiply: given the X-coordinate of q, return the
 * X-coordinate of e*q.
 *
 * result and q are field elements. e is an exponent.
 */
static COMPACT_25519_DECL void c25519_smult(uint8_t *result, const uint8_t *q, const uint8_t *e);
#endif
// ******* END:   c25519/c25519.h ********
// ******* BEGIN: c25519/ed25519.h ********
/* Edwards curve operations
 * Daniel Beer <dlbeer@gmail.com>, 9 Jan 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519

/* This is not the Ed25519 signature system. Rather, we're implementing
 * basic operations on the twisted Edwards curve over (Z mod 2^255-19):
 *
 *     -x^2 + y^2 = 1 - (121665/121666)x^2y^2
 *
 * With the positive-x base point y = 4/5.
 *
 * These functions will not leak secret data through timing.
 *
 * For more information, see:
 *
 *     Bernstein, D.J. & Lange, T. (2007) "Faster addition and doubling on
 *     elliptic curves". Document ID: 95616567a6ba20f575c5f25e7cebaf83.
 *
 *     Hisil, H. & Wong, K K. & Carter, G. & Dawson, E. (2008) "Twisted
 *     Edwards curves revisited". Advances in Cryptology, ASIACRYPT 2008,
 *     Vol. 5350, pp. 326-343.
 */

/* Projective coordinates */
struct ed25519_pt {
	uint8_t  x[F25519_SIZE];
	uint8_t  y[F25519_SIZE];
	uint8_t  t[F25519_SIZE];
	uint8_t  z[F25519_SIZE];
};

COMPACT_25519_DECL extern const struct ed25519_pt ed25519_base;
COMPACT_25519_DECL extern const struct ed25519_pt ed25519_neutral;

/* Convert between projective and affine coordinates (x/y in F25519) */
static COMPACT_25519_DECL void ed25519_project(struct ed25519_pt *p,
		     const uint8_t *x, const uint8_t *y);

static COMPACT_25519_DECL void ed25519_unproject(uint8_t *x, uint8_t *y,
		       const struct ed25519_pt *p);

/* Compress/uncompress points. try_unpack() will check that the
 * compressed point is on the curve, returning 1 if the unpacked point
 * is valid, and 0 otherwise.
 */
#define ED25519_PACK_SIZE  F25519_SIZE

static COMPACT_25519_DECL void ed25519_pack(uint8_t *c, const uint8_t *x, const uint8_t *y);
static COMPACT_25519_DECL uint8_t ed25519_try_unpack(uint8_t *x, uint8_t *y, const uint8_t *c);

/* Add, double and scalar multiply */
#define ED25519_EXPONENT_SIZE  32

/* Prepare an exponent by clamping appropriate bits */
static COMPACT_25519_DECL inline void ed25519_prepare(uint8_t *e)
{
	e[0] &= 0xf8;
	e[31] &= 0x7f;
	e[31] |= 0x40;
}

/* Order of the group generated by the base point */
static COMPACT_25519_DECL inline void ed25519_copy(struct ed25519_pt *dst,
				const struct ed25519_pt *src)
{
	memcpy(dst, src, sizeof(*dst));
}

static COMPACT_25519_DECL void ed25519_add(struct ed25519_pt *r,
		 const struct ed25519_pt *a, const struct ed25519_pt *b);
static COMPACT_25519_DECL void ed25519_double(struct ed25519_pt *r, const struct ed25519_pt *a);
static COMPACT_25519_DECL void ed25519_smult(struct ed25519_pt *r, const struct ed25519_pt *a,
		   const uint8_t *e);

#endif
// ******* END:   c25519/ed25519.h ********
// ******* BEGIN: c25519/edsign.h ********
/* Edwards curve signature system
 * Daniel Beer <dlbeer@gmail.com>, 22 Apr 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519
#include <stdint.h>
#include <stddef.h>

/* This is the Ed25519 signature system, as described in:
 *
 *     Daniel J. Bernstein, Niels Duif, Tanja Lange, Peter Schwabe, Bo-Yin
 *     Yang. High-speed high-security signatures. Journal of Cryptographic
 *     Engineering 2 (2012), 77-89. Document ID:
 *     a1a62a2f76d23f65d622484ddd09caf8. URL:
 *     http://cr.yp.to/papers.html#ed25519. Date: 2011.09.26.
 *
 * The format and calculation of signatures is compatible with the
 * Ed25519 implementation in SUPERCOP. Note, however, that our secret
 * keys are half the size: we don't store a copy of the public key in
 * the secret key (we generate it on demand).
 */

/* Any string of 32 random bytes is a valid secret key. There is no
 * clamping of bits, because we don't use the key directly as an
 * exponent (the exponent is derived from part of a key expansion).
 */
#define EDSIGN_SECRET_KEY_SIZE  32

/* Given a secret key, produce the public key (a packed Edwards-curve
 * point).
 */
#define EDSIGN_PUBLIC_KEY_SIZE  32

static COMPACT_25519_DECL void edsign_sec_to_pub(uint8_t *pub, const uint8_t *secret);

/* Produce a signature for a message. */
#define EDSIGN_SIGNATURE_SIZE  64

static COMPACT_25519_DECL void edsign_sign(uint8_t *signature, const uint8_t *pub,
		 const uint8_t *secret,
		 const uint8_t *message, size_t len);

/* Verify a message signature. Returns non-zero if ok. */
static COMPACT_25519_DECL uint8_t edsign_verify(const uint8_t *signature, const uint8_t *pub,
		      const uint8_t *message, size_t len);

#endif
// ******* END:   c25519/edsign.h ********
// ******* BEGIN: c25519/f25519.c ********
/* Arithmetic mod p = 2^255-19
 * Daniel Beer <dlbeer@gmail.com>, 5 Jan 2014
 *
 * This file is in the public domain.
 */

#ifdef FULL_C25519_CODE
COMPACT_25519_DECL const uint8_t f25519_zero[F25519_SIZE] = {0};
#endif
COMPACT_25519_DECL const uint8_t f25519_one[F25519_SIZE] = {1};

static COMPACT_25519_DECL void f25519_load(uint8_t *x, uint32_t c)
{
	unsigned int i;

	for (i = 0; i < sizeof(c); i++) {
		x[i] = c;
		c >>= 8;
	}

	for (; i < F25519_SIZE; i++)
		x[i] = 0;
}

static COMPACT_25519_DECL void f25519_normalize(uint8_t *x)
{
	uint8_t minusp[F25519_SIZE];
	uint16_t c;
	int i;

	/* Reduce using 2^255 = 19 mod p */
	c = (x[31] >> 7) * 19;
	x[31] &= 127;

	for (i = 0; i < F25519_SIZE; i++) {
		c += x[i];
		x[i] = c;
		c >>= 8;
	}

	/* The number is now less than 2^255 + 18, and therefore less than
	 * 2p. Try subtracting p, and conditionally load the subtracted
	 * value if underflow did not occur.
	 */
	c = 19;

	for (i = 0; i + 1 < F25519_SIZE; i++) {
		c += x[i];
		minusp[i] = c;
		c >>= 8;
	}

	c += ((uint16_t)x[i]) - 128;
	minusp[31] = c;

	/* Load x-p if no underflow */
	f25519_select(x, minusp, x, (c >> 15) & 1);
}

static COMPACT_25519_DECL uint8_t f25519_eq(const uint8_t *x, const uint8_t *y)
{
	uint8_t sum = 0;
	int i;

	for (i = 0; i < F25519_SIZE; i++)
		sum |= x[i] ^ y[i];

	sum |= (sum >> 4);
	sum |= (sum >> 2);
	sum |= (sum >> 1);

	return (sum ^ 1) & 1;
}

static COMPACT_25519_DECL void f25519_select(uint8_t *dst,
		   const uint8_t *zero, const uint8_t *one,
		   uint8_t condition)
{
	const uint8_t mask = -condition;
	int i;

	for (i = 0; i < F25519_SIZE; i++)
		dst[i] = zero[i] ^ (mask & (one[i] ^ zero[i]));
}

static COMPACT_25519_DECL void f25519_add(uint8_t *r, const uint8_t *a, const uint8_t *b)
{
	uint16_t c = 0;
	int i;

	/* Add */
	for (i = 0; i < F25519_SIZE; i++) {
		c >>= 8;
		c += ((uint16_t)a[i]) + ((uint16_t)b[i]);
		r[i] = c;
	}

	/* Reduce with 2^255 = 19 mod p */
	r[31] &= 127;
	c = (c >> 7) * 19;

	for (i = 0; i < F25519_SIZE; i++) {
		c += r[i];
		r[i] = c;
		c >>= 8;
	}
}

static COMPACT_25519_DECL void f25519_sub(uint8_t *r, const uint8_t *a, const uint8_t *b)
{
	uint32_t c = 0;
	int i;

	/* Calculate a + 2p - b, to avoid underflow */
	c = 218;
	for (i = 0; i + 1 < F25519_SIZE; i++) {
		c += 65280 + ((uint32_t)a[i]) - ((uint32_t)b[i]);
		r[i] = c;
		c >>= 8;
	}

	c += ((uint32_t)a[31]) - ((uint32_t)b[31]);
	r[31] = c & 127;
	c = (c >> 7) * 19;

	for (i = 0; i < F25519_SIZE; i++) {
		c += r[i];
		r[i] = c;
		c >>= 8;
	}
}

static COMPACT_25519_DECL void f25519_neg(uint8_t *r, const uint8_t *a)
{
	uint32_t c = 0;
	int i;

	/* Calculate 2p - a, to avoid underflow */
	c = 218;
	for (i = 0; i + 1 < F25519_SIZE; i++) {
		c += 65280 - ((uint32_t)a[i]);
		r[i] = c;
		c >>= 8;
	}

	c -= ((uint32_t)a[31]);
	r[31] = c & 127;
	c = (c >> 7) * 19;

	for (i = 0; i < F25519_SIZE; i++) {
		c += r[i];
		r[i] = c;
		c >>= 8;
	}
}

static COMPACT_25519_DECL void f25519_mul__distinct(uint8_t *r, const uint8_t *a, const uint8_t *b)
{
	uint32_t c = 0;
	int i;

	for (i = 0; i < F25519_SIZE; i++) {
		int j;

		c >>= 8;
		for (j = 0; j <= i; j++)
			c += ((uint32_t)a[j]) * ((uint32_t)b[i - j]);

		for (; j < F25519_SIZE; j++)
			c += ((uint32_t)a[j]) *
			     ((uint32_t)b[i + F25519_SIZE - j]) * 38;

		r[i] = c;
	}

	r[31] &= 127;
	c = (c >> 7) * 19;

	for (i = 0; i < F25519_SIZE; i++) {
		c += r[i];
		r[i] = c;
		c >>= 8;
	}
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void f25519_mul(uint8_t *r, const uint8_t *a, const uint8_t *b)
{
	uint8_t tmp[F25519_SIZE];

	f25519_mul__distinct(tmp, a, b);
	f25519_copy(r, tmp);
}
#endif

static COMPACT_25519_DECL void f25519_mul_c(uint8_t *r, const uint8_t *a, uint32_t b)
{
	uint32_t c = 0;
	int i;

	for (i = 0; i < F25519_SIZE; i++) {
		c >>= 8;
		c += b * ((uint32_t)a[i]);
		r[i] = c;
	}

	r[31] &= 127;
	c >>= 7;
	c *= 19;

	for (i = 0; i < F25519_SIZE; i++) {
		c += r[i];
		r[i] = c;
		c >>= 8;
	}
}

static COMPACT_25519_DECL void f25519_inv__distinct(uint8_t *r, const uint8_t *x)
{
	uint8_t s[F25519_SIZE];
	int i;

	/* This is a prime field, so by Fermat's little theorem:
	 *
	 *     x^(p-1) = 1 mod p
	 *
	 * Therefore, raise to (p-2) = 2^255-21 to get a multiplicative
	 * inverse.
	 *
	 * This is a 255-bit binary number with the digits:
	 *
	 *     11111111... 01011
	 *
	 * We compute the result by the usual binary chain, but
	 * alternate between keeping the accumulator in r and s, so as
	 * to avoid copying temporaries.
	 */

	/* 1 1 */
	f25519_mul__distinct(s, x, x);
	f25519_mul__distinct(r, s, x);

	/* 1 x 248 */
	for (i = 0; i < 248; i++) {
		f25519_mul__distinct(s, r, r);
		f25519_mul__distinct(r, s, x);
	}

	/* 0 */
	f25519_mul__distinct(s, r, r);

	/* 1 */
	f25519_mul__distinct(r, s, s);
	f25519_mul__distinct(s, r, x);

	/* 0 */
	f25519_mul__distinct(r, s, s);

	/* 1 */
	f25519_mul__distinct(s, r, r);
	f25519_mul__distinct(r, s, x);

	/* 1 */
	f25519_mul__distinct(s, r, r);
	f25519_mul__distinct(r, s, x);
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void f25519_inv(uint8_t *r, const uint8_t *x)
{
	uint8_t tmp[F25519_SIZE];

	f25519_inv__distinct(tmp, x);
	f25519_copy(r, tmp);
}
#endif

/* Raise x to the power of (p-5)/8 = 2^252-3, using s for temporary
 * storage.
 */
static COMPACT_25519_DECL void exp2523(uint8_t *r, const uint8_t *x, uint8_t *s)
{
	int i;

	/* This number is a 252-bit number with the binary expansion:
	 *
	 *     111111... 01
	 */

	/* 1 1 */
	f25519_mul__distinct(r, x, x);
	f25519_mul__distinct(s, r, x);

	/* 1 x 248 */
	for (i = 0; i < 248; i++) {
		f25519_mul__distinct(r, s, s);
		f25519_mul__distinct(s, r, x);
	}

	/* 0 */
	f25519_mul__distinct(r, s, s);

	/* 1 */
	f25519_mul__distinct(s, r, r);
	f25519_mul__distinct(r, s, x);
}

static COMPACT_25519_DECL void f25519_sqrt(uint8_t *r, const uint8_t *a)
{
	uint8_t v[F25519_SIZE];
	uint8_t i[F25519_SIZE];
	uint8_t x[F25519_SIZE];
	uint8_t y[F25519_SIZE];

	/* v = (2a)^((p-5)/8) [x = 2a] */
	f25519_mul_c(x, a, 2);
	exp2523(v, x, y);

	/* i = 2av^2 - 1 */
	f25519_mul__distinct(y, v, v);
	f25519_mul__distinct(i, x, y);
	f25519_load(y, 1);
	f25519_sub(i, i, y);

	/* r = avi */
	f25519_mul__distinct(x, v, a);
	f25519_mul__distinct(r, x, i);
}
// ******* END:   c25519/f25519.c ********
// ******* BEGIN: c25519/fprime.c ********
/* Arithmetic in prime fields
 * Daniel Beer <dlbeer@gmail.com>, 10 Jan 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519
#ifdef FULL_C25519_CODE
COMPACT_25519_DECL const uint8_t fprime_zero[FPRIME_SIZE] = {0};
COMPACT_25519_DECL const uint8_t fprime_one[FPRIME_SIZE] = {1};
#endif

static COMPACT_25519_DECL void raw_add(uint8_t *x, const uint8_t *p)
{
	uint16_t c = 0;
	int i;

	for (i = 0; i < FPRIME_SIZE; i++) {
		c += ((uint16_t)x[i]) + ((uint16_t)p[i]);
		x[i] = c;
		c >>= 8;
	}
}

static COMPACT_25519_DECL void raw_try_sub(uint8_t *x, const uint8_t *p)
{
	uint8_t minusp[FPRIME_SIZE];
	uint16_t c = 0;
	int i;

	for (i = 0; i < FPRIME_SIZE; i++) {
		c = ((uint16_t)x[i]) - ((uint16_t)p[i]) - c;
		minusp[i] = c;
		c = (c >> 8) & 1;
	}

	fprime_select(x, minusp, x, c);
}

/* Warning: this function is variable-time */
static COMPACT_25519_DECL int prime_msb(const uint8_t *p)
{
	int i;
	uint8_t x;

	for (i = FPRIME_SIZE - 1; i >= 0; i--)
		if (p[i])
			break;

	x = p[i];
	i <<= 3;

	while (x) {
		x >>= 1;
		i++;
	}

	return i - 1;
}

/* Warning: this function may be variable-time in the argument n */
static COMPACT_25519_DECL void shift_n_bits(uint8_t *x, int n)
{
	uint16_t c = 0;
	int i;

	for (i = 0; i < FPRIME_SIZE; i++) {
		c |= ((uint16_t)x[i]) << n;
		x[i] = c;
		c >>= 8;
	}
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void fprime_load(uint8_t *x, uint32_t c)
{
	unsigned int i;

	for (i = 0; i < sizeof(c); i++) {
		x[i] = c;
		c >>= 8;
	}

	for (; i < FPRIME_SIZE; i++)
		x[i] = 0;
}
#endif

static COMPACT_25519_DECL inline int min_int(int a, int b)
{
	return a < b ? a : b;
}

static COMPACT_25519_DECL void fprime_from_bytes(uint8_t *n,
		       const uint8_t *x, size_t len,
		       const uint8_t *modulus)
{
	const int preload_total = min_int(prime_msb(modulus) - 1, len << 3);
	const int preload_bytes = preload_total >> 3;
	const int preload_bits = preload_total & 7;
	const int rbits = (len << 3) - preload_total;
	int i;

	memset(n, 0, FPRIME_SIZE);

	for (i = 0; i < preload_bytes; i++)
		n[i] = x[len - preload_bytes + i];

	if (preload_bits) {
		shift_n_bits(n, preload_bits);
		n[0] |= x[len - preload_bytes - 1] >> (8 - preload_bits);
	}

	for (i = rbits - 1; i >= 0; i--) {
		const uint8_t bit = (x[i >> 3] >> (i & 7)) & 1;

		shift_n_bits(n, 1);
		n[0] |= bit;
		raw_try_sub(n, modulus);
	}
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void fprime_normalize(uint8_t *x, const uint8_t *modulus)
{
	uint8_t n[FPRIME_SIZE];

	fprime_from_bytes(n, x, FPRIME_SIZE, modulus);
	fprime_copy(x, n);
}

static COMPACT_25519_DECL uint8_t fprime_eq(const uint8_t *x, const uint8_t *y)
{
	uint8_t sum = 0;
	int i;

	for (i = 0; i < FPRIME_SIZE; i++)
		sum |= x[i] ^ y[i];

	sum |= (sum >> 4);
	sum |= (sum >> 2);
	sum |= (sum >> 1);

	return (sum ^ 1) & 1;
}
#endif
static COMPACT_25519_DECL void fprime_select(uint8_t *dst,
		   const uint8_t *zero, const uint8_t *one,
		   uint8_t condition)
{
	const uint8_t mask = -condition;
	int i;

	for (i = 0; i < FPRIME_SIZE; i++)
		dst[i] = zero[i] ^ (mask & (one[i] ^ zero[i]));
}

static COMPACT_25519_DECL void fprime_add(uint8_t *r, const uint8_t *a, const uint8_t *modulus)
{
	raw_add(r, a);
	raw_try_sub(r, modulus);
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void fprime_sub(uint8_t *r, const uint8_t *a, const uint8_t *modulus)
{
	raw_add(r, modulus);
	raw_try_sub(r, a);
	raw_try_sub(r, modulus);
}
#endif

static COMPACT_25519_DECL void fprime_mul(uint8_t *r, const uint8_t *a, const uint8_t *b,
		const uint8_t *modulus)
{
	int i;

	memset(r, 0, FPRIME_SIZE);

	for (i = prime_msb(modulus); i >= 0; i--) {
		const uint8_t bit = (b[i >> 3] >> (i & 7)) & 1;
		uint8_t plusa[FPRIME_SIZE];

		shift_n_bits(r, 1);
		raw_try_sub(r, modulus);

		fprime_copy(plusa, r);
		fprime_add(plusa, a, modulus);

		fprime_select(r, r, plusa, bit);
	}
}

#ifdef FULL_C25519_CODE
static COMPACT_25519_DECL void fprime_inv(uint8_t *r, const uint8_t *a, const uint8_t *modulus)
{
	uint8_t pm2[FPRIME_SIZE];
	uint16_t c = 2;
	int i;

	/* Compute (p-2) */
	fprime_copy(pm2, modulus);
	for (i = 0; i < FPRIME_SIZE; i++) {
		c = modulus[i] - c;
		pm2[i] = c;
		c >>= 8;
	}

	/* Binary exponentiation */
	fprime_load(r, 1);

	for (i = prime_msb(modulus); i >= 0; i--) {
		uint8_t r2[FPRIME_SIZE];

		fprime_mul(r2, r, r, modulus);

		if ((pm2[i >> 3] >> (i & 7)) & 1)
			fprime_mul(r, r2, a, modulus);
		else
			fprime_copy(r, r2);
	}
}
#endif
#endif
// ******* END:   c25519/fprime.c ********
// ******* BEGIN: c25519/sha512.c ********
/* SHA512
 * Daniel Beer <dlbeer@gmail.com>, 22 Apr 2014
 *
 * This file is in the public domain.
 */

#if !defined(COMPACT_DISABLE_ED25519) || !defined(COMPACT_DISABLE_X25519_DERIVE)
COMPACT_25519_DECL const struct sha512_state sha512_initial_state = { {
	0x6a09e667f3bcc908LL, 0xbb67ae8584caa73bLL,
	0x3c6ef372fe94f82bLL, 0xa54ff53a5f1d36f1LL,
	0x510e527fade682d1LL, 0x9b05688c2b3e6c1fLL,
	0x1f83d9abfb41bd6bLL, 0x5be0cd19137e2179LL,
} };

COMPACT_25519_DECL const uint64_t round_k[80] = {
	0x428a2f98d728ae22LL, 0x7137449123ef65cdLL,
	0xb5c0fbcfec4d3b2fLL, 0xe9b5dba58189dbbcLL,
	0x3956c25bf348b538LL, 0x59f111f1b605d019LL,
	0x923f82a4af194f9bLL, 0xab1c5ed5da6d8118LL,
	0xd807aa98a3030242LL, 0x12835b0145706fbeLL,
	0x243185be4ee4b28cLL, 0x550c7dc3d5ffb4e2LL,
	0x72be5d74f27b896fLL, 0x80deb1fe3b1696b1LL,
	0x9bdc06a725c71235LL, 0xc19bf174cf692694LL,
	0xe49b69c19ef14ad2LL, 0xefbe4786384f25e3LL,
	0x0fc19dc68b8cd5b5LL, 0x240ca1cc77ac9c65LL,
	0x2de92c6f592b0275LL, 0x4a7484aa6ea6e483LL,
	0x5cb0a9dcbd41fbd4LL, 0x76f988da831153b5LL,
	0x983e5152ee66dfabLL, 0xa831c66d2db43210LL,
	0xb00327c898fb213fLL, 0xbf597fc7beef0ee4LL,
	0xc6e00bf33da88fc2LL, 0xd5a79147930aa725LL,
	0x06ca6351e003826fLL, 0x142929670a0e6e70LL,
	0x27b70a8546d22ffcLL, 0x2e1b21385c26c926LL,
	0x4d2c6dfc5ac42aedLL, 0x53380d139d95b3dfLL,
	0x650a73548baf63deLL, 0x766a0abb3c77b2a8LL,
	0x81c2c92e47edaee6LL, 0x92722c851482353bLL,
	0xa2bfe8a14cf10364LL, 0xa81a664bbc423001LL,
	0xc24b8b70d0f89791LL, 0xc76c51a30654be30LL,
	0xd192e819d6ef5218LL, 0xd69906245565a910LL,
	0xf40e35855771202aLL, 0x106aa07032bbd1b8LL,
	0x19a4c116b8d2d0c8LL, 0x1e376c085141ab53LL,
	0x2748774cdf8eeb99LL, 0x34b0bcb5e19b48a8LL,
	0x391c0cb3c5c95a63LL, 0x4ed8aa4ae3418acbLL,
	0x5b9cca4f7763e373LL, 0x682e6ff3d6b2b8a3LL,
	0x748f82ee5defb2fcLL, 0x78a5636f43172f60LL,
	0x84c87814a1f0ab72LL, 0x8cc702081a6439ecLL,
	0x90befffa23631e28LL, 0xa4506cebde82bde9LL,
	0xbef9a3f7b2c67915LL, 0xc67178f2e372532bLL,
	0xca273eceea26619cLL, 0xd186b8c721c0c207LL,
	0xeada7dd6cde0eb1eLL, 0xf57d4f7fee6ed178LL,
	0x06f067aa72176fbaLL, 0x0a637dc5a2c898a6LL,
	0x113f9804bef90daeLL, 0x1b710b35131c471bLL,
	0x28db77f523047d84LL, 0x32caab7b40c72493LL,
	0x3c9ebe0a15c9bebcLL, 0x431d67c49c100d4cLL,
	0x4cc5d4becb3e42b6LL, 0x597f299cfc657e2aLL,
	0x5fcb6fab3ad6faecLL, 0x6c44198c4a475817LL,
};

static COMPACT_25519_DECL inline uint64_t load64(const uint8_t *x)
{
	uint64_t r;

	r = *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);
	r = (r << 8) | *(x++);

	return r;
}

static COMPACT_25519_DECL inline void store64(uint8_t *x, uint64_t v)
{
	x += 7;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
	v >>= 8;
	*(x--) = v;
}

static COMPACT_25519_DECL inline uint64_t rot64(uint64_t x, int bits)
{
	return (x >> bits) | (x << (64 - bits));
}

static COMPACT_25519_DECL void sha512_block(struct sha512_state *s, const uint8_t *blk)
{
	uint64_t w[16];
	uint64_t a, b, c, d, e, f, g, h;
	int i;

	for (i = 0; i < 16; i++) {
		w[i] = load64(blk);
		blk += 8;
	}

	/* Load state */
	a = s->h[0];
	b = s->h[1];
	c = s->h[2];
	d = s->h[3];
	e = s->h[4];
	f = s->h[5];
	g = s->h[6];
	h = s->h[7];

	for (i = 0; i < 80; i++) {
		/* Compute value of w[i + 16]. w[wrap(i)] is currently w[i] */
		const uint64_t wi = w[i & 15];
		const uint64_t wi15 = w[(i + 1) & 15];
		const uint64_t wi2 = w[(i + 14) & 15];
		const uint64_t wi7 = w[(i + 9) & 15];
		const uint64_t s0 =
			rot64(wi15, 1) ^ rot64(wi15, 8) ^ (wi15 >> 7);
		const uint64_t s1 =
			rot64(wi2, 19) ^ rot64(wi2, 61) ^ (wi2 >> 6);

		/* Round calculations */
		const uint64_t S0 = rot64(a, 28) ^ rot64(a, 34) ^ rot64(a, 39);
		const uint64_t S1 = rot64(e, 14) ^ rot64(e, 18) ^ rot64(e, 41);
		const uint64_t ch = (e & f) ^ ((~e) & g);
		const uint64_t temp1 = h + S1 + ch + round_k[i] + wi;
		const uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
		const uint64_t temp2 = S0 + maj;

		/* Update round state */
		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;

		/* w[wrap(i)] becomes w[i + 16] */
		w[i & 15] = wi + s0 + wi7 + s1;
	}

	/* Store state */
	s->h[0] += a;
	s->h[1] += b;
	s->h[2] += c;
	s->h[3] += d;
	s->h[4] += e;
	s->h[5] += f;
	s->h[6] += g;
	s->h[7] += h;
}

static COMPACT_25519_DECL void sha512_final(struct sha512_state *s, const uint8_t *blk,
		  size_t total_size)
{
	uint8_t temp[SHA512_BLOCK_SIZE] = {0};
	const size_t last_size = total_size & (SHA512_BLOCK_SIZE - 1);

	if (last_size)
		memcpy(temp, blk, last_size);
	temp[last_size] = 0x80;

	if (last_size > 111) {
		sha512_block(s, temp);
		memset(temp, 0, sizeof(temp));
	}

	/* Note: we assume total_size fits in 61 bits */
	store64(temp + SHA512_BLOCK_SIZE - 8, total_size << 3);
	sha512_block(s, temp);
}

static COMPACT_25519_DECL void sha512_get(const struct sha512_state *s, uint8_t *hash,
		unsigned int offset, unsigned int len)
{
	int i;

	if (offset > SHA512_BLOCK_SIZE)
		return;

	if (len > SHA512_BLOCK_SIZE - offset)
		len = SHA512_BLOCK_SIZE - offset;

	/* Skip whole words */
	i = offset >> 3;
	offset &= 7;

	/* Skip/read out bytes */
	if (offset) {
		uint8_t tmp[8];
		unsigned int c = 8 - offset;

		if (c > len)
			c = len;

		store64(tmp, s->h[i++]);
		memcpy(hash, tmp + offset, c);
		len -= c;
		hash += c;
	}

	/* Read out whole words */
	while (len >= 8) {
		store64(hash, s->h[i++]);
		hash += 8;
		len -= 8;
	}

	/* Read out bytes */
	if (len) {
		uint8_t tmp[8];

		store64(tmp, s->h[i]);
		memcpy(hash, tmp, len);
	}
}
#endif
// ******* END:   c25519/sha512.c ********
// ******* BEGIN: c25519/c25519.c ********
/* Curve25519 (Montgomery form)
 * Daniel Beer <dlbeer@gmail.com>, 18 Apr 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_X25519
COMPACT_25519_DECL const uint8_t c25519_base_x[F25519_SIZE] = {9};

/* Double an X-coordinate */
static COMPACT_25519_DECL void xc_double(uint8_t *x3, uint8_t *z3,
		      const uint8_t *x1, const uint8_t *z1)
{
	/* Explicit formulas database: dbl-1987-m
	 *
	 * source 1987 Montgomery "Speeding the Pollard and elliptic
	 *   curve methods of factorization", page 261, fourth display
	 * compute X3 = (X1^2-Z1^2)^2
	 * compute Z3 = 4 X1 Z1 (X1^2 + a X1 Z1 + Z1^2)
	 */
	uint8_t x1sq[F25519_SIZE];
	uint8_t z1sq[F25519_SIZE];
	uint8_t x1z1[F25519_SIZE];
	uint8_t a[F25519_SIZE];

	f25519_mul__distinct(x1sq, x1, x1);
	f25519_mul__distinct(z1sq, z1, z1);
	f25519_mul__distinct(x1z1, x1, z1);

	f25519_sub(a, x1sq, z1sq);
	f25519_mul__distinct(x3, a, a);

	f25519_mul_c(a, x1z1, 486662);
	f25519_add(a, x1sq, a);
	f25519_add(a, z1sq, a);
	f25519_mul__distinct(x1sq, x1z1, a);
	f25519_mul_c(z3, x1sq, 4);
}

/* Differential addition */
static COMPACT_25519_DECL void xc_diffadd(uint8_t *x5, uint8_t *z5,
		       const uint8_t *x1, const uint8_t *z1,
		       const uint8_t *x2, const uint8_t *z2,
		       const uint8_t *x3, const uint8_t *z3)
{
	/* Explicit formulas database: dbl-1987-m3
	 *
	 * source 1987 Montgomery "Speeding the Pollard and elliptic curve
	 *   methods of factorization", page 261, fifth display, plus
	 *   common-subexpression elimination
	 * compute A = X2+Z2
	 * compute B = X2-Z2
	 * compute C = X3+Z3
	 * compute D = X3-Z3
	 * compute DA = D A
	 * compute CB = C B
	 * compute X5 = Z1(DA+CB)^2
	 * compute Z5 = X1(DA-CB)^2
	 */
	uint8_t da[F25519_SIZE];
	uint8_t cb[F25519_SIZE];
	uint8_t a[F25519_SIZE];
	uint8_t b[F25519_SIZE];

	f25519_add(a, x2, z2);
	f25519_sub(b, x3, z3); /* D */
	f25519_mul__distinct(da, a, b);

	f25519_sub(b, x2, z2);
	f25519_add(a, x3, z3); /* C */
	f25519_mul__distinct(cb, a, b);

	f25519_add(a, da, cb);
	f25519_mul__distinct(b, a, a);
	f25519_mul__distinct(x5, z1, b);

	f25519_sub(a, da, cb);
	f25519_mul__distinct(b, a, a);
	f25519_mul__distinct(z5, x1, b);
}

static COMPACT_25519_DECL void c25519_smult(uint8_t *result, const uint8_t *q, const uint8_t *e)
{
	/* Current point: P_m */
	uint8_t xm[F25519_SIZE];
	uint8_t zm[F25519_SIZE] = {1};

	/* Predecessor: P_(m-1) */
	uint8_t xm1[F25519_SIZE] = {1};
	uint8_t zm1[F25519_SIZE] = {0};

	int i;

	/* Note: bit 254 is assumed to be 1 */
	f25519_copy(xm, q);

	for (i = 253; i >= 0; i--) {
		const int bit = (e[i >> 3] >> (i & 7)) & 1;
		uint8_t xms[F25519_SIZE];
		uint8_t zms[F25519_SIZE];

		/* From P_m and P_(m-1), compute P_(2m) and P_(2m-1) */
		xc_diffadd(xm1, zm1, q, f25519_one, xm, zm, xm1, zm1);
		xc_double(xm, zm, xm, zm);

		/* Compute P_(2m+1) */
		xc_diffadd(xms, zms, xm1, zm1, xm, zm, q, f25519_one);

		/* Select:
		 *   bit = 1 --> (P_(2m+1), P_(2m))
		 *   bit = 0 --> (P_(2m), P_(2m-1))
		 */
		f25519_select(xm1, xm1, xm, bit);
		f25519_select(zm1, zm1, zm, bit);
		f25519_select(xm, xm, xms, bit);
		f25519_select(zm, zm, zms, bit);
	}

	/* Freeze out of projective coordinates */
	f25519_inv__distinct(zm1, zm);
	f25519_mul__distinct(result, zm1, xm);
	f25519_normalize(result);
}
#endif
// ******* END:   c25519/c25519.c ********
// ******* BEGIN: c25519/ed25519.c ********
/* Edwards curve operations
 * Daniel Beer <dlbeer@gmail.com>, 9 Jan 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519

/* Base point is (numbers wrapped):
 *
 *     x = 151122213495354007725011514095885315114
 *         54012693041857206046113283949847762202
 *     y = 463168356949264781694283940034751631413
 *         07993866256225615783033603165251855960
 *
 * y is derived by transforming the original Montgomery base (u=9). x
 * is the corresponding positive coordinate for the new curve equation.
 * t is x*y.
 */
COMPACT_25519_DECL const struct ed25519_pt ed25519_base = {
	.x = {
		0x1a, 0xd5, 0x25, 0x8f, 0x60, 0x2d, 0x56, 0xc9,
		0xb2, 0xa7, 0x25, 0x95, 0x60, 0xc7, 0x2c, 0x69,
		0x5c, 0xdc, 0xd6, 0xfd, 0x31, 0xe2, 0xa4, 0xc0,
		0xfe, 0x53, 0x6e, 0xcd, 0xd3, 0x36, 0x69, 0x21
	},
	.y = {
		0x58, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
		0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66
	},
	.t = {
		0xa3, 0xdd, 0xb7, 0xa5, 0xb3, 0x8a, 0xde, 0x6d,
		0xf5, 0x52, 0x51, 0x77, 0x80, 0x9f, 0xf0, 0x20,
		0x7d, 0xe3, 0xab, 0x64, 0x8e, 0x4e, 0xea, 0x66,
		0x65, 0x76, 0x8b, 0xd7, 0x0f, 0x5f, 0x87, 0x67
	},
	.z = {1, 0}
};

COMPACT_25519_DECL const struct ed25519_pt ed25519_neutral = {
	.x = {0},
	.y = {1, 0},
	.t = {0},
	.z = {1, 0}
};

/* Conversion to and from projective coordinates */
static COMPACT_25519_DECL void ed25519_project(struct ed25519_pt *p,
		     const uint8_t *x, const uint8_t *y)
{
	f25519_copy(p->x, x);
	f25519_copy(p->y, y);
	f25519_load(p->z, 1);
	f25519_mul__distinct(p->t, x, y);
}

static COMPACT_25519_DECL void ed25519_unproject(uint8_t *x, uint8_t *y,
		       const struct ed25519_pt *p)
{
	uint8_t z1[F25519_SIZE];

	f25519_inv__distinct(z1, p->z);
	f25519_mul__distinct(x, p->x, z1);
	f25519_mul__distinct(y, p->y, z1);

	f25519_normalize(x);
	f25519_normalize(y);
}

/* Compress/uncompress points. We compress points by storing the x
 * coordinate and the parity of the y coordinate.
 *
 * Rearranging the curve equation, we obtain explicit formulae for the
 * coordinates:
 *
 *     x = sqrt((y^2-1) / (1+dy^2))
 *     y = sqrt((x^2+1) / (1-dx^2))
 *
 * Where d = (-121665/121666), or:
 *
 *     d = 370957059346694393431380835087545651895
 *         42113879843219016388785533085940283555
 */

COMPACT_25519_DECL const uint8_t ed25519_d[F25519_SIZE] = {
	0xa3, 0x78, 0x59, 0x13, 0xca, 0x4d, 0xeb, 0x75,
	0xab, 0xd8, 0x41, 0x41, 0x4d, 0x0a, 0x70, 0x00,
	0x98, 0xe8, 0x79, 0x77, 0x79, 0x40, 0xc7, 0x8c,
	0x73, 0xfe, 0x6f, 0x2b, 0xee, 0x6c, 0x03, 0x52
};

static COMPACT_25519_DECL void ed25519_pack(uint8_t *c, const uint8_t *x, const uint8_t *y)
{
	uint8_t tmp[F25519_SIZE];
	uint8_t parity;

	f25519_copy(tmp, x);
	f25519_normalize(tmp);
	parity = (tmp[0] & 1) << 7;

	f25519_copy(c, y);
	f25519_normalize(c);
	c[31] |= parity;
}

static COMPACT_25519_DECL uint8_t ed25519_try_unpack(uint8_t *x, uint8_t *y, const uint8_t *comp)
{
	const int parity = comp[31] >> 7;
	uint8_t a[F25519_SIZE];
	uint8_t b[F25519_SIZE];
	uint8_t c[F25519_SIZE];

	/* Unpack y */
	f25519_copy(y, comp);
	y[31] &= 127;

	/* Compute c = y^2 */
	f25519_mul__distinct(c, y, y);

	/* Compute b = (1+dy^2)^-1 */
	f25519_mul__distinct(b, c, ed25519_d);
	f25519_add(a, b, f25519_one);
	f25519_inv__distinct(b, a);

	/* Compute a = y^2-1 */
	f25519_sub(a, c, f25519_one);

	/* Compute c = a*b = (y^2-1)/(1-dy^2) */
	f25519_mul__distinct(c, a, b);

	/* Compute a, b = +/-sqrt(c), if c is square */
	f25519_sqrt(a, c);
	f25519_neg(b, a);

	/* Select one of them, based on the compressed parity bit */
	f25519_select(x, a, b, (a[0] ^ parity) & 1);

	/* Verify that x^2 = c */
	f25519_mul__distinct(a, x, x);
	f25519_normalize(a);
	f25519_normalize(c);

	return f25519_eq(a, c);
}

/* k = 2d */
COMPACT_25519_DECL const uint8_t ed25519_k[F25519_SIZE] = {
	0x59, 0xf1, 0xb2, 0x26, 0x94, 0x9b, 0xd6, 0xeb,
	0x56, 0xb1, 0x83, 0x82, 0x9a, 0x14, 0xe0, 0x00,
	0x30, 0xd1, 0xf3, 0xee, 0xf2, 0x80, 0x8e, 0x19,
	0xe7, 0xfc, 0xdf, 0x56, 0xdc, 0xd9, 0x06, 0x24
};

static COMPACT_25519_DECL void ed25519_add(struct ed25519_pt *r,
		 const struct ed25519_pt *p1, const struct ed25519_pt *p2)
{
	/* Explicit formulas database: add-2008-hwcd-3
	 *
	 * source 2008 Hisil--Wong--Carter--Dawson,
	 *     http://eprint.iacr.org/2008/522, Section 3.1
	 * appliesto extended-1
	 * parameter k
	 * assume k = 2 d
	 * compute A = (Y1-X1)(Y2-X2)
	 * compute B = (Y1+X1)(Y2+X2)
	 * compute C = T1 k T2
	 * compute D = Z1 2 Z2
	 * compute E = B - A
	 * compute F = D - C
	 * compute G = D + C
	 * compute H = B + A
	 * compute X3 = E F
	 * compute Y3 = G H
	 * compute T3 = E H
	 * compute Z3 = F G
	 */
	uint8_t a[F25519_SIZE];
	uint8_t b[F25519_SIZE];
	uint8_t c[F25519_SIZE];
	uint8_t d[F25519_SIZE];
	uint8_t e[F25519_SIZE];
	uint8_t f[F25519_SIZE];
	uint8_t g[F25519_SIZE];
	uint8_t h[F25519_SIZE];

	/* A = (Y1-X1)(Y2-X2) */
	f25519_sub(c, p1->y, p1->x);
	f25519_sub(d, p2->y, p2->x);
	f25519_mul__distinct(a, c, d);

	/* B = (Y1+X1)(Y2+X2) */
	f25519_add(c, p1->y, p1->x);
	f25519_add(d, p2->y, p2->x);
	f25519_mul__distinct(b, c, d);

	/* C = T1 k T2 */
	f25519_mul__distinct(d, p1->t, p2->t);
	f25519_mul__distinct(c, d, ed25519_k);

	/* D = Z1 2 Z2 */
	f25519_mul__distinct(d, p1->z, p2->z);
	f25519_add(d, d, d);

	/* E = B - A */
	f25519_sub(e, b, a);

	/* F = D - C */
	f25519_sub(f, d, c);

	/* G = D + C */
	f25519_add(g, d, c);

	/* H = B + A */
	f25519_add(h, b, a);

	/* X3 = E F */
	f25519_mul__distinct(r->x, e, f);

	/* Y3 = G H */
	f25519_mul__distinct(r->y, g, h);

	/* T3 = E H */
	f25519_mul__distinct(r->t, e, h);

	/* Z3 = F G */
	f25519_mul__distinct(r->z, f, g);
}

static COMPACT_25519_DECL void ed25519_double(struct ed25519_pt *r, const struct ed25519_pt *p)
{
	/* Explicit formulas database: dbl-2008-hwcd
	 *
	 * source 2008 Hisil--Wong--Carter--Dawson,
	 *     http://eprint.iacr.org/2008/522, Section 3.3
	 * compute A = X1^2
	 * compute B = Y1^2
	 * compute C = 2 Z1^2
	 * compute D = a A
	 * compute E = (X1+Y1)^2-A-B
	 * compute G = D + B
	 * compute F = G - C
	 * compute H = D - B
	 * compute X3 = E F
	 * compute Y3 = G H
	 * compute T3 = E H
	 * compute Z3 = F G
	 */
	uint8_t a[F25519_SIZE];
	uint8_t b[F25519_SIZE];
	uint8_t c[F25519_SIZE];
	uint8_t e[F25519_SIZE];
	uint8_t f[F25519_SIZE];
	uint8_t g[F25519_SIZE];
	uint8_t h[F25519_SIZE];

	/* A = X1^2 */
	f25519_mul__distinct(a, p->x, p->x);

	/* B = Y1^2 */
	f25519_mul__distinct(b, p->y, p->y);

	/* C = 2 Z1^2 */
	f25519_mul__distinct(c, p->z, p->z);
	f25519_add(c, c, c);

	/* D = a A (alter sign) */
	/* E = (X1+Y1)^2-A-B */
	f25519_add(f, p->x, p->y);
	f25519_mul__distinct(e, f, f);
	f25519_sub(e, e, a);
	f25519_sub(e, e, b);

	/* G = D + B */
	f25519_sub(g, b, a);

	/* F = G - C */
	f25519_sub(f, g, c);

	/* H = D - B */
	f25519_neg(h, b);
	f25519_sub(h, h, a);

	/* X3 = E F */
	f25519_mul__distinct(r->x, e, f);

	/* Y3 = G H */
	f25519_mul__distinct(r->y, g, h);

	/* T3 = E H */
	f25519_mul__distinct(r->t, e, h);

	/* Z3 = F G */
	f25519_mul__distinct(r->z, f, g);
}

static COMPACT_25519_DECL void ed25519_smult(struct ed25519_pt *r_out, const struct ed25519_pt *p,
		   const uint8_t *e)
{
	struct ed25519_pt r;
	int i;

	ed25519_copy(&r, &ed25519_neutral);

	for (i = 255; i >= 0; i--) {
		const uint8_t bit = (e[i >> 3] >> (i & 7)) & 1;
		struct ed25519_pt s;

		ed25519_double(&r, &r);
		ed25519_add(&s, &r, p);

		f25519_select(r.x, r.x, s.x, bit);
		f25519_select(r.y, r.y, s.y, bit);
		f25519_select(r.z, r.z, s.z, bit);
		f25519_select(r.t, r.t, s.t, bit);
	}

	ed25519_copy(r_out, &r);
}
#endif
// ******* END:   c25519/ed25519.c ********
// ******* BEGIN: c25519/edsign.c ********
/* Edwards curve signature system
 * Daniel Beer <dlbeer@gmail.com>, 22 Apr 2014
 *
 * This file is in the public domain.
 */

#ifndef COMPACT_DISABLE_ED25519

#define EXPANDED_SIZE  64

COMPACT_25519_DECL const uint8_t ed25519_order[FPRIME_SIZE] = {
	0xed, 0xd3, 0xf5, 0x5c, 0x1a, 0x63, 0x12, 0x58,
	0xd6, 0x9c, 0xf7, 0xa2, 0xde, 0xf9, 0xde, 0x14,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10
};

static COMPACT_25519_DECL void expand_key(uint8_t *expanded, const uint8_t *secret)
{
	struct sha512_state s;

	sha512_init(&s);
	sha512_final(&s, secret, EDSIGN_SECRET_KEY_SIZE);
	sha512_get(&s, expanded, 0, EXPANDED_SIZE);
	ed25519_prepare(expanded);
}

static COMPACT_25519_DECL uint8_t upp(struct ed25519_pt *p, const uint8_t *packed)
{
	uint8_t x[F25519_SIZE];
	uint8_t y[F25519_SIZE];
	uint8_t ok = ed25519_try_unpack(x, y, packed);

	ed25519_project(p, x, y);
	return ok;
}

static COMPACT_25519_DECL void pp(uint8_t *packed, const struct ed25519_pt *p)
{
	uint8_t x[F25519_SIZE];
	uint8_t y[F25519_SIZE];

	ed25519_unproject(x, y, p);
	ed25519_pack(packed, x, y);
}

static COMPACT_25519_DECL void sm_pack(uint8_t *r, const uint8_t *k)
{
	struct ed25519_pt p;

	ed25519_smult(&p, &ed25519_base, k);
	pp(r, &p);
}

static COMPACT_25519_DECL void edsign_sec_to_pub(uint8_t *pub, const uint8_t *secret)
{
	uint8_t expanded[EXPANDED_SIZE];

	expand_key(expanded, secret);
	sm_pack(pub, expanded);
}

static COMPACT_25519_DECL void hash_with_prefix(uint8_t *out_fp,
			     uint8_t *init_block, unsigned int prefix_size,
			     const uint8_t *message, size_t len)
{
	struct sha512_state s;

	sha512_init(&s);

	if (len < SHA512_BLOCK_SIZE && len + prefix_size < SHA512_BLOCK_SIZE) {
		memcpy(init_block + prefix_size, message, len);
		sha512_final(&s, init_block, len + prefix_size);
	} else {
		size_t i;

		memcpy(init_block + prefix_size, message,
		       SHA512_BLOCK_SIZE - prefix_size);
		sha512_block(&s, init_block);

		for (i = SHA512_BLOCK_SIZE - prefix_size;
		     i + SHA512_BLOCK_SIZE <= len;
		     i += SHA512_BLOCK_SIZE)
			sha512_block(&s, message + i);

		sha512_final(&s, message + i, len + prefix_size);
	}

	sha512_get(&s, init_block, 0, SHA512_HASH_SIZE);
	fprime_from_bytes(out_fp, init_block, SHA512_HASH_SIZE, ed25519_order);
}

static COMPACT_25519_DECL void generate_k(uint8_t *k, const uint8_t *kgen_key,
		       const uint8_t *message, size_t len)
{
	uint8_t block[SHA512_BLOCK_SIZE];

	memcpy(block, kgen_key, 32);
	hash_with_prefix(k, block, 32, message, len);
}

static COMPACT_25519_DECL void hash_message(uint8_t *z, const uint8_t *r, const uint8_t *a,
			 const uint8_t *m, size_t len)
{
	uint8_t block[SHA512_BLOCK_SIZE];

	memcpy(block, r, 32);
	memcpy(block + 32, a, 32);
	hash_with_prefix(z, block, 64, m, len);
}

static COMPACT_25519_DECL void edsign_sign(uint8_t *signature, const uint8_t *pub,
		 const uint8_t *secret,
		 const uint8_t *message, size_t len)
{
	uint8_t expanded[EXPANDED_SIZE];
	uint8_t e[FPRIME_SIZE];
	uint8_t s[FPRIME_SIZE];
	uint8_t k[FPRIME_SIZE];
	uint8_t z[FPRIME_SIZE];

	expand_key(expanded, secret);

	/* Generate k and R = kB */
	generate_k(k, expanded + 32, message, len);
	sm_pack(signature, k);

	/* Compute z = H(R, A, M) */
	hash_message(z, signature, pub, message, len);

	/* Obtain e */
	fprime_from_bytes(e, expanded, 32, ed25519_order);

	/* Compute s = ze + k */
	fprime_mul(s, z, e, ed25519_order);
	fprime_add(s, k, ed25519_order);
	memcpy(signature + 32, s, 32);
}

static COMPACT_25519_DECL uint8_t edsign_verify(const uint8_t *signature, const uint8_t *pub,
		      const uint8_t *message, size_t len)
{
	struct ed25519_pt p;
	struct ed25519_pt q;
	uint8_t lhs[F25519_SIZE];
	uint8_t rhs[F25519_SIZE];
	uint8_t z[FPRIME_SIZE];
	uint8_t ok = 1;

	/* Compute z = H(R, A, M) */
	hash_message(z, signature, pub, message, len);

	/* sB = (ze + k)B = ... */
	sm_pack(lhs, signature + 32);

	/* ... = zA + R */
	ok &= upp(&p, pub);
	ed25519_smult(&p, &p, z);
	ok &= upp(&q, signature);
	ed25519_add(&p, &p, &q);
	pp(rhs, &p);

	/* Equal? */
	return ok & f25519_eq(lhs, rhs);
}
#endif
// ******* END:   c25519/edsign.c ********
// ******* BEGIN: compact_wipe.c ********

#include <stdlib.h>
#include <string.h>

COMPACT_25519_DECL void *compact_wipe(void *data, size_t length) {
// simplification of: https://www.cryptologie.net/article/419/zeroing-memory-compiler-optimizations-and-memset_s/
	 volatile unsigned char *p = data;
	 while (length--){
		 *p++ = 0;
	 }
	return data;
}
// ******* END:   compact_wipe.c ********
// ******* BEGIN: compact_x25519.c ********

#ifndef COMPACT_DISABLE_X25519

COMPACT_25519_DECL void compact_x25519_keygen(
    uint8_t private_key[X25519_KEY_SIZE], 
    uint8_t public_key[X25519_KEY_SIZE],
    uint8_t random_seed[X25519_KEY_SIZE]
) {
    memcpy(private_key, random_seed, X25519_KEY_SIZE);
    compact_wipe(random_seed, X25519_KEY_SIZE);
    c25519_prepare(private_key);
    c25519_smult(public_key, c25519_base_x, private_key);
}

COMPACT_25519_DECL void compact_x25519_shared(
    uint8_t shared_secret[X25519_SHARED_SIZE], 
    const uint8_t my_private_key[X25519_KEY_SIZE], 
    const uint8_t their_public_key[X25519_KEY_SIZE]
) {
    // Ensure that supplied private key is clamped (fix issue #1).
    // Calling `c25519_prepare` multiple times for the same private key
    // is OK because it won't modify already clamped key.
    uint8_t clamped_private_key[X25519_KEY_SIZE];
    memcpy(clamped_private_key, my_private_key, X25519_KEY_SIZE);
    c25519_prepare(clamped_private_key);
    c25519_smult(shared_secret, their_public_key, clamped_private_key);
    compact_wipe(clamped_private_key, X25519_KEY_SIZE);
}

#ifndef COMPACT_DISABLE_X25519_DERIVE
#if (X25519_KEY_SIZE + (2 * X25519_KEY_SIZE)) > SHA512_BLOCK_SIZE 
#error "Unexpected key sizes"
#endif

static COMPACT_25519_DECL uint8_t* append(uint8_t *dst, const void * source, size_t length) {
    memcpy(dst, source, length);
    return dst + length;
}

COMPACT_25519_DECL void compact_x25519_derive_encryption_key(
    uint8_t *encryption_key, 
    size_t key_size, 
    const uint8_t shared_secret[X25519_SHARED_SIZE], 
    const uint8_t public_key1[X25519_KEY_SIZE], 
    const uint8_t public_key2[X25519_KEY_SIZE]
) {
    if (key_size > SHA512_HASH_SIZE) {
        key_size = SHA512_HASH_SIZE;
    }
    uint8_t key_data[X25519_SHARED_SIZE + 2 * X25519_KEY_SIZE];
    uint8_t *p = key_data;
    p = append(p, shared_secret, X25519_SHARED_SIZE);
    p = append(p, public_key1, X25519_KEY_SIZE);
    append(p, public_key2, X25519_KEY_SIZE);

    struct sha512_state hasher;
    sha512_init(&hasher);
    sha512_final(&hasher, key_data, sizeof(key_data));
    sha512_get(&hasher, encryption_key, 0, key_size);

    compact_wipe(key_data, X25519_SHARED_SIZE); // clear the session key at least
}
#endif
#endif
// ******* END:   compact_x25519.c ********
// ******* BEGIN: compact_ed25519.c ********

#ifndef COMPACT_DISABLE_ED25519

#include <string.h>

#define __PUBLIC_KEY_OFFSET (32)

COMPACT_25519_DECL void compact_ed25519_keygen(
    uint8_t private_key[ED25519_PRIVATE_KEY_SIZE], 
    uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    uint8_t random_seed[ED25519_SEED_SIZE]
) {
    // private key is seed + public key, like golang and others
    edsign_sec_to_pub(public_key, random_seed);
    memcpy(private_key, random_seed, ED25519_SEED_SIZE);
    memcpy(private_key + __PUBLIC_KEY_OFFSET, public_key, ED25519_PUBLIC_KEY_SIZE);
    compact_wipe(random_seed, ED25519_SEED_SIZE);
}

COMPACT_25519_DECL void compact_ed25519_calc_public_key(
    uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    const uint8_t private_key[ED25519_PRIVATE_KEY_SIZE]
) {
    memcpy(public_key, private_key + __PUBLIC_KEY_OFFSET, ED25519_PUBLIC_KEY_SIZE);
}

COMPACT_25519_DECL void compact_ed25519_sign(
    uint8_t signature[ED25519_SIGNATURE_SIZE], 
    const uint8_t private_key[ED25519_PRIVATE_KEY_SIZE], 
    const void *message, 
    size_t msg_length
) {
    edsign_sign(signature, private_key + __PUBLIC_KEY_OFFSET, private_key, message, msg_length);
}

COMPACT_25519_DECL bool compact_ed25519_verify(
    const uint8_t signature[ED25519_SIGNATURE_SIZE], 
    const uint8_t public_key[ED25519_PUBLIC_KEY_SIZE], 
    const void *message, 
    size_t msg_length
) {
    return edsign_verify(signature, public_key, message, msg_length) != 0;
}
#endif
// ******* END:   compact_ed25519.c ********
