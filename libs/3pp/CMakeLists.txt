# Collect third party libraries and tools here, for now keep everything in this
# file but split into directories when it makes sense
# TODO: Hmm, I've had a few issues with this setup, dig a bit whether this is
# actually a good idea


# == Icecream-cpp
# https://stackoverflow.com/questions/65586352/is-it-possible-to-use-fetchcontent-or-an-equivalent-to-add-a-library-that-has-no
# header only lib, no configure or build steps, this one fails with the
# compiler flag pedantic, my current solution is to "patch" and remove the
# superfluous ; that the library has in two lines, figure out if I can set up
# compiler flags so they are ignored for this target, or if I can run an
# automated patch so that I won't have to do it manually
# Workaround: since I'm calling find_package(.) from this subdirectory it's not
# available for other scopes. So for now I'm creating a wraper around it, but
# later on it should probably be done in a better way.
include(FetchContent)
FetchContent_Declare(icecream
    GIT_REPOSITORY https://github.com/renatoGarcia/icecream-cpp
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
Fetchcontent_MakeAvailable(icecream)
add_library(icecream INTERFACE EXCLUDE_FROM_ALL)
target_include_directories(icecream
    INTERFACE
    ${icecream_SOURCE_DIR}/
)


# == google test
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
Fetchcontent_MakeAvailable(googletest)
add_library(gtest-wrapper INTERFACE EXCLUDE_FROM_ALL)
target_link_libraries(gtest-wrapper
    INTERFACE
    GTest::gtest_main
)


# == OpenMP
# Was available on my system, skipping REQUIRED since it's not in that many
# targets.
# Workaround: since I'm calling find_package(.) from this subdirectory
# it's not available for other scopes. For now I'm creating a wraper around
# it, but later on it should probably be done in a better way.
find_package(OpenMP)
add_library(openmp-wrapper INTERFACE EXCLUDE_FROM_ALL)
target_link_libraries(openmp-wrapper
    INTERFACE
    OpenMP::OpenMP_CXX
)
