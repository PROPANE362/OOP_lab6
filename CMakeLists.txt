cmake_minimum_required(VERSION 3.10)
project(balagur_fate_3_editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory(googletest)


add_executable(editor
    main.cpp
    npc.cpp
    observer.cpp
    factory.cpp
    visitor.cpp
    dungeon_editor.cpp
)

target_include_directories(editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(editor PROPERTIES SUFFIX ".exe")


add_executable(rpg_tests
    tests.cpp
    npc.cpp
    observer.cpp
    factory.cpp
    visitor.cpp
    dungeon_editor.cpp
)

target_include_directories(rpg_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rpg_tests gtest gtest_main)
set_target_properties(rpg_tests PROPERTIES SUFFIX ".exe")