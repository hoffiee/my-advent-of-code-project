# Helpers for handling python virtual environments
# inspo
# https://stackoverflow.com/questions/30802485/cmake-setting-up-python-virtualenv

find_package(Python3 REQUIRED)

set(VENV_PYTEST ${CMAKE_BINARY_DIR}/venv/bin/pytest)
set(VENV_PYTHON ${CMAKE_BINARY_DIR}/venv/bin/python)
set(VENV_PIP ${CMAKE_BINARY_DIR}/venv/bin/pip)

add_custom_target(venv-create
    COMMAND ${Python3_EXECUTABLE} -m venv venv
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(venv-update
    DEPENDS venv-create ${PROJECT_SOURCE_DIR}/requirements.txt
    COMMAND ${VENV_PIP} install -r ${PROJECT_SOURCE_DIR}/requirements.txt --upgrade
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
