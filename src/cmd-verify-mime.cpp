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

#include "cmd-verify-mime.h"

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

QCmdVerifyMime::QCmdVerifyMime()
{
  qVerbose(<< "[QCmdVerifyMime::QCmdVerifyMime]" << this);
}

QCmdVerifyMime::~QCmdVerifyMime()
{
  qVerbose(<< "[QCmdVerifyMime::~QCmdVerifyMime]" << this);
}

void QCmdVerifyMime::process()
{
  int res;

  // Initialize libcrypto
  CRYPTO_malloc_init();
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();

  CMS_ContentInfo *cms = NULL;
  CMS_ContentInfo_free(cms);

  BIO *const in = BIO_new_file("../data/mime.txt", "r");
  if (!in) {
    qDebug() << "Error: cannnot open inout file with signature";
    emit done();
    return;
  }
  BIO *indata = NULL;
  cms = SMIME_read_CMS(in, &indata);

  X509_STORE *store = X509_STORE_new();
  assert(store);
  X509_LOOKUP *lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
  assert(lookup);
  lookup = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir());
  assert(lookup);
  res = X509_LOOKUP_add_dir(lookup, NULL, X509_FILETYPE_DEFAULT);
  assert(res);

  unsigned long err;
  while ((err = ERR_get_error())) {
    qDebug() << "Got error before verification, reason:" << ERR_GET_REASON(err);
  }

  // Reset the OpenSSL error queue
  while ((err = ERR_get_error())) {
    qDebug() << "Got error before verification, reason:" << ERR_GET_REASON(err);
  }

  res = CMS_verify(cms, NULL, store, indata, NULL, 0);
  if (res) {
    qDebug() << "Verification result: success (" << res << ")";
  } else {
    qDebug() << "Verification result: failure (" << res << ")";
  }

  while ((err = ERR_get_error())) {
    qDebug() << "Got error after verification, reason:" << ERR_GET_REASON(err);
  }

  CMS_ContentInfo_free(cms);
  BIO_free(indata);
  BIO_free(in);

  emit done();
}
