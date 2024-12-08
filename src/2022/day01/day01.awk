#!/usr/bin/awk -f

BEGIN {
    max_calories = 0
    elf = 1
    max_elf = 1
    calories = 0
    print "begin"
}

/^$/ {
    print "New elf"

    elf += 1
    calories = 0
}

{
    calories += $1

    if (calories > max_calories) {
        max_calories = calories
        max_elf = elf
    }

}


END {
    print "end"
    printf("nr of elfs: %d\n", elf)
    printf("max elf: %d, max_calories: %d\n", max_elf, max_calories)
}

