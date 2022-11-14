#!/bin/bash

./test_ft > ft.log

./test_std > std.log

sh diff.sh

echo "------------"

exit 0
