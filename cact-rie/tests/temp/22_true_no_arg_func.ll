; ModuleID = '22_true_no_arg_func'
source_filename = "22_true_no_arg_func.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
define i32 @func()
{
    entry:
        %a.b.0.addr = alloca i32
        store i32 3, i32* %a.b.0.addr
        %b.b.0.addr = alloca i32
        store i32 2, i32* %b.b.0.addr
        %0 = load i32, i32* %b.b.0.addr
        %1 = load i32, i32* %a.b.0.addr
        %2 = add i32 %0, %1
        store i32 %2, i32* %b.b.0.addr
        %3 = load i32, i32* %b.b.0.addr
        ret i32 %3
        ret i32 0
}
define i32 @main()
{
    entry:
        %a.b.0.addr = alloca i32
        %0 = call i32 @func()
        store i32 %0, i32* %a.b.0.addr
        %1 = load i32, i32* %a.b.0.addr
        ret i32 %1
        ret i32 0
}
