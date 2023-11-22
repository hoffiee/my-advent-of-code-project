get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK ${AOC_YEAR}_${AOC_DAY})

# TODO: Move input to input file
add_custom_target(${TASK}-run
    COMMAND python3 ${TASK}.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
