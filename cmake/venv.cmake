# Helpers for handling python virtual environments
# inspo
# https://stackoverflow.com/questions/30802485/cmake-setting-up-python-virtualenv

# set(AOC_PYTEST_BIN ${CMAKE_BINARY_DIR}/venv/bin/pytest)
# set(AOC_PYTHON_BIN ${CMAKE_BINARY_DIR}/venv/bin/python)

# add_custom_target(venv-create
#     COMMAND python3 -m venv venv
#     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
# )
# 
# add_custom_target(venv
#     OUTPUT venv.stamp
#     DEPENDS venv-create venv-update
#     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
# )
# 
# add_custom_target(venv-update
#     OUTPUT venv.stamp
#     DEPENDS venv-create requirements.txt
#     COMMAND . venv/bin/activate
#         && pip install -r ${PROJECT_SOURCE_DIR}/requirements.txt
#     WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
# )


#add_custom_target(venv-update
#    OUTPUT venv.stamp
#    DEPENDS venv-create requirements.txt
#    COMMAND . venv/bin/activate
#        && pip install -r ${PROJECT_SOURCE_DIR}/requirements.txt
#    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
#)

set(VENV_PYTEST
    ${CMAKE_BINARY_DIR}/venv/bin/pytest
    #${CMAKE_BINARY_DIR}/venv/bin/py.test
)
set(VENV_PYTHON ${CMAKE_BINARY_DIR}/venv/bin/python)
set(VENV_PIP ${CMAKE_BINARY_DIR}/venv/bin/pip)

add_custom_target(venv-create
    COMMAND python3 -m venv venv
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_custom_target(venv-update
    DEPENDS venv-create ${PROJECT_SOURCE_DIR}/requirements.txt
    COMMAND ${VENV_PIP} install -r ${PROJECT_SOURCE_DIR}/requirements.txt --upgrade
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
