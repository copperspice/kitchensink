## KitchenSink

### Introduction

KitchenSink is a standalone program which combines multiple demos in one executable. The purpose of KitchenSink is to
demonstrate the capabilities and functionality of the CopperSpice libraries. These demos are basic examples and the code
is intentionally simplistic and not optimized.


### System Requirements

To build KitchenSink you will need a current copy of the CopperSpice libraries, a C++14 compiler, and a C++14 standard library.

Uses CMake or Autotools for building binary files.


### Building

If you are using a version of CopperSpice which has OpenSSL enabled you need the necessary OpenSSL library files in your deployment of
KitchenSink.

If CopperSpice was not built with OpenSSL you will need to configure KitchenSink as shown.


CMake

```
cmake -G "Ninja" -DCMAKE_CXX_FLAGS="-DQT_NO_OPENSSL" -DCMAKE_BUILD_TYPE=Release .
```


AutoTools

```
./configure CXXFLAGS="-O2 -DQT_NO_OPENSSL"
```



### Presentations

YouTube channel videos about CopperSpice, DoxyPress, C++, and the other topics related to our work.

https://www.youtube.com/copperspice


Links to technical presentations recorded at CppNow and CppCon:

www.copperspice.com/presentations.html


### Authors / Contributors

* **Ansel Sermersheim**
* **Barbara Geller**
* **Zbigniew Skowron**


### License

This library is released under the 2-Clause BSD license. For more information refer to the LICENSE file provided with
this project.


### References

* Website: www.copperspice.com
* Email:   info@copperspice.com
