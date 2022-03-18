# Int24Types
### 24bit Integer Types  (Int24 and UInt24) for 
- C++ (single file include header) 
- .Net (interop dll)

## Short description:

### 1. Int24Types for native C++ 

- These come as a single include header which easyly can be added to c++ projects by just including file *src/int24bittypes.hpp*
- Optionally std/stl support can be enabled via #define symbol. with that additionally numeric_limits and type_traits extension will be implemented which make possible that the 24bit types can be used together with c++ std library functionallities   

### 2. Int24Types for .Net

- Int24Types is a .Net dll project which provides 24 bit integer types (a signed and an unsigned variant) which can be used almost like other regular 8, 16, 32 and 64 bit integer types which can be used in .Net projects.
- It's based on an (also in this repo contained) single header include library which is written in native C++ and which implements INT24 and UINT24 types in a way that makes possible using these together with c++ std library functions 
- The .Net types Int24 and UInt24 it provides are binary compatible with their relaying native c++ implemented types and are able being directly passed between managed clr environment code and code from linked unmanaged c++ binaries.   
 
