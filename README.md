# FPM

## DESCRIPTION
This API allows you to check file permissions. There can be 3 levels, USER, ADMIN, and OWNER. User has low-control, Admin has moderate control, and Owner has full control. There can only be 1 owner.

## HOW TO INSTALL (GCC/G++ && CMAKE)

## FOR CMAKE USE VERSION 1.0.3
## FOR G++ USE VERSION EARLIER THAN 1.0.3

# GCC/G++

1- Extract the `.rar` file from `Releases`.

2- After you have gotten `Version 1.02` or earlier builds, put the `FPM` and `.vscode` folders in your root directory.

3- Your project structure must be something like:

```
YourRootProject/
    src/
        main.cpp

    FPM/
        FPM.cpp
        fpm_operators.hpp
        FPM.hpp

    .vscode/
        tasks.json
        launch.json
        c_cpp_properties.json
```

4- optional if you want faster compiling; go to `tasks.json` and `launch.json` and `c_cpp_properties.json` and change to your path.

5- After that, Include it like:

```cpp
#include "FPM.hpp" // if it dosent work do ../FPM/FPM.hpp
#include "fpm_operators.hpp" // if it dosent work do ../FPM/fpm_operators.hpp

int main() {
// your code
}
```

6- optional; you can hit f7 to compile and run.

# CMAKE

1- Extract the `.rar` from `Version 1.0.3` in `Releases`.

2- In your projects `CMakeLists.txt`, add FPM as a library:

```cmake
cmake_minimum_required(VERSION 3.20)
project(UserApp LANGUAGES CXX)

add_subdirectory(FPM)

add_executable(app
    src/main.cpp # or whatever your file is called
)

target_link_libraries(app PRIVATE fpm)

```

3- Build the project with commands:

```powershell
cmake -S . -B build
cmake --build build
```

4- Just final check, your project structure must be something like:

```
YourRootProject/
    CMakeLists.txt # YOUR CMakeLists.txt that you will put step 2 in.

    src/
        main.cpp # YOUR main file

    FPM/ # THE EXTRACTED .RAR FILE
        include/
            FPM.hpp
            fpm_operators.hpp
        src/
            FPM.cpp
    .vscode
```

5- optional; you can hit f7 to build and run.
