# libciphers
This repo contains the code to do basic classical ciphers in C++ as full ADTs. 

# Hill Cipher
This cipher requires matrices so I've wrote the matrix Templated class solely for this cipher.

## Matrix Class
This class is a full ADT. It supports any integral or floating point type. Also works exactly the same as any of the default builtin types in C++. It uses vectors for the matrix elements itself.
- All Arithematic Operators(`*`,`/`,`-`,`+`)
  - Also inplace `+=`,`/=`,`-=`,`+=`
- All Comparison Operators
  - `==`, `>=`, `<=`, `<`, `>`
- Subscript operators `[]`, and `()`
- Assignment Operator
- Linear equation solver(GAE, and LUD backsub)
- Matrix Operators
  - Inversion
  - Determinant
  - Adjugate
  - Inverse Modulus
  - Cofactor of a matrix
    

