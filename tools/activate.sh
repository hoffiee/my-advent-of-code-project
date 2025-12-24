# Setup for aoc workspace. set it up with
# source tools/workspace

if [[ "$(git rev-parse --show-toplevel 2> /dev/null)" != "$(pwd)" ]]; then
    echo "Should be run from repo root"
    return 1
fi

deactivate_sign() {
    if [ -n "${_OLD_PS1:-}" ] ; then
        PS1="${_OLD_PS1:-}"
        export PS1
        unset _OLD_PS1
    fi
}

deactivate() {
    deactivate_sign
}

activate_sign() {
    _OLD_PS1="${PS1}"
    PS1='[aoc] '"${PS1:-}"
    export PS1
}

# Cleanup previous if sourcing again
deactivate

activate_sign

export PYTHONPATH="${PYTHONPATH}:$(git rev-parse --show-toplevel 2> /dev/null)"

source tools/aoc_completion.sh
