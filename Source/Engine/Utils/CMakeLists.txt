## Provides various utilities, such as memory management, logger etc.
project(Utils VERSION 0.1 LANGUAGES CXX)

if(VALGRIND_FOUND)
    set(VALGRIND_ADDITIONAL_HEADERS ${VALGRIND_INCLUDE_DIR} include/Utils/ValgrindMemoryBoundChecker.h include/Utils/ValgrindMemoryTracker.h)
endif(VALGRIND_FOUND)

add_library(Utils STATIC ${VALGRIND_ADDITIONAL_HEADERS} include/Utils/SafeDelete.h src/Debug.cpp include/Utils/Handle.h include/Utils/Container.h include/Utils/Color.hpp include/Utils/Using.h include/Utils/Index.h include/Utils/TypeInfo.h include/Utils/BorrowedPtr.h include/Utils/DefaultTrait.h include/Utils/File.h include/Utils/Allocator.h src/LinearAllocator.cpp include/Utils/LinearAllocator.h include/Utils/DebugSourceInfo.h include/Utils/MemoryBlock.h src/StackAllocator.cpp include/Utils/StackAllocator.h src/FreeListAllocator.cpp include/Utils/FreeListAllocator.h src/PoolAllocator.cpp include/Utils/PoolAllocator.h include/Utils/List.h include/Utils/String.h src/String.cpp include/Utils/Dictionary.h include/Utils/PropertyMacro.h include/Utils/MemoryBoundChecker.h include/Utils/MemoryTracker.h include/Utils/MemorySizes.h include/Utils/SimpleMemoryTracker.h include/Utils/SimpleMemoryBoundChecker.h src/MemoryTracker.cpp src/MemoryBoundChecker.cpp src/SafeDelete.cpp include/Utils/TypeIndexList.h include/Utils/ForEachType.h include/Utils/HandleContainer.h include/Utils/Slice.h include/Utils/Assert.h src/Assert.cpp include/Utils/IContainer.h include/Utils/Range.h include/Utils/Math.h include/Utils/RelativePtr.h include/Utils/Colony.h include/Utils/SmartHandle.h include/Utils/Defines.h)
add_library(YAGE::Utils ALIAS Utils)

target_include_directories(Utils PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${YAGE_INCLUDE_DIR}>
        PRIVATE src ${CMAKE_CURRENT_BINARY_DIR})

target_compile_features(Utils PUBLIC
        cxx_nullptr
        cxx_auto_type
        cxx_variadic_templates
        cxx_trailing_return_types
        cxx_return_type_deduction
        cxx_right_angle_brackets
        cxx_constexpr)
#        cxx_std_17
#        cxx_relaxed_constexpr)

target_compile_definitions(Utils PRIVATE ${YAGE_LIB_COMPILE_DEFS})

if(VALGRIND_FOUND)
    target_compile_definitions(Utils PRIVATE YAGE_VALGRIND=1)
    target_include_directories(Utils PRIVATE ${VALGRIND_INCLUDE_DIR})
endif()

# 'make install' to the correct location
install(TARGETS Utils
        EXPORT Engine DESTINATION "${YAGE_LIBRARY_DIR}"
        ARCHIVE  DESTINATION ${YAGE_LIBRARY_DIR}
        LIBRARY  DESTINATION ${YAGE_LIBRARY_DIR}
        RUNTIME  DESTINATION ${YAGE_BINARY_DIR})
install(DIRECTORY include/ DESTINATION ${YAGE_INCLUDE_DIR})

# This makes the project importable from the build directory
export(TARGETS Utils FILE UtilsConfig.cmake)

if(YAGE_BUILD_TESTS)
    # Every library has unit tests, of course
    add_executable(UtilsTests test/UtilsTests.cpp test/MemoryTests.cpp test/ContainerTests.cpp test/HandleTests.cpp test/UsingTests.cpp test/TypeInfoTests.cpp test/LinearAllocatorTest.cpp test/StackAllocatorTest.cpp test/PoolAllocatorTest.cpp test/FreeListAllocatorTest.cpp test/ListTests.cpp test/StringTests.cpp test/DictionaryTests.cpp test/TypeIndexListTests.cpp test/ForEachTypeTests.cpp test/HandleContainerTests.cpp test/MockHelper.h test/RelativePtrTest.cpp test/SmartHandleTests.cpp)

    target_link_libraries(UtilsTests
            Utils ${CMAKE_THREAD_LIBS_INIT})

    add_test(UtilsTests UtilsTests)
    add_coverage(Utils)
endif(YAGE_BUILD_TESTS)