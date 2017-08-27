## KitchenSink

### Introduction

KitchenSink is a standalone program which combines multiple demos in one executable. The purpose of KitchenSink is to
demonstrate the capabilities and functionality of the CopperSpice libraries. These demos are basic examples and the code
is intentionally simplistic and not optimized.


### System Requirements

To build KitchenSink you will need a current copy of the CopperSpice libraries, a C++14 compiler, and a C++14 standard library.

Uses Autotools for building binary files.


### Building

If CopperSpice was not built with OpenSSL you will need to configure KitchenSink with the following:

```
./configure CXXFLAGS="-O2 -DQT_NO_OPENSSL"
```

If you are using a version of CopperSpice which has OpenSSL enabled, you must have the necessary OpenSSL library files
in your deployment of KitchenSink.



### Authors

* **Ansel Sermersheim**
* **Barbara Geller**
* **Zbigniew Skowron**


### License

This library is released under the 2-Clause BSD license. For more information refer to the LICENSE file provided with
this project.


### References

* Website: www.copperspice.com
* Email:   info@copperspice.com
