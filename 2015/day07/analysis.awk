#!/usr/bin/awk -f

BEGIN {
    count_lshift = 0
    count_rshift = 0
    count_and = 0
    count_or = 0
}

/LSHIFT/ {
    count_lshift += 1
}
/RSHIFT/ {
    count_rshift += 1
}
/AND/ {
    count_and += 1
}
/OR/ {
    count_or += 1
}

NF == 5 && $1 ~ /^[0-9]+$/ {

}

NF == 5 && $3 ~ /^[0-9]+$/ {

}

END {
    printf("lshift: %d\n", count_lshift)
    printf("rshift: %d\n", count_rshift)
    printf("and: %d\n", count_and)
    printf("or: %d\n", count_or)
}
