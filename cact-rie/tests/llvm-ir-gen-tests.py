import sys
import os

# get argv[1] as path to cact-rie executable string, save as cact_rie

cact_rie = sys.argv[1]

# get the dir of this python file
current_source_dir = os.path.dirname(os.path.abspath(__file__))

tests_dir = current_source_dir + "/samples_semantic/"
tests = os.listdir(tests_dir)
tests.sort()

temp_dir = current_source_dir + "/temp/"
os.system("mkdir " + temp_dir + " 2> /dev/null")
for test in tests:
    if test.split("_")[1] == "false":
        continue
    print("<<<<<<<<<<<<<< test " + test + " start! >>>>>>>>>>>>>>>")
    test_name = test.split(".")[0]
    os.system(cact_rie + " " + tests_dir + test + " -o " + temp_dir + test_name + ".ll" + " 2> /dev/null")
    os.system("cp " + tests_dir + test + " " + temp_dir + test_name + ".cpp")
    clang_compile_result = os.system("clang -S -emit-llvm " + temp_dir + test_name + ".cpp" + " -o " + temp_dir + test_name + "-std.ll" + " 2> /dev/null")
    os.system("rm " + temp_dir + test_name + ".cpp")
    if clang_compile_result != 0:
        print("\033[34m" + test + " failed to compile with clang, possibly because cact and cpp syntax are not the same\n" + "\033[0m")
        continue

    print("\nall compiled, start result check!\n--------------------\n")
    cact_rie_ret_val = os.system("lli " + temp_dir + test_name + ".ll")
    print("the llvm ir compiled by cact-rie is: " + str(cact_rie_ret_val))
    std_ret_val = os.system("lli " + temp_dir + test_name + "-std.ll")
    print("the llvm ir compiled by clang is: " + str(std_ret_val))
    print("-------result-------")
    if cact_rie_ret_val == std_ret_val:
        # use green color
        print("\033[32m" + test + " passed!\n" + "\033[0m")
    else:
        # use red color
        print("\033[31m" + test + " failed...\n" + "\033[0m")
        break

# remove temp dir
# os.system("rm -r " + temp_dir)