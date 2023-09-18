# README #

Repo for learning how to work with CMake and some libs.

### Changelog ###
* Updated to Qt6
* Integrated QML live reloader

### Tested with next configuration (Windows/Ubuntu)  ###
* CMake 3.20.0  
* Qt 6.5.1 

### How do I get set up? ###
sudo snap install cmake
sudo apt install python3-pip
sudo pip3 install conan

### Additional packages
sudo apt install clang-format

### Conan ###
1. Issue command: conan profile detect
2. Create conanfile.txt/conanfile.py with list dependencies
3. Issue command: conan install . --output-folder=build/dependencies/conan --build=missing
4. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

### CMakeVariables to set ###
* BENCHMARK_CMAKE - Enables fetching and applying small example of GoogleBenchmark
* TEST_CMAKE      - Enables fetching and applying small example of GoogleTest

* QT_EXAMPLE         - Enables Qt examples
* Qt5_DIR            - Mandatory to specify if QT config files not in PATH (ex. "QtFolder/lib/cmake/Qt5")
* Qt5_QUICK_COMPILER - Mandatory only for Linux (ex. "QtFolder/lib/cmake/Qt5QuickCompiler")
* CMAKE_PREFIX_PATH  - Path to cmake lib folder (ex. "QtFolder/lib/cmake/Qt6")