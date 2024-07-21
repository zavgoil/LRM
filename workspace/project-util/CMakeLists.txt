cmake_minimum_required(VERSION 3.22)
project(project-util)

find_package(yaml-cpp)

if(PROJECT_IS_TOP_LEVEL)
    find_package(nlohmann_json REQUIRED)
endif()

add_library(project-util INTERFACE)
add_library(project-util::project-util ALIAS project-util)
target_link_libraries(project-util INTERFACE yaml-cpp nlohmann_json::nlohmann_json)
target_include_directories(project-util INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

install(DIRECTORY 
    include/ 
    DESTINATION 
    include)

install (TARGETS project-util EXPORT project-utilTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/config/ 
    DESTINATION 
    share/project-util/config)

install (EXPORT project-utilTargets
        NAMESPACE project-util::
        DESTINATION lib/cmake/project-util
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/project-util-config.cmake
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/project-util-config.cmake
    DESTINATION lib/cmake/project-util
)