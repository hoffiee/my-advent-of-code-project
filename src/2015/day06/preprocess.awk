#!/usr/bin/awk -f
# command mapping
# turn on -> p (positive)
# turn off -> n (negatige)
# toggle -> t (toggle)

{
    # Make the coordinates a bit easier to parse for all rows
    gsub(",", " ", $0);
}

/turn on/ {
    printf("p %d %d %d %d\n", $3, $4, $6, $7);
    next
}

/turn off/ {
    printf("n %d %d %d %d\n", $3, $4, $6, $7);
    next
}

/toggle/ {
    printf("t %d %d %d %d\n", $2, $3, $5, $6);
    next
}
