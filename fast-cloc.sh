# use cloc to count lines of code here
# exclude deps/, cmake-build-*/, chiisai-llvm/include/chiisai-llvm/autogen/, chiisai-llvm/src/autogen/, cact-front-end/autogen/
cloc . --exclude-dir=deps,cmake-build-debug --not-match-d='chiisai-llvm/include/chiisai-llvm/autogen|chiisai-llvm/src/autogen|cact-front-end/autogen'
