add_custom_target(setup_day
    COMMAND ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/setup_day.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS venv-update
    COMMENT "Setting up day"
)
