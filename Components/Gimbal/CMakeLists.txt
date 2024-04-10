####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Gimbal.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Gimbal.cpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Add your dependencies here
# )

# Add include directories for WiringPi
include_directories(/usr/local/include)

# Create the component library
add_library(Gimbal ${SOURCE_FILES})

set(MOD_DEPS
    "/usr/lib/libwiringPi.so"
)

# Add WiringPi library to the target
target_link_libraries(Gimbal wiringPi)

# Register the F prime module
register_fprime_module()
