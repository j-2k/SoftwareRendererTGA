# CMakeList.txt : CMake project for JumaGFX_CMake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (JumaGFX_CMake "JumaGFX_CMake.cpp" "JumaGFX_CMake.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JumaGFX_CMake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
