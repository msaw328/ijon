cmake_minimum_required(VERSION 3.0.0)
project("ijon-ref" LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Common flags for all build targets
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wextra")

add_library(ijon SHARED
        src/keyexp.c
        src/encrypt.c
        src/decrypt.c
        src/spn.c
        )

target_include_directories(ijon PUBLIC include)

if(IJON_NO_STD)
    target_link_options(ijon PRIVATE "-nostdlib")
endif(IJON_NO_STD)

add_subdirectory(examples EXCLUDE_FROM_ALL)
