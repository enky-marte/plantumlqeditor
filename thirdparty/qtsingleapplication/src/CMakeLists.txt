set (SOURCES_LIB
    qtsingleapplication.cpp
    qtlocalpeer.cpp
)

set (EXTRA_HEADERS_LIB
    QtSingleApplication
)

add_library (qtsingleapplicationlib STATIC
    ${SOURCES_LIB}
    ${EXTRA_HEADERS_LIB}
)

target_link_libraries (qtsingleapplicationlib
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::Widgets
)

target_include_directories(qtsingleapplicationlib PUBLIC ".")
