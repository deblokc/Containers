#!/bin/bash

awk 'FNR==NR { a[FNR""] = $0; next } { print a[FNR""], $0 }' std.log ft.log | awk -e '/^[0-9]*\.[0-9]*s\s[0-9]*\.[0-9]*s$/ {print $1 " " $2}' | awk -e '{printf("%+f%\n", (($1 - $2)*100)/$1)}'
