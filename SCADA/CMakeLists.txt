cmake_minimum_required(VERSION 3.19)
project(SCADA LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialBus Network)

qt_standard_project_setup()

qt_add_executable(SCADA
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(SCADA
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::SerialBus
        Qt6::Network
)

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