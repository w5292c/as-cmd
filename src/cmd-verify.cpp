/*
 * MIT License
 *
 * Copyright (c) 2018 Alexander Chumakov
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "cmd-verify.h"

#include "as-debug.h"

#include <QFile>
#include <assert.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/engine.h>
#include <QCryptographicHash>

QCmdVerify::QCmdVerify()
{
  qVerbose(<< "[QCmdVerify::QCmdVerify]" << this);
}

QCmdVerify::~QCmdVerify()
{
  qVerbose(<< "[QCmdVerify::~QCmdVerify]" << this);
}

void QCmdVerify::process()
{
  // Initialize libcrypto
  CRYPTO_malloc_init();
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();

  CMS_ContentInfo *cms = NULL;

  BIO *const in = BIO_new_file("../data/signature.p7s", "rb");
  if (!in) {
    qDebug() << "Error: cannnot open inout file with signature";
    emit done();
    return;
  }
  BIO *const indata = BIO_new_file("../data/plain.txt", "rb");
  if (!indata) {
    qDebug() << "Error: failed to open the content file";
    BIO_free(in);
    emit done();
    return;
  }
  X509_STORE *store = X509_STORE_new();
  assert(store);
  X509_LOOKUP *lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
  assert(lookup);
  int res = X509_LOOKUP_load_file(lookup, "/etc/ssl/certs/COMODO_RSA_Client_Authentication_and_Secure_Email_CA.pem", X509_FILETYPE_PEM);
  assert(res);
  lookup = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir());
  assert(lookup);
  X509_LOOKUP_add_dir(lookup, NULL, X509_FILETYPE_DEFAULT);

  cms = d2i_CMS_bio(in, NULL);
  if (!cms) {
    qDebug() << "Error: the input signature file cannot be loaded";
  }

  res = CMS_verify(cms, NULL, store, indata, NULL, CMS_DETACHED /* | CMS_NO_SIGNER_CERT_VERIFY | CMS_BINARY*/);
  qDebug() << "Verification result:" << res;
  if (!res) {
    int err = ERR_get_error();
    qDebug() << "Error:" << err << ", reason:" << ERR_error_string(err, NULL);
  }

cleanup:
  CMS_ContentInfo_free(cms);
  BIO_free(indata);
  BIO_free(in);

  emit done();
}
