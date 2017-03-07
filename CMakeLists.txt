project (plantumlqeditor)

cmake_minimum_required (VERSION 3.7)

if(WIN32)
    add_definitions(-DUNICODE -DQT_LARGEFILE_SUPPORT)
endif()

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Network REQUIRED)

option (ENABLE_UNIT_TESTS "enable unit test" OFF)
if (${ENABLE_UNIT_TESTS})
    set (CMAKE_BUILD_TYPE "Debug")
    set (GMOCK_ROOT ${CMAKE_SOURCE_DIR}/thirdparty/gmock)
    set (GTEST_INCLUDE_DIR ${GMOCK_ROOT}/gtest/include)
    set (GTEST_MAIN_LIBRARY gtest_main)
    set (GTEST_LIBRARY gtest)
    set (GMOCK_LIBRARY gmock)
    enable_testing ()
    find_package (GTest REQUIRED)
    include_directories (${GMOCK_ROOT}/include ${GTEST_INCLUDE_DIR})
endif()

message ("CMAKE_BUILD_TYPE:  ${CMAKE_BUILD_TYPE}")
message ("Qt Headers:        ${QT_INCLUDES}")

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc")
endif()

add_subdirectory (thirdparty)

#-------------------------------------------------------------------------------
# add to SOURCES files that will be tested with GMock and GTest
#-------------------------------------------------------------------------------
set (SOURCES_LIB
    assistantxmlreader.cpp
    filecache.cpp
    recentdocuments.cpp
    )

add_library (plantumlqeditorlib STATIC
    ${SOURCES_LIB}
    ${EXTRA_HEADERS_LIB}
    )

target_link_libraries (plantumlqeditorlib
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Svg
    )

target_include_directories(plantumlqeditorlib PUBLIC ".")

if(${ENABLE_UNIT_TESTS})
    add_subdirectory(tests)
endif()

#-------------------------------------------------------------------------------
# the real app
#-------------------------------------------------------------------------------
set(SOURCES_APP
    main.cpp
    mainwindow.cpp
    preferencesdialog.cpp
    previewwidget.cpp
    utils.cpp
    textedit.cpp
    )

set(EXTRA_HEADERS_APP
    utils.h
    settingsconstants.h
    )

set(FORMS_APP
    preferencesdialog.ui
    logdialog.ui
    )

set(QRC_APP
    plantumlqeditor.qrc
    )

if(WIN32)
    set(OPTIONS_APP WIN32)
endif()

add_executable(plantumlqeditor ${OPTIONS_APP}
    ${SOURCES_APP}
    ${SOURCES_FORMS_APP}
    ${SOURCES_QRC_APP}
    ${EXTRA_HEADERS_APP}
    )

target_link_libraries(plantumlqeditor
    plantumlqeditorlib
    qtsingleapplicationlib
    )

if(WIN32)
    set_target_properties(plantumlqeditor PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

#-------------------------------------------------------------------------------
# installer support
#-------------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME "plantuml-qeditor")
set(CPACK_PACKAGE_VENDOR "Ioan Calin Borcoman")
set(CPACK_PACKAGE_CONTACT "iborco@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "PlantUML QEditor - a Qt editor for PlantUML")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/icon64.png")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "PlantUML QEditor")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_IGNORE_FILES ".git/;.gitignore;thirdparty/gmock-1.6.0/")

if(WIN32)
    set(CPACK_GENERATOR "ZIP" "NSIS")

    set(CPACK_PACKAGE_EXECUTABLES plantumlqeditor "PlantUML QEditor")

    install(TARGETS plantumlqeditor
        RUNTIME
        DESTINATION bin
        COMPONENT applications
        )

    file(GLOB LIBGCC_S_SJLJ_DLL ${CMAKE_FIND_ROOT_PATH}/bin/libgcc_s_sjlj*.dll)
    file(GLOB LIBPNG_DLL ${CMAKE_FIND_ROOT_PATH}/bin/libpng*.dll)
    file(GLOB LIBSTDCPP_DLL ${CMAKE_FIND_ROOT_PATH}/bin/libstdc++-*.dll)

    install(FILES
        ${CMAKE_FIND_ROOT_PATH}/bin/QtCore${QT_VERSION_MAJOR}.dll
        ${CMAKE_FIND_ROOT_PATH}/bin/QtGui${QT_VERSION_MAJOR}.dll
        ${CMAKE_FIND_ROOT_PATH}/bin/QtNetwork${QT_VERSION_MAJOR}.dll
        ${CMAKE_FIND_ROOT_PATH}/bin/QtSvg${QT_VERSION_MAJOR}.dll
        ${LIBGCC_S_SJLJ_DLL}
        ${LIBPNG_DLL}
        ${LIBSTDCPP_DLL}
        ${CMAKE_FIND_ROOT_PATH}/bin/zlib1.dll
        DESTINATION bin
        COMPONENT applications
        )

    install(FILES assistant.xml
        DESTINATION share/plantumlqeditor
        COMPONENT assistant
        )

    install(DIRECTORY icons
        DESTINATION share/plantumlqeditor
        COMPONENT assistant
        )

    set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "PlantUML QEditor")
    set(CPACK_COMPONENT_ASSISTANT_DISPLAY_NAME "Default Assistant")

    set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION
        "A PlantUML editor written with Qt${QT_VERSION_MAJOR}"
        )
    set(CPACK_COMPONENT_ASSISTANT_DESCRIPTION
        "The default assistant.xml and associated icons"
        )

endif()

include (CPack)
