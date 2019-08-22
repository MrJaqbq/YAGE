cmake --version
where cmake

pip install conan conan_package_tools --upgrade --upgrade-strategy only-if-needed

conan user
move scripts/conan-fallback-settings.yml %USERPROFILE%/.conan/settings.yml
mkdir Build
cd Build
conan remote add yage https://api.bintray.com/conan/bentoudev/yage
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
cmake --target all -DCMAKE_BUILD_TYPE=Release -DYAGE_VERSION_PATCH=%PATCH_VER% -DYAGE_BUILD_EDITOR=OFF ..
cmake -P cmake_install.cmake