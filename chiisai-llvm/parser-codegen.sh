#!/bin/bash

JAVA_EXEC=$1
ANTLR_JAR=$2

${JAVA_EXEC} -jar "${ANTLR_JAR}" -Dlanguage=Cpp -package llvm -visitor -no-listener -o . ./grammar/*.g4

find ./grammar -name "*.cpp" -exec mv {} src/autogen \;
find ./grammar -name "*.cc" -exec mv {} src/autogen \;
find ./grammar -name "*.h" -exec mv {} include/mini-llvm/autogen \;
find ./grammar -name "*.hpp" -exec mv {} include/mini-llvm/autogen \;

rm ./grammar/*.interp
rm ./grammar/*.tokens