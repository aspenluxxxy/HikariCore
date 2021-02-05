// For licensing terms, please read LICENSE.md in this repository.
//===----------------------------------------------------------------------===//
#include "Obfuscation/CryptoUtils.h"

#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/Twine.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/raw_ostream.h"

#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

using namespace llvm;
namespace llvm
{
ManagedStatic<CryptoUtils> cryptoutils;
}
CryptoUtils::CryptoUtils() {
	eng = nanorand::new_chacha12();
}

uint32_t CryptoUtils::scramble32(uint32_t in, std::map<uint32_t /*IDX*/, uint32_t /*VAL*/>& VMap) {

	if (VMap.find(in) == VMap.end()) {
		uint32_t V = get_uint32_t();
		VMap[in] = V;
		return V;
	} else {
		return VMap[in];
	}
}

uint32_t CryptoUtils::get_range(uint32_t min, uint32_t max) {
	if (max == 0) {
		return 0;
	}
	return nanorand::chacha_range_u32(&eng, min, max);
}
