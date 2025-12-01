# FPM

## DESCRIPTION
This API allows you to check file permissions. There can be 3 levels, USER, ADMIN, and OWNER. User has low-control, Admin has moderate control, and Owner has full control. There can only be 1 owner.

## HOW TO INSTALL (GCC/G++ ONLY)
1- Copy the files from include and src to one main folder. Name it whatever you want (the folder). 

2- Go to compiling folder. It will teach you to build tasks.json and launch.json, c_cpp_properties.json if needed.

3- Including it:

```cpp
#include "../<yourFolder>/FPM.hpp"
#include "../<yourFolder>/fpm_operators.hpp"

int main() {
// your code
}
```
