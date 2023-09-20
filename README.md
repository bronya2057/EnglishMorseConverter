# EnglishMorseConverter #

EnglishMorseConverter is a simple C++/QML gui application that can translate between English and Morse letters

## How do I get set up? ##
1. Install base dependencies: Qt6.5, cmake
2. Modify CMakeUserPresets.json to reflect paths from your local machine, or create preset that will suit your needs from templates in CMakePresets.json
3. Run cmake with created user preset

## Additional packages ##
Install additional dependencies if needed: cppcheck, clang-format, lcov + genhtml, clang-tidy, include-what-you-use

To activate additional checks on each target please refer to cmakeHelpers/CMakeLists.txt

## Cmake config ##
If any variables are missing for CMake Configuration, refer to cmakeHelpers/ConfigurePresetsBase.json or CMakePresets.json and reuse/extend one of the predefined presets

## License

[MIT](https://choosealicense.com/licenses/mit/)