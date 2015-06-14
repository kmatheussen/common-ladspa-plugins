# the name of the target operating system
#SET(CMAKE_SYSTEM_NAME Windows)
#SET(CMAKE_SYSTEM_NAME Generic)
#SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_NAME Darwin)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER __CC__ -I__ROOT__/include/)
SET(CMAKE_CXX_COMPILER __CCC__ -I__ROOT__/include/)
SET(CMAKE_RC_COMPILER __WINDRES__)
set(CMAKE_AR x86_64-apple-darwin12-ar CACHE FILEPATH "Archiver")

# here is the target environment located
# SET(CMAKE_FIND_ROOT_PATH  /usr/i586-mingw32msvc /home/alex/mingw-install )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#set(CMAKE_BUILD_TYPE RELEASE)
#set(CMAKE_C_FLAGS "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb")
