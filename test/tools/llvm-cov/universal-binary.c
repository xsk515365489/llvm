// The coverage reader should be able to handle universal binaries

// CHECK: 100| [[@LINE+1]]|int main
int main(int argc, const char *argv[]) {}

// RUN: llvm-profdata merge %S/Inputs/universal-binary.proftext -o %t.profdata
// RUN: llvm-cov show %S/Inputs/universal-binary -instr-profile %t.profdata -no-colors -filename-equivalence %s -arch x86_64 | FileCheck %s

// RUN: not llvm-cov show %S/Inputs/universal-binary -instr-profile %t.profdata -no-colors -filename-equivalence %s -arch i386 2>&1 | FileCheck --check-prefix=WRONG-ARCH %s
// WRONG-ARCH: Failed to load coverage

// llvm-cov doesn't work on big endian yet
// XFAIL: powerpc64-, s390x, mips-, mips64-, sparc
