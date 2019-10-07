## KitchenSink

### Introduction

KitchenSink is a standalone program which combines multiple demos in one executable. The purpose of KitchenSink is to
demonstrate the capabilities and functionality of the CopperSpice libraries. These demos are basic examples and the
code is intentionally simplistic and not optimized.


### Building

KitchenSink prebuilt binaries are available for Linux, Mac OS X, and Windows.

https://download.copperspice.com/kitchensink/binary/

To build KitchenSink from source a current copy of the CopperSpice libraries, a C++17 compiler, and a C++17 standard
library are required.

CMake build files are provided with the KitchenSink source distribution.


###### OpenSSL

If you are using a version of CopperSpice which has OpenSSL enabled you need the necessary OpenSSL library files in
your deployment of KitchenSink.

If CopperSpice was not built with OpenSSL you will need to configure KitchenSink as shown.


```
cmake -G "Ninja" -DCMAKE_CXX_FLAGS="-DQT_NO_OPENSSL" -DCMAKE_BUILD_TYPE=Release .
```


### Documentation

Information about KitchenSink can be found on our web site.

www.copperspice.com/documentation-kitchensink.html



### Presentations

Our YouTube channel videos are about modern C++, build systems, CopperSpice, DoxyPress, and other topics related to
our open source work.

https://www.youtube.com/copperspice


Links to technical presentations recorded at CppNow and CppCon:

www.copperspice.com/presentations.html


### Authors / Contributors

* **Barbara Geller**
* **Ansel Sermersheim**
* **Zbigniew Skowron**
* **Daniel Pfeifer**
* **Jan Wilmans**
* **Tim van Deurzen**


### License

This program is released under the 2-Clause BSD license. For more information refer to the LICENSE file provided with
this project.


### References

* Website: www.copperspice.com
* Email:   info@copperspice.com
