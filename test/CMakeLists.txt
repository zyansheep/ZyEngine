#Find Sources and Headers in src folder
file(GLOB_RECURSE TEST_SOURCES *.cpp)
file(GLOB_RECURSE TEST_HEADERS *.h)

#Test executable
add_executable(Test ${TEST_SOURCES} ${TEST_HEADERS})
target_link_libraries(Test LINK_PUBLIC ZyEngine)