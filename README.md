# Int24Types
### 24bit Integer Types  (Int24 and UInt24) for 
- C++ (single file include header) 
- .Net (interop dll)

## Short description:

### 1. Int24Types for native C++ 

- This comes as a single file include header *src/int24bittypes.hpp* which easyly can be used in c++ projects by just including this single file 
- Optionally std/stl support can be enabled via define INT24_TYPETRAIT_SUPPORT. with this set to 1, the header additionally implements numeric_limits and type_traits extensions for the c++ std library which make possible that std library functions can handle passed variables of 24bit integer types correctly.

### 2. Int24Types for .Net

- Int24Types is a .Net dll clr project written in managed C++ which provides 24 bit integer types (a signed and an unsigned variant) for .Net projects. The 24Bit types can be used almost same like other 8, 16, 32 and 64 bit integer types in .Net Projects
- It's based on an (also in this repo contained) single header include library which is written in native C++ and which implements INT24 and UINT24 types in a way that makes possible using these together with c++ std library functions 
- The Int24 and UInt24 types wihch this .Net library provides are binary compatible with their relaying native c++ implementations and can be passed directly reinterpreted from a managed clr environment to unmanaged code located inside a linked c++ binary and vice versa.   
 
