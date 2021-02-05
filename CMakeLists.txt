find_package(Corrosion REQUIRED)

add_llvm_library(LLVMObfuscationCommon
  src/CryptoUtils.cpp
  src/LegacyLowerSwitch.cpp
  src/PassScheduler.cpp
  src/Passes/AntiClassDump.cpp
  src/Passes/BogusControlFlow.cpp
  src/Passes/Flattening.cpp
  src/Passes/FunctionCallObfuscate.cpp
  src/Passes/FunctionWrapper.cpp
  src/Passes/IndirectBranch.cpp
  src/Passes/SplitBasicBlocks.cpp
  src/Passes/StringEncryption.cpp
  src/Passes/Substitution.cpp
  src/RegisterPass.cpp
  src/Utils.cpp
  DEPENDS
  intrinsics_gen
)
target_include_directories(LLVMObfuscationCommon PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
corrosion_import_crate(MANIFEST_PATH nanorand/Cargo.toml CRATES nanorand-abi)
target_link_libraries(LLVMObfuscationCommon PUBLIC nanorand)
execute_process(
  COMMAND git log -1 --format=%H
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE HIKARI_GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
target_compile_definitions(LLVMObfuscationCommon PRIVATE "-DGIT_COMMIT_HASH=\"${HIKARI_GIT_COMMIT_HASH}\"")

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS "-fPIC")
endif()
