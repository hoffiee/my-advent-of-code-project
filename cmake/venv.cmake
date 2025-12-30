# Helpers for handling python virtual environments
# inspo
# https://stackoverflow.com/questions/30802485/cmake-setting-up-python-virtualenv

find_package(Python3 REQUIRED)

set(VENV_PYTEST ${CMAKE_BINARY_DIR}/venv/bin/pytest)
set(VENV_PYTHON ${CMAKE_BINARY_DIR}/venv/bin/python)
set(VENV_PIP ${CMAKE_BINARY_DIR}/venv/bin/pip)

# Set a stamp so that the venv-update is only ran when requirements.txt has changed
set(VENV_STAMP "${CMAKE_BINARY_DIR}/venv_stamp.txt")
# Remove to force check
file(REMOVE "${VENV_STAMP}")

add_custom_command(
    OUTPUT ${VENV_STAMP}
    COMMAND ${Python3_EXECUTABLE} -m venv venv --clear  # clear forces recreate if needed
    COMMAND ${VENV_PIP} install -r ${PROJECT_SOURCE_DIR}/requirements.txt --upgrade
    COMMAND ${CMAKE_COMMAND} -E touch ${VENV_STAMP}
    DEPENDS ${PROJECT_SOURCE_DIR}/requirements.txt
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Updating venv from ${PROJECT_SOURCE_DIR}/requirements.txt"
    VERBATIM
)

add_custom_target(venv-update DEPENDS ${VENV_STAMP})
