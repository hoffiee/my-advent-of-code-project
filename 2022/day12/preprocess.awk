#!/usr/bin/awk -f

/^  Starting items:/ {
    for (i = 3; i <= NF; ++i) {
        printf("%d ", $i);
    }
    printf("\n");
}

/^  Operation:/ {
    out = $5" "$6
    sub("old", "x", out)
    print out
}

/^  Test:/ {
    printf("%d\n", $4);
}

/^    If (true|false):/ {
    printf("%d\n", $6);
}

/^$/ {
    printf("\n");
}
