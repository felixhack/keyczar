// Copyright 2009 Sebastien Martini (seb@dbzteam.org)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef KEYCZAR_ECDSA_PRIVATE_KEY_H_
#define KEYCZAR_ECDSA_PRIVATE_KEY_H_

#include <string>

#include <keyczar/base/basictypes.h>
#include <keyczar/base/scoped_ptr.h>
#include <keyczar/base/values.h>
#include <keyczar/private_key.h>
#include <keyczar/ecdsa_impl.h>
#include <keyczar/ecdsa_public_key.h>

namespace keyczar {

class ECDSAPrivateKey : public PrivateKey {
 public:
  // Takes ownership of |public_key| and |ecdsa_impl|.
  ECDSAPrivateKey(ECDSAImpl* ecdsa_impl, ECDSAPublicKey* public_key, int size)
      : PrivateKey(public_key, size), ecdsa_impl_(ecdsa_impl) {}

  // Creates a key from |root_key|. The caller takes ownership of the returned
  // Key.
  static ECDSAPrivateKey* CreateFromValue(const Value& root_key);

  // Generates a |size| bits key. The caller takes ownership of the returned
  // Key.
  static ECDSAPrivateKey* GenerateKey(int size);

  // Imports a PEM key |filename| and creates a new key. |passphrase| is
  // optional.
  static ECDSAPrivateKey* CreateFromPEMPrivateKey(
      const std::string& filename, const std::string* passphrase);

  // The caller takes ownership of the returned Value.
  virtual Value* GetValue() const;

  // Exports this private key to PKCS8 file |filename| optionally encrypted
  // with |passphrase|.
  virtual bool ExportPrivateKey(const std::string& filename,
                                const std::string* passphrase) const;

  virtual bool Sign(const std::string& data, std::string* signature) const;

 private:
  // The caller doesn't take ownership over the returned object.
  ECDSAImpl* ecdsa_impl() const { return ecdsa_impl_.get(); }

  scoped_ptr<ECDSAImpl> ecdsa_impl_;

  DISALLOW_COPY_AND_ASSIGN(ECDSAPrivateKey);
};

}  // namespace keyczar

#endif  // KEYCZAR_ECDSA_PRIVATE_KEY_H_
