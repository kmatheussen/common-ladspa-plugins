# the name of the target operating system

#INCLUDE(CMakeForceCompiler)

SET (CMAKE_CROSSCOMPILING   TRUE)
SET (CMAKE_SYSTEM_NAME      "Darwin")
#SET (CMAKE_SYSTEM_PROCESSOR "arm")

#SET (SDKVER     "4.3")
#SET (DEVROOT    "/Developer/Platforms/iPhoneOS.platform/Developer")
#SET (SDKROOT    "/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS${SDKVER}.sdk")

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER __CC__ -I__ROOT__/include/)
SET(CMAKE_CXX_COMPILER __CCC__ -I__ROOT__/include/)
SET(CMAKE_RC_COMPILER __WINDRES__)

#SET (CC         "${DEVROOT}/usr/bin/clang")
#SET (CXX        "${DEVROOT}/usr/bin/clang++")

#CMAKE_FORCE_C_COMPILER          (${CC} CLang)
#CMAKE_FORCE_CXX_COMPILER        (${CXX} CLang)

#SET (CMAKE_FIND_ROOT_PATH               "${SDKROOT}" "${DEVROOT}")
#SET (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM  NEVER)
#SET (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY  ONLY)
#SET (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE  ONLY)
