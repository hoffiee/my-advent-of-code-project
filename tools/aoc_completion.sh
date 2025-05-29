# bash/zsh completion for aoc

_aoc_ninja_targets() {
    (
        cd build 2>/dev/null || return
        ninja -t targets all 2>/dev/null | awk '{print $1}'
    )
}

_aoc_complete() {
    local cur prev
    if [[ -n $BASH_VERSION ]]; then
        COMPREPLY=()
        cur="${COMP_WORDS[COMP_CWORD]}"
        prev="${COMP_WORDS[COMP_CWORD-1]}"
        # Complete subcommands as first argument
        if [[ $COMP_CWORD -eq 1 ]]; then
            COMPREPLY=( $(compgen -W "build format setup_day" -- "$cur") )
            return 0
        fi
        # Complete ninja targets for 'build'
        if [[ ${COMP_WORDS[1]} == "build" && $COMP_CWORD -ge 2 ]]; then
            local targets=$(_aoc_ninja_targets)
            COMPREPLY=( $(compgen -W "$targets" -- "$cur") )
            return 0
        fi
        return 0
    fi
    if [[ -n $ZSH_VERSION ]]; then
        local -a subcmds
        subcmds=(build format setup_day)
        if (( CURRENT == 2 )); then
            _describe -t commands 'aoc subcommands' subcmds
            return
        fi
        if [[ $words[2] == "build" && $CURRENT -ge 3 ]]; then
            local -a targets
            targets=($(_aoc_ninja_targets))
            _describe -t targets 'ninja targets' targets
            return
        fi
    fi
}

# Register completion
if [[ -n $BASH_VERSION ]]; then
    complete -F _aoc_complete aoc
elif [[ -n $ZSH_VERSION ]]; then
    autoload -U compinit && compinit
    compdef _aoc_complete aoc
fi
