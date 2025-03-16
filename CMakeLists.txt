cmake_minimum_required(VERSION 3.24)
project(crossroads C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wshadow -Wuninitialized -Wconversion -Wnull-dereference -Wdouble-promotion")

set(CMAKE_C_STANDARD 11)

find_package(cJSON REQUIRED)

include_directories(include)

set(SOURCES
        src/queue.c
        src/vehicle.c
        src/lights.c
        src/vehicle.c
        src/parser.c src/simulation.c)

add_executable(crossroads
        src/main.c
        ${SOURCES})

target_link_libraries(crossroads cjson)

enable_testing()

add_executable(run_tests
        tests/test_lights.c
        ${SOURCES}
        )

target_link_libraries(run_tests cjson)
target_include_directories(run_tests PRIVATE include)

add_test(NAME TestLightSwitch COMMAND run_tests --gtest_filter=testLightSwitch)
add_test(NAME TestLightInitialization COMMAND run_tests --gtest_filter=testLightInitialization())
add_test(NAME TestVehicleMovement COMMAND run_tests --gtest_filter=testVehicleMovement())
add_test(NAME TestLeftTurnConflict COMMAND run_tests --gtest_filter=testLeftTurnConflict())
add_test(NAME TestGreenTimeAdjustment COMMAND run_tests --gtest_filter=testGreenTimeAdjustment())

add_custom_target(example
    COMMAND ${CMAKE_BINARY_DIR}/crossroads ${CMAKE_SOURCE_DIR}/example/input.json ${CMAKE_SOURCE_DIR}/example/output.json
    DEPENDS crossroads
)
