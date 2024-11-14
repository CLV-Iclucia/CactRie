# use cloc to count lines of code here
# exclude deps/, cmake-build-*/, chiisai-llvm/include/chiisai-llvm/autogen/, chiisai-llvm/src/autogen/, cact-front-end/autogen/
cloc . --not-match-d='^(deps|cmake-build-|chiisai-llvm/include/chiisai-llvm/autogen|chiisai-llvm/src/autogen|cact-front-end/autogen)'
