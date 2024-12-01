; ModuleID = '38_true_same_name'
source_filename = "38_true_same_name.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
@foo.global = global i32 0
define i32 @foo(i32 %a)
{
    entry:
        %a.addr = alloca i32
        store i32 %a, i32* %a.addr
        %0 = load i32, i32* %a.addr
        %1 = load i32, i32* %a.addr
        %2 = add i32 %0, %1
        ret i32 %2
        ret i32 0
}
define i32 @main()
{
    entry:
        ret i32 0
        ret i32 0
}
