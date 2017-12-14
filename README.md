## KitchenSink

### Introduction

KitchenSink is a standalone program which combines multiple demos in one executable. The purpose of KitchenSink is to
demonstrate the capabilities and functionality of the CopperSpice libraries. These demos are basic examples and the code
is intentionally simplistic and not optimized.


### System Requirements

To build KitchenSink you will need a current copy of the CopperSpice libraries, a C++14 compiler, and a C++14 standard library.

Uses CMake or Autotools to build the executable.


### Building

###### Build Files

If you are building KitchenSink with CMake you will need binaries of CopperSpice which were also built with CMake.


###### OpenSSL

If you are using a version of CopperSpice which has OpenSSL enabled you need the necessary OpenSSL library files in your
deployment of KitchenSink.

If CopperSpice was not built with OpenSSL you will need to configure KitchenSink as shown.


CMake

```
cmake -G "Ninja" -DCMAKE_CXX_FLAGS="-DQT_NO_OPENSSL" -DCMAKE_BUILD_TYPE=Release .
```


AutoTools

```
./configure CXXFLAGS="-O2 -DQT_NO_OPENSSL"
```

### Documentation

Information about KitchenSink can be found using the following links. The "Build System" video on our YouTube channel
provides details about building KitchenSink.

www.copperspice.com/documentation-kitchensink.html

https://www.youtube.com/watch?v=GI2coXFs5RM



### Presentations

Our YouTube channel videos are about modern C++, build systems, CopperSpice, DoxyPress, and other topics related to our
open source work.

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
