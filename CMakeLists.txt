cmake_minimum_required(VERSION 3.10)
project(legionutil)

set(CMAKE_CXX_STANDARD 14)

add_executable(legionutil main.cpp)

install(TARGETS legionutil PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE SETUID)