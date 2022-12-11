find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API
documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()

set(doxyfile_in ${PROJECT_SOURCE_DIR}/docs/Doxyfile)
set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

configure_file(${doxyfile_in} ${doxyfile} @ONLY)

message("Doxygen build started.")

add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
