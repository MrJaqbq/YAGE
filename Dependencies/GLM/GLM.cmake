# GLM
add_library(glm INTERFACE)
target_include_directories(glm
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Dependencies/GLM/Source>)

install(TARGETS glm
        EXPORT Engine DESTINATION "${YAGE_LIBRARY_DIR}"
        ARCHIVE  DESTINATION ${YAGE_LIBRARY_DIR}
        LIBRARY  DESTINATION ${YAGE_LIBRARY_DIR}
        RUNTIME  DESTINATION ${YAGE_BINARY_DIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/Dependencies/GLM/Source/glm DESTINATION include)