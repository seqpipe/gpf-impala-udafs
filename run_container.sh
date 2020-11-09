#!/bin/bash

if [[ -z $WD ]]; then
    SCRIPT_LOCATION=$(readlink -f "$0")
    export WD=$(dirname "${SCRIPT_LOCATION}")
fi

if [[ -z $GPF_UDAF_IMAGE ]]; then
    export GPF_UDAF_IMAGE="gpf-impala-udaf-test-image"
fi

if [[ -z $GPF_UDAF_CONTAINER ]]; then
    export GPF_UDAF_CONTAINER="gpf-impala-udaf-test"
fi

echo $WD

docker run --rm \
    --name ${GPF_UDAF_CONTAINER} \
    -v $WD:/code \
    $GPF_UDAF_IMAGE /code/build_tests.sh

docker run --rm \
    --name ${GPF_UDAF_CONTAINER} \
    -v $WD:/code \
    $GPF_UDAF_IMAGE /code/run_tests.sh
