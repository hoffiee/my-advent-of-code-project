#!/usr/bin/awk -f
{
    gsub("[xy,:=]"," ", $0);
    printf("%d %d %d %d\n", $3, $4, $9, $10);
}
