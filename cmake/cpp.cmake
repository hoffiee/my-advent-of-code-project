add_custom_target(lint-cpp
    COMMAND xargs cppcheck --project=compile_commands.json --suppressions-list=cppcheck_suppressions.txt . 1> /dev/null
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-cpp
    COMMAND git ls-files src libs tools
        | grep -E  '\\.cpp$$|\\.h$$'
        | xargs clang-format -Werror -i -style=file
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
