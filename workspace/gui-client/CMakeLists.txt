cmake_minimum_required(VERSION 3.16)
project(gui-client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2)

if(PROJECT_IS_TOP_LEVEL)
    find_package(proto REQUIRED)
    find_package(project-util REQUIRED)
endif()

qt_standard_project_setup()
qt_add_executable(appgui-client
    src/main.cpp
    src/gui-client/gui-client.cpp
    src/app-backend/app-backend.cpp

    include/app-backend/app-backend.hpp
    include/app-backend/contact-list-model.hpp
)
target_include_directories(appgui-client PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/app-backend>)

qt_add_qml_module(appgui-client
    URI app
    VERSION 1.0
    RESOURCE_PREFIX /qt/qml
    QML_FILES 
    qml/Main.qml

    qml/page/SignInPage.qml
    qml/page/SignUpPage.qml
    qml/page/PersonalAreaPage.qml

    qml/subpage/personal-area/MainSubpage.qml
    qml/subpage/personal-area/ContactsSubpage.qml
    qml/subpage/personal-area/SettingsSubpage.qml

    qml/widget/AlarmButtonWidget.qml
    qml/widget/SignInWidget.qml
    qml/widget/SignUpWidget.qml
    qml/widget/ContactListWidget.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgui-client PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgui-client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgui-client
    PRIVATE 
    Qt6::Quick 
    Qt6::QuickControls2 
    proto::proto 
    project-util::project-util
)

target_compile_definitions(appgui-client PRIVATE 
                           RPC_MAP_PATH="${PROJECT_UTIL_RPC_MAP_PATH}")

include(GNUInstallDirs)
install(TARGETS appgui-client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
