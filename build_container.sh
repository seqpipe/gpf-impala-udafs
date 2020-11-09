#!/bin/bash

if [[ -z $WD ]]; then
    SCRIPT_LOCATION=$(readlink -f "$0")
    export WD=$(dirname "${SCRIPT_LOCATION}")
fi

if [[ -z $GPF_UDAF_IMAGE ]]; then
    export GPF_UDAF_IMAGE="gpf-impala-udaf-test-image"
fi

docker build -t $GPF_UDAF_IMAGE $WD

