// REQUIRES: powerpc-registered-target

// RUN: %clang_cc1 -target-feature +altivec -target-feature +power9-vector \
// RUN:   -triple powerpc64-unknown-unknown -fsyntax-only   \
// RUN: -Wall -Werror -verify %s

// RUN: %clang_cc1 -target-feature +altivec -target-feature +power9-vector  \
// RUN: -triple powerpc64le-unknown-unknown -fsyntax-only    \
// RUN: -Wall -Werror -verify %s

#include <altivec.h>

extern vector signed int vsi;
extern vector unsigned char vuc;

void testInsertWord(void) {
  int index = 5;
  vector unsigned char v1 = vec_insert4b(vsi, vuc, index); // expected-error {{argument to '__builtin_vsx_insertword' must be a constant integer}}
  vector unsigned long long v2 = vec_extract4b(vuc, index);   // expected-error {{argument to '__builtin_vsx_extractuword' must be a constant integer}}
}

void testXXPERMDI(int index) {
  vec_xxpermdi(vsi); //expected-error {{too few arguments to function call, expected at least 3, have 1}}
  vec_xxpermdi(vsi, vsi, 2, 4); //expected-error {{too many arguments to function call, expected at most 3, have 4}}
  vec_xxpermdi(vsi, vsi, index); //expected-error {{argument 3 to '__builtin_vsx_xxpermdi' must be a 2-bit unsigned literal (i.e. 0, 1, 2 or 3)}}
  vec_xxpermdi(1, 2, 3); //expected-error {{first two arguments to '__builtin_vsx_xxpermdi' must be vectors}}
  vec_xxpermdi(vsi, vuc, 2); //expected-error {{first two arguments to '__builtin_vsx_xxpermdi' must have the same type}}
}

void testXXSLDWI(int index) {
  vec_xxsldwi(vsi); //expected-error {{too few arguments to function call, expected at least 3, have 1}}
  vec_xxsldwi(vsi, vsi, 2, 4); //expected-error {{too many arguments to function call, expected at most 3, have 4}}
  vec_xxsldwi(vsi, vsi, index); //expected-error {{argument 3 to '__builtin_vsx_xxsldwi' must be a 2-bit unsigned literal (i.e. 0, 1, 2 or 3)}}
  vec_xxsldwi(1, 2, 3); //expected-error {{first two arguments to '__builtin_vsx_xxsldwi' must be vectors}}
  vec_xxsldwi(vsi, vuc, 2); //expected-error {{first two arguments to '__builtin_vsx_xxsldwi' must have the same type}}
}
