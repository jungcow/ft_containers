#!/bin/bash

set -eux;

make "$@" && ./"$@"

exit "$?"