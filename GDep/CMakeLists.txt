#####
# 'GDep' Deployment:
#
# This registers the 'GDep' deployment to the build system. 
# Custom components that have not been added at the project-level should be added to 
# the list below.
#
#####

###
# Topology and Components
###
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")

# Specify the executable name
set(EXECUTABLE_NAME GDepExecutable)

# Specify the source files
set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")



# Add the executable
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Find WiringPi library
find_library(WIRINGPI_LIBRARY wiringPi)

# Check if WiringPi library is found
if(NOT WIRINGPI_LIBRARY)
    message(FATAL_ERROR "WiringPi library not found")
endif()

# Link WiringPi library to the target
target_link_libraries(${EXECUTABLE_NAME} ${WIRINGPI_LIBRARY})

# Add custom components to this specific deployment here
# add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/MyComponent/")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")
set(MOD_DEPS ${FPRIME_CURRENT_MODULE}/Top)

register_fprime_deployment()
