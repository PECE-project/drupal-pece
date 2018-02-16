# Real AES

## Introduction

Real AES provides an encryption method plugin for the Encrypt module (https://drupal.org/project/encrypt).
It also serves as a library loader for the Defuse PHP-encryption library.

Partial API compatibility with the insecure AES module (via a submodule) is provided to act as a replacement
for use with other modules. Contrary to AES, this module will not accept keys that are too long or too small.

Defuse PHP-encryption provides authenticated encryption via an Encrypt-then-MAC scheme. AES-128 CBC is the symmetric
encryption algorithm, SHA-256 the hash algorithm for the HMAC. IV's are automatically and randomly generated. You do
not need to manage the IV separately, as it is included in the ciphertext.

Ciphertext format is: HMAC || iv || ciphertext

The HMAC verifies both IV and Ciphertext.

Beware that AES-module compatibility is at API-level only, and then just partial. Existing messages cannot be decrypted, nor
is there an upgrade path.

## Authenticated encryption

Authenticated encryption ensures data integrity of the ciphertext. When decrypting, integrity is checked first. Further
decrypting operations will only be executed when the integrity check passes.
This prevents certain ciphertext attacks on AES CBC.

## Differences to the AES module:

By default:

- Uses AES
- Only one encryption mode
- No IV reuse
- Authenticated encryption (prevents ciphertext tampering attacks eg the Padding Oracle "Vaudenay" attack)
- No silent key replacement
- No database keys
- No generation of weak keys
- Unambiguous padding, allowing correct decryption of binary data ending in 0x00
- Will not accept "keys" of incorrect length
- No support for AES encryption of user passwords
- Fails hard when there are problems with encryption or decryption

## Requirements

- PHP 5.4 or later with the openssl extension.
- The Defuse PHP-Encryption library from
  https://github.com/defuse/php-encryption/archive/522859f0b3f35fe83be5803ede83af3f517bfd5b.zip . Unzip the archive
  and install it as php-encryption in your libraries folder (sites/all/libraries/php-encryption).

## General configuration

If you need the defuse php-encryption library, or use the Encrypt plugin just enable Real AES and install the library.

If you need aes_encrypt / aes_decrypt using a global key, enable the included AES submodule and follow the steps below
to generate a default key.

### Generate a key

To generate a 128 bits random key, use the following command on the Unix CLI:

dd if=/dev/urandom bs=16 count=1 > /path/to/aes.key

This file MUST be stored outside of the docroot. Copy this file to an off-server, safe backup. If you lose the key,
you will not be able to decrypt encrypted information in the database.

If you do not have access to dd, generate the file using drush on a working Drupal installation:

drush php-eval 'echo drupal_random_bytes(16);' > /path/to/aes.key

### Point Real AES to the key

$conf['real_aes_key_file'] = '/path/to/aes.key';

## Encrypt plugin configuration

Real AES adds the "Authenticated AES" encryption method on the "Encryption method settings" tab for Encrypt
configurations.

It is important to ensure a proper key. We suggest to use the "File" key provider, but generate the key yourself.

dd if=/dev/urandom bs=16 count=1 > /path/to/encrypt_key.key

or

drush php-eval 'echo drupal_random_bytes(16);' > /path/to/encrypt_key.key

Supply the key provider with the path to this file.

## Usage

1. Use the Authenticated AES encryption method with the Encrypt module (https://drupal.org/project/encrypt).

2. If you implement encryption yourself, use this module as a Defuse PHP Encryption library loader.
   In your own code, include the library with libraries_load('php-encryption'), then call Crypto::encrypt,
   Crypto::decrypt and Crypto::createNewRandomKey directly.

   See
   * https://github.com/defuse/php-encryption for documentation,
   * https://github.com/defuse/php-encryption/blob/master/example.php for an example

3. If necessary, enable the provided AES submodule. This is an API module exposing aes_encrypt and aes_decrypt
for partial API compatibility with modules depending on the insecure AES module.

## Further reading

* Encryption in PHP https://defuse.ca/secure-php-encryption.htm
* Defuse php-encryption readme: https://github.com/defuse/php-encryption/blob/master/README.md
* Authenticated encryption: https://en.wikipedia.org/wiki/Authenticated_encryption
* CBC Block mode: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Block_Chaining_.28CBC.29
* HMAC: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code
* SHA-256: https://en.wikipedia.org/wiki/SHA-2

## Key management

Key storage on the webserver is one of the weak points of this system. Consider
using Encrypt with a key management solution.

One example is https://www.drupal.org/project/townsec_key . We have not reviewed
this module or the system it connects with.

## Frequently given answers

Q Why not use AES-GCM?
A This is currently not supported by the php openssl library.

Q No AES-256?
A No.

Q But, why no AES-256??
A You won't need it unless your threat model includes adversaries having a
working and fast quantum computer implementing Grover's algorithm.

## Credits

This module was created by LimoenGroen - https://limoengroen.nl - after carefully considering the various encryption
modules and libraries.

The library doing the actual work, Defuse PHP encryption, is authored by Taylor Hornby and Scott Arciszewski. Its
home is https://github.com/defuse/php-encryption .

## Future plans:

Patch the module encrypted_files to use Defuse PHP-encryption and properly derive a _key_ from a password.
