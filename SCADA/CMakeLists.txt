cmake_minimum_required(VERSION 3.19)
project(SCADA LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialBus Network)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

qt_standard_project_setup()

qt_add_executable(SCADA
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    deviceconfigpage.h deviceconfigpage.cpp deviceconfigpage.ui
    modbusdebugpage.h modbusdebugpage.cpp modbusdebugpage.ui

)

target_link_libraries(SCADA
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::SerialBus
        Qt6::Network
)

# 让 uic 生成的 ui_mainwindow.h（在 build 目录里）能 #include "deviceconfigpage.h"
target_include_directories(SCADA PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS SCADA
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SCADA
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

set_target_properties(SCADA PROPERTIES WIN32_EXECUTABLE OFF)