; ModuleID = '34_true_multidim_init'
source_filename = "34_true_multidim_init.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
@a.global = constant [18 x i32] [i32 1, i32 2, i32 3, i32 4, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0]
define i32 @main()
{
    entry:
        %b.b.0.addr = alloca i32, i32 6
        %0 = getelementptr i32, i32* %b.b.0.addr, i32 0
        store i32 1, i32* %0
        %1 = getelementptr i32, i32* %b.b.0.addr, i32 1
        store i32 2, i32* %1
        %2 = getelementptr i32, i32* %b.b.0.addr, i32 2
        store i32 3, i32* %2
        %3 = getelementptr i32, i32* %b.b.0.addr, i32 3
        store i32 0, i32* %3
        %4 = getelementptr i32, i32* %b.b.0.addr, i32 4
        store i32 0, i32* %4
        %5 = getelementptr i32, i32* %b.b.0.addr, i32 5
        store i32 0, i32* %5
        %6 = getelementptr i32, i32* @a.global, i32 10
        %7 = load i32, i32* %6
        %8 = getelementptr i32, i32* %b.b.0.addr, i32 3
        %9 = load i32, i32* %8
        %10 = add i32 %7, %9
        ret i32 %10
        ret i32 0
}
