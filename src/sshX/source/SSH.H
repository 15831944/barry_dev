#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#include "puttymem.h"
#include "network.h"
#include "int64.h"
#include "misc.h"

#define SSH1_MSG_DISCONNECT                       1	/* 0x1 */
#define SSH1_SMSG_PUBLIC_KEY                      2	/* 0x2 */
#define SSH1_CMSG_SESSION_KEY                     3	/* 0x3 */
#define SSH1_CMSG_USER                            4	/* 0x4 */
#define SSH1_CMSG_AUTH_RSA                        6	/* 0x6 */
#define SSH1_SMSG_AUTH_RSA_CHALLENGE              7	/* 0x7 */
#define SSH1_CMSG_AUTH_RSA_RESPONSE               8	/* 0x8 */
#define SSH1_CMSG_AUTH_PASSWORD                   9	/* 0x9 */
#define SSH1_CMSG_REQUEST_PTY                     10	/* 0xa */
#define SSH1_CMSG_WINDOW_SIZE                     11	/* 0xb */
#define SSH1_CMSG_EXEC_SHELL                      12	/* 0xc */
#define SSH1_CMSG_EXEC_CMD                        13	/* 0xd */
#define SSH1_SMSG_SUCCESS                         14	/* 0xe */
#define SSH1_SMSG_FAILURE                         15	/* 0xf */
#define SSH1_CMSG_STDIN_DATA                      16	/* 0x10 */
#define SSH1_SMSG_STDOUT_DATA                     17	/* 0x11 */
#define SSH1_SMSG_STDERR_DATA                     18	/* 0x12 */
#define SSH1_CMSG_EOF                             19	/* 0x13 */
#define SSH1_SMSG_EXIT_STATUS                     20	/* 0x14 */
#define SSH1_MSG_CHANNEL_OPEN_CONFIRMATION        21	/* 0x15 */
#define SSH1_MSG_CHANNEL_OPEN_FAILURE             22	/* 0x16 */
#define SSH1_MSG_CHANNEL_DATA                     23	/* 0x17 */
#define SSH1_MSG_CHANNEL_CLOSE                    24	/* 0x18 */
#define SSH1_MSG_CHANNEL_CLOSE_CONFIRMATION       25	/* 0x19 */
#define SSH1_SMSG_X11_OPEN                        27	/* 0x1b */
#define SSH1_CMSG_PORT_FORWARD_REQUEST            28	/* 0x1c */
#define SSH1_MSG_PORT_OPEN                        29	/* 0x1d */
#define SSH1_CMSG_AGENT_REQUEST_FORWARDING        30	/* 0x1e */
#define SSH1_SMSG_AGENT_OPEN                      31	/* 0x1f */
#define SSH1_MSG_IGNORE                           32	/* 0x20 */
#define SSH1_CMSG_EXIT_CONFIRMATION               33	/* 0x21 */
#define SSH1_CMSG_X11_REQUEST_FORWARDING          34	/* 0x22 */
#define SSH1_CMSG_AUTH_RHOSTS_RSA                 35	/* 0x23 */
#define SSH1_MSG_DEBUG                            36	/* 0x24 */
#define SSH1_CMSG_REQUEST_COMPRESSION             37	/* 0x25 */
#define SSH1_CMSG_AUTH_TIS                        39	/* 0x27 */
#define SSH1_SMSG_AUTH_TIS_CHALLENGE              40	/* 0x28 */
#define SSH1_CMSG_AUTH_TIS_RESPONSE               41	/* 0x29 */
#define SSH1_CMSG_AUTH_CCARD                      70	/* 0x46 */
#define SSH1_SMSG_AUTH_CCARD_CHALLENGE            71	/* 0x47 */
#define SSH1_CMSG_AUTH_CCARD_RESPONSE             72	/* 0x48 */

#define SSH1_AUTH_TIS                             5	/* 0x5 */
#define SSH1_AUTH_CCARD                           16	/* 0x10 */

#define SSH1_PROTOFLAG_SCREEN_NUMBER              1	/* 0x1 */
/* Mask for protoflags we will echo back to server if seen */
#define SSH1_PROTOFLAGS_SUPPORTED                 0	/* 0x1 */

#define SSH2_MSG_DISCONNECT                       1	/* 0x1 */
#define SSH2_MSG_IGNORE                           2	/* 0x2 */
#define SSH2_MSG_UNIMPLEMENTED                    3	/* 0x3 */
#define SSH2_MSG_DEBUG                            4	/* 0x4 */
#define SSH2_MSG_SERVICE_REQUEST                  5	/* 0x5 */
#define SSH2_MSG_SERVICE_ACCEPT                   6	/* 0x6 */
#define SSH2_MSG_KEXINIT                          20	/* 0x14 */
#define SSH2_MSG_NEWKEYS                          21	/* 0x15 */
#define SSH2_MSG_KEXDH_INIT                       30	/* 0x1e */
#define SSH2_MSG_KEXDH_REPLY                      31	/* 0x1f */
#define SSH2_MSG_KEX_DH_GEX_REQUEST               30	/* 0x1e */
#define SSH2_MSG_KEX_DH_GEX_GROUP                 31	/* 0x1f */
#define SSH2_MSG_KEX_DH_GEX_INIT                  32	/* 0x20 */
#define SSH2_MSG_KEX_DH_GEX_REPLY                 33	/* 0x21 */
#define SSH2_MSG_USERAUTH_REQUEST                 50	/* 0x32 */
#define SSH2_MSG_USERAUTH_FAILURE                 51	/* 0x33 */
#define SSH2_MSG_USERAUTH_SUCCESS                 52	/* 0x34 */
#define SSH2_MSG_USERAUTH_BANNER                  53	/* 0x35 */
#define SSH2_MSG_USERAUTH_PK_OK                   60	/* 0x3c */
#define SSH2_MSG_USERAUTH_PASSWD_CHANGEREQ        60	/* 0x3c */
#define SSH2_MSG_USERAUTH_INFO_REQUEST            60	/* 0x3c */
#define SSH2_MSG_USERAUTH_INFO_RESPONSE           61	/* 0x3d */
#define SSH2_MSG_GLOBAL_REQUEST                   80	/* 0x50 */
#define SSH2_MSG_REQUEST_SUCCESS                  81	/* 0x51 */
#define SSH2_MSG_REQUEST_FAILURE                  82	/* 0x52 */
#define SSH2_MSG_CHANNEL_OPEN                     90	/* 0x5a */
#define SSH2_MSG_CHANNEL_OPEN_CONFIRMATION        91	/* 0x5b */
#define SSH2_MSG_CHANNEL_OPEN_FAILURE             92	/* 0x5c */
#define SSH2_MSG_CHANNEL_WINDOW_ADJUST            93	/* 0x5d */
#define SSH2_MSG_CHANNEL_DATA                     94	/* 0x5e */
#define SSH2_MSG_CHANNEL_EXTENDED_DATA            95	/* 0x5f */
#define SSH2_MSG_CHANNEL_EOF                      96	/* 0x60 */
#define SSH2_MSG_CHANNEL_CLOSE                    97	/* 0x61 */
#define SSH2_MSG_CHANNEL_REQUEST                  98	/* 0x62 */
#define SSH2_MSG_CHANNEL_SUCCESS                  99	/* 0x63 */
#define SSH2_MSG_CHANNEL_FAILURE                  100	/* 0x64 */

/*
* Packet type contexts, so that ssh2_pkt_type can correctly decode
* the ambiguous type numbers back into the correct type strings.
*/
#define SSH2_PKTCTX_DHGROUP          0x0001
#define SSH2_PKTCTX_DHGEX            0x0002
#define SSH2_PKTCTX_KEX_MASK         0x000F
#define SSH2_PKTCTX_PUBLICKEY        0x0010
#define SSH2_PKTCTX_PASSWORD         0x0020
#define SSH2_PKTCTX_KBDINTER         0x0040
#define SSH2_PKTCTX_AUTH_MASK        0x00F0

#define SSH2_DISCONNECT_HOST_NOT_ALLOWED_TO_CONNECT 1	/* 0x1 */
#define SSH2_DISCONNECT_PROTOCOL_ERROR            2	/* 0x2 */
#define SSH2_DISCONNECT_KEY_EXCHANGE_FAILED       3	/* 0x3 */
#define SSH2_DISCONNECT_HOST_AUTHENTICATION_FAILED 4	/* 0x4 */
#define SSH2_DISCONNECT_MAC_ERROR                 5	/* 0x5 */
#define SSH2_DISCONNECT_COMPRESSION_ERROR         6	/* 0x6 */
#define SSH2_DISCONNECT_SERVICE_NOT_AVAILABLE     7	/* 0x7 */
#define SSH2_DISCONNECT_PROTOCOL_VERSION_NOT_SUPPORTED 8	/* 0x8 */
#define SSH2_DISCONNECT_HOST_KEY_NOT_VERIFIABLE   9	/* 0x9 */
#define SSH2_DISCONNECT_CONNECTION_LOST           10	/* 0xa */
#define SSH2_DISCONNECT_BY_APPLICATION            11	/* 0xb */
#define SSH2_DISCONNECT_TOO_MANY_CONNECTIONS      12	/* 0xc */
#define SSH2_DISCONNECT_AUTH_CANCELLED_BY_USER    13	/* 0xd */
#define SSH2_DISCONNECT_NO_MORE_AUTH_METHODS_AVAILABLE 14	/* 0xe */
#define SSH2_DISCONNECT_ILLEGAL_USER_NAME         15	/* 0xf */

struct ssh_channel;
struct ssh_tag ;

extern SOCKET ssh_log_socket(void *handle);
extern void sshfwd_close(struct ssh_channel *c);
extern int sshfwd_write(struct ssh_channel *c, char *, int);
extern void sshfwd_unthrottle(struct ssh_channel *c, int bufsize);

/*
 * Useful thing.
 */
#ifndef lenof
#define lenof(x) ( (sizeof((x))) / (sizeof(*(x))))
#endif

#define SSH_CIPHER_IDEA		1
#define SSH_CIPHER_DES		2
#define SSH_CIPHER_3DES		3
#define SSH_CIPHER_BLOWFISH	6

#ifdef MSCRYPTOAPI
#define APIEXTRA 8
#else
#define APIEXTRA 0
#endif

#ifndef BIGNUM_INTERNAL
typedef void *Bignum;
#endif

struct RSAKey {
    int bits;
    int bytes;
#ifdef MSCRYPTOAPI
    unsigned long exponent;
    unsigned char *modulus;
#else
    Bignum modulus;
    Bignum exponent;
    Bignum private_exponent;
    Bignum p;
    Bignum q;
    Bignum iqmp;
#endif
    char *comment;
};

struct dss_key {
    Bignum p, q, g, y, x;
};

int makekey(unsigned char *data, int len, struct RSAKey *result,
	    unsigned char **keystr, int order);
int makeprivate(unsigned char *data, int len, struct RSAKey *result);
int rsaencrypt(unsigned char *data, int length, struct RSAKey *key);
Bignum rsadecrypt(Bignum input, struct RSAKey *key);
void rsasign(unsigned char *data, int length, struct RSAKey *key);
void rsasanitise(struct RSAKey *key);
int rsastr_len(struct RSAKey *key);
void rsastr_fmt(char *str, struct RSAKey *key);
void rsa_fingerprint(char *str, int len, struct RSAKey *key);
int rsa_verify(struct RSAKey *key);
unsigned char *rsa_public_blob(struct RSAKey *key, int *len);
int rsa_public_blob_len(void *data, int maxlen);
void freersakey(struct RSAKey *key);

typedef unsigned int word32;
typedef unsigned int uint32;

unsigned long crc32_compute(const void *s, size_t len);
unsigned long crc32_update(unsigned long crc_input, const void *s, size_t len);

/* SSH CRC compensation attack detector */
void *crcda_make_context(void);
void crcda_free_context(void *handle);
int detect_attack(void *handle, unsigned char *buf, uint32 len,
		  unsigned char *IV);

typedef struct {
    uint32 h[4];
} MD5_Core_State;

struct MD5Context {
#ifdef MSCRYPTOAPI
    unsigned long hHash;
#else
    MD5_Core_State core;
    unsigned char block[64];
    int blkused;
    uint32 lenhi, lenlo;
#endif
};

void MD5Init(struct MD5Context *context);
void MD5Update(struct MD5Context *context, unsigned char const *buf,
	       unsigned len);
void MD5Final(unsigned char digest[16], struct MD5Context *context);
void MD5Simple(void const *p, unsigned len, unsigned char output[16]);

void *hmacmd5_make_context(void);
void hmacmd5_free_context(void *handle);
void hmacmd5_key(void *handle, void const *key, int len);
void hmacmd5_do_hmac(void *handle, unsigned char const *blk, int len,
		     unsigned char *hmac);

typedef struct {
    uint32 h[5];
    unsigned char block[64];
    int blkused;
    uint32 lenhi, lenlo;
} SHA_State;
void SHA_Init(SHA_State * s);
void SHA_Bytes(SHA_State * s, void *p, int len);
void SHA_Final(SHA_State * s, unsigned char *output);
void SHA_Simple(void *p, int len, unsigned char *output);

void hmac_sha1_simple(void *key, int keylen, void *data, int datalen,
		      unsigned char *output);

typedef struct {
    uint64 h[8];
    unsigned char block[128];
    int blkused;
    uint32 len[4];
} SHA512_State;
void SHA512_Init(SHA512_State * s);
void SHA512_Bytes(SHA512_State * s, const void *p, int len);
void SHA512_Final(SHA512_State * s, unsigned char *output);
void SHA512_Simple(const void *p, int len, unsigned char *output);

struct ssh_cipher {
    void *(*make_context)(void);
    void (*free_context)(void *);
    void (*sesskey) (void *, unsigned char *key);	/* for SSH-1 */
    void (*encrypt) (void *, unsigned char *blk, int len);
    void (*decrypt) (void *, unsigned char *blk, int len);
    int blksize;
    char *text_name;
};

struct ssh2_cipher {
    void *(*make_context)(void);
    void (*free_context)(void *);
    void (*setiv) (void *, unsigned char *key);	/* for SSH-2 */
    void (*setkey) (void *, unsigned char *key);/* for SSH-2 */
    void (*encrypt) (void *, unsigned char *blk, int len);
    void (*decrypt) (void *, unsigned char *blk, int len);
    char *name;
    int blksize;
    int keylen;
    char *text_name;
};

struct ssh2_ciphers {
    int nciphers;
    const struct ssh2_cipher *const *list;
};

struct ssh_mac {
    void *(*make_context)(void);
    void (*free_context)(void *);
    void (*setkey) (void *, unsigned char *key);
    void (*generate) (void *, unsigned char *blk, int len, unsigned long seq);
    int (*verify) (void *, unsigned char *blk, int len, unsigned long seq);
    char *name;
    int len;
    char *text_name;
};

struct ssh_kex {
    /*
     * Plugging in another KEX algorithm requires structural chaos,
     * so it's hard to abstract them into nice little structures
     * like this. Fortunately, all our KEXes are basically
     * Diffie-Hellman at the moment, so in this structure I simply
     * parametrise the DH exchange a bit.
     */
    char *name, *groupname;
    const unsigned char *pdata, *gdata;/* NULL means use group exchange */
    int plen, glen;
};

struct ssh_signkey {
    void *(*newkey) (char *data, int len);
    void (*freekey) (void *key);
    char *(*fmtkey) (void *key);
    unsigned char *(*public_blob) (void *key, int *len);
    unsigned char *(*private_blob) (void *key, int *len);
    void *(*createkey) (unsigned char *pub_blob, int pub_len,
			unsigned char *priv_blob, int priv_len);
    void *(*openssh_createkey) (unsigned char **blob, int *len);
    int (*openssh_fmtkey) (void *key, unsigned char *blob, int len);
    int (*pubkey_bits) (void *blob, int len);
    char *(*fingerprint) (void *key);
    int (*verifysig) (void *key, char *sig, int siglen,
		      char *data, int datalen);
    unsigned char *(*sign) (void *key, char *data, int datalen,
			    int *siglen);
    char *name;
    char *keytype;		       /* for host key cache */
};

struct ssh_compress {
    char *name;
    void *(*compress_init) (void);
    void (*compress_cleanup) (void *);
    int (*compress) (void *, unsigned char *block, int len,
		     unsigned char **outblock, int *outlen);
    void *(*decompress_init) (void);
    void (*decompress_cleanup) (void *);
    int (*decompress) (void *, unsigned char *block, int len,
		       unsigned char **outblock, int *outlen);
    int (*disable_compression) (void *);
    char *text_name;
};

struct ssh2_userkey {
    const struct ssh_signkey *alg;     /* the key algorithm */
    void *data;			       /* the key data */
    char *comment;		       /* the key comment */
};

extern const struct ssh_cipher ssh_3des;
extern const struct ssh_cipher ssh_des;
extern const struct ssh_cipher ssh_blowfish_ssh1;
extern const struct ssh2_ciphers ssh2_3des;
extern const struct ssh2_ciphers ssh2_des;
extern const struct ssh2_ciphers ssh2_aes;
extern const struct ssh2_ciphers ssh2_blowfish;
extern const struct ssh_kex ssh_diffiehellman_group1;
extern const struct ssh_kex ssh_diffiehellman_group14;
extern const struct ssh_kex ssh_diffiehellman_gex;
extern const struct ssh_signkey ssh_dss;
extern const struct ssh_signkey ssh_rsa;
extern const struct ssh_mac ssh_md5;
extern const struct ssh_mac ssh_sha1;
extern const struct ssh_mac ssh_sha1_buggy;

/*
 * PuTTY version number formatted as an SSH version string. 
 */
extern char sshver[];

/*
 * Gross hack: pscp will try to start SFTP but fall back to scp1 if
 * that fails. This variable is the means by which scp.c can reach
 * into the SSH code and find out which one it got.
 */
extern int ssh_fallback_cmd(void *handle);

#ifndef MSCRYPTOAPI
void SHATransform(word32 * digest, word32 * data);
#endif

int random_byte(void);
void random_add_noise(void *noise, int length);
void random_add_heavynoise(void *noise, int length);

void logevent(void *, const char *);

/* Allocate and register a new channel for port forwarding */
void *new_sock_channel(void *handle, Socket s);
void ssh_send_port_open(void *channel, char *hostname, int port, char *org);

/* Exports from portfwd.c */
extern const char *pfd_newconnect(Socket * s, char *hostname, int port,
				  void *c, const Config *cfg,
				  int addressfamily);
/* desthost == NULL indicates dynamic (SOCKS) port forwarding */
extern const char *pfd_addforward(char *desthost, int destport, char *srcaddr,
				  int port, void *backhandle,
				  const Config *cfg, void **sockdata,
				  int address_family);
extern void pfd_close(Socket s);
extern void pfd_terminate(void *sockdata);
extern int pfd_send(Socket s, char *data, int len);
extern void pfd_confirm(Socket s);
extern void pfd_unthrottle(Socket s);
extern void pfd_override_throttle(Socket s, int enable);

/* Exports from x11fwd.c */
extern const char *x11_init(Socket *, char *, void *, void *, const char *,
			    int, const Config *);
extern void x11_close(Socket);
extern int x11_send(Socket, char *, int);
extern void *x11_invent_auth(char *, int, char *, int, int);
extern void x11_free_auth(void *);
extern void x11_unthrottle(Socket s);
extern void x11_override_throttle(Socket s, int enable);
extern int x11_get_screen_number(char *display);
void x11_get_real_auth(void *authv, char *display);
char *x11_display(const char *display);

/* Platform-dependent X11 functions */
extern void platform_get_x11_auth(char *display, int *proto,
                                  unsigned char *data, int *datalen);
extern const char platform_x11_best_transport[];
/* best X11 hostname for this platform if none specified */
SockAddr platform_get_x11_unix_address(int displaynum, char **canonicalname);
/* make up a SockAddr naming the address for displaynum */
char *platform_get_x_display(void);
/* allocated local X display string, if any */

Bignum copybn(Bignum b);
Bignum bn_power_2(int n);
void bn_restore_invariant(Bignum b);
Bignum bignum_from_long(unsigned long n);
void freebn(Bignum b);
Bignum modpow(Bignum base, Bignum exp, Bignum mod);
Bignum modmul(Bignum a, Bignum b, Bignum mod);
void decbn(Bignum n);
extern Bignum Zero, One;
Bignum bignum_from_bytes(const unsigned char *data, int nbytes);
int ssh1_read_bignum(const unsigned char *data, int len, Bignum * result);
int bignum_bitcount(Bignum bn);
int ssh1_bignum_length(Bignum bn);
int ssh2_bignum_length(Bignum bn);
int bignum_byte(Bignum bn, int i);
int bignum_bit(Bignum bn, int i);
void bignum_set_bit(Bignum bn, int i, int value);
int ssh1_write_bignum(void *data, Bignum bn);
Bignum biggcd(Bignum a, Bignum b);
unsigned short bignum_mod_short(Bignum number, unsigned short modulus);
Bignum bignum_add_long(Bignum number, unsigned long addend);
Bignum bigmul(Bignum a, Bignum b);
Bignum bigmuladd(Bignum a, Bignum b, Bignum addend);
Bignum bigdiv(Bignum a, Bignum b);
Bignum bigmod(Bignum a, Bignum b);
Bignum modinv(Bignum number, Bignum modulus);
Bignum bignum_bitmask(Bignum number);
Bignum bignum_rshift(Bignum number, int shift);
int bignum_cmp(Bignum a, Bignum b);
char *bignum_decimal(Bignum x);

#ifdef DEBUG
void diagbn(char *prefix, Bignum md);
#endif

void *dh_setup_group(const struct ssh_kex *kex);
void *dh_setup_gex(Bignum pval, Bignum gval);
void dh_cleanup(void *);
Bignum dh_create_e(void *, int nbits);
Bignum dh_find_K(void *, Bignum f);

int loadrsakey(const Filename *filename, struct RSAKey *key,
	       char *passphrase, const char **errorstr);
int rsakey_encrypted(const Filename *filename, char **comment);
int rsakey_pubblob(const Filename *filename, void **blob, int *bloblen,
		   const char **errorstr);

int saversakey(const Filename *filename, struct RSAKey *key, char *passphrase);

extern int base64_decode_atom(char *atom, unsigned char *out);
extern int base64_lines(int datalen);
extern void base64_encode_atom(unsigned char *data, int n, char *out);
extern void base64_encode(FILE *fp, unsigned char *data, int datalen, int cpl);

/* ssh2_load_userkey can return this as an error */
extern struct ssh2_userkey ssh2_wrong_passphrase;
#define SSH2_WRONG_PASSPHRASE (&ssh2_wrong_passphrase)

int ssh2_userkey_encrypted(const Filename *filename, char **comment);
struct ssh2_userkey *ssh2_load_userkey(const Filename *filename,
				       char *passphrase, const char **errorstr);
char *ssh2_userkey_loadpub(const Filename *filename, char **algorithm,
			   int *pub_blob_len, const char **errorstr);
int ssh2_save_userkey(const Filename *filename, struct ssh2_userkey *key,
		      char *passphrase);
const struct ssh_signkey *find_pubkey_alg(const char *name);

enum {
    SSH_KEYTYPE_UNOPENABLE,
    SSH_KEYTYPE_UNKNOWN,
    SSH_KEYTYPE_SSH1, SSH_KEYTYPE_SSH2,
    SSH_KEYTYPE_OPENSSH, SSH_KEYTYPE_SSHCOM
};
int key_type(const Filename *filename);
char *key_type_to_str(int type);

int import_possible(int type);
int import_target_type(int type);
int import_encrypted(const Filename *filename, int type, char **comment);
int import_ssh1(const Filename *filename, int type,
		struct RSAKey *key, char *passphrase, const char **errmsg_p);
struct ssh2_userkey *import_ssh2(const Filename *filename, int type,
				 char *passphrase, const char **errmsg_p);
int export_ssh1(const Filename *filename, int type,
		struct RSAKey *key, char *passphrase);
int export_ssh2(const Filename *filename, int type,
                struct ssh2_userkey *key, char *passphrase);

void des3_decrypt_pubkey(unsigned char *key, unsigned char *blk, int len);
void des3_encrypt_pubkey(unsigned char *key, unsigned char *blk, int len);
void des3_decrypt_pubkey_ossh(unsigned char *key, unsigned char *iv,
			      unsigned char *blk, int len);
void des3_encrypt_pubkey_ossh(unsigned char *key, unsigned char *iv,
			      unsigned char *blk, int len);
void aes256_encrypt_pubkey(unsigned char *key, unsigned char *blk,
			   int len);
void aes256_decrypt_pubkey(unsigned char *key, unsigned char *blk,
			   int len);

void des_encrypt_xdmauth(unsigned char *key, unsigned char *blk, int len);
void des_decrypt_xdmauth(unsigned char *key, unsigned char *blk, int len);

/*
 * For progress updates in the key generation utility.
 */
#define PROGFN_INITIALISE 1
#define PROGFN_LIN_PHASE 2
#define PROGFN_EXP_PHASE 3
#define PROGFN_PHASE_EXTENT 4
#define PROGFN_READY 5
#define PROGFN_PROGRESS 6
typedef void (*progfn_t) (void *param, int action, int phase, int progress);

int rsa_generate(struct RSAKey *key, int bits, progfn_t pfn,
		 void *pfnparam);
int dsa_generate(struct dss_key *key, int bits, progfn_t pfn,
		 void *pfnparam);
Bignum primegen(int bits, int modulus, int residue, Bignum factor,
		int phase, progfn_t pfn, void *pfnparam);


/*
 * zlib compression.
 */
void *zlib_compress_init(void);
void zlib_compress_cleanup(void *);
void *zlib_decompress_init(void);
void zlib_decompress_cleanup(void *);
int zlib_compress_block(void *, unsigned char *block, int len,
			unsigned char **outblock, int *outlen);
int zlib_decompress_block(void *, unsigned char *block, int len,
			  unsigned char **outblock, int *outlen);

/*
 * SSH-1 agent messages.
 */
#define SSH1_AGENTC_REQUEST_RSA_IDENTITIES    1
#define SSH1_AGENT_RSA_IDENTITIES_ANSWER      2
#define SSH1_AGENTC_RSA_CHALLENGE             3
#define SSH1_AGENT_RSA_RESPONSE               4
#define SSH1_AGENTC_ADD_RSA_IDENTITY          7
#define SSH1_AGENTC_REMOVE_RSA_IDENTITY       8
#define SSH1_AGENTC_REMOVE_ALL_RSA_IDENTITIES 9	/* openssh private? */

/*
 * Messages common to SSH-1 and OpenSSH's SSH-2.
 */
#define SSH_AGENT_FAILURE                    5
#define SSH_AGENT_SUCCESS                    6

/*
 * OpenSSH's SSH-2 agent messages.
 */
#define SSH2_AGENTC_REQUEST_IDENTITIES          11
#define SSH2_AGENT_IDENTITIES_ANSWER            12
#define SSH2_AGENTC_SIGN_REQUEST                13
#define SSH2_AGENT_SIGN_RESPONSE                14
#define SSH2_AGENTC_ADD_IDENTITY                17
#define SSH2_AGENTC_REMOVE_IDENTITY             18
#define SSH2_AGENTC_REMOVE_ALL_IDENTITIES       19

/*
 * Need this to warn about support for the original SSH-2 keyfile
 * format.
 */
void old_keyfile_warning(void);
