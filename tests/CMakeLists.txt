file(GLOB TEST_SOURCES CONFIGURE_DEPENDS
    src/*.c
)


add_executable(dango_tests

    ${TEST_SOURCES}

)


target_include_directories(dango_tests
    PRIVATE

        ${CMAKE_CURRENT_SOURCE_DIR}/include

)


target_link_libraries(dango_tests
    PRIVATE

        dango_lib

)


enable_dev_flags(dango_tests)


add_test(
    NAME dango_tests
    COMMAND dango_tests
)