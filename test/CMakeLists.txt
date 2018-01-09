file(GLOB SRCS *.cpp)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)

add_executable(testAvl ${SRCS} ../avlBaum/AvlTree.h ../avlBaum/AvlTree.cpp )

target_link_libraries(testAvl
        gtest
        gmock
)

include_directories("..")

install(TARGETS testAvl DESTINATION bin)
