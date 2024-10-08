#!/bin/bash

JAVA_EXEC=$1
ANTLR_JAR=$2

${JAVA_EXEC} -jar "${ANTLR_JAR}" -Dlanguage=Cpp -package cactfrontend -visitor -no-listener -o . ./grammar/*.g4

mkdir -p autogen/src
mkdir -p autogen/include/cact-front-end

find ./grammar -name "*.cpp" -exec mv {} autogen/src/ \;
find ./grammar -name "*.cc" -exec mv {} autogen/src/ \;
find ./grammar -name "*.h" -exec mv {} autogen/include/cact-front-end/ \;
find ./grammar -name "*.hpp" -exec mv {} autogen/include/cact-front-end/ \;

rm ./grammar/*.interp
rm ./grammar/*.tokens
