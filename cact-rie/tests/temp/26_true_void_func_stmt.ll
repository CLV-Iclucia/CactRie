; ModuleID = '26_true_void_func_stmt'
source_filename = "26_true_void_func_stmt.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
define void @func(i32 %a)
{
    entry:
        %a.addr = alloca i32
        store i32 %a, i32* %a.addr
        %b.b.0.addr = alloca i32
        store i32 3, i32* %b.b.0.addr
        store i32 2, i32* %a.addr
        %0 = load i32, i32* %a.addr
        %1 = load i32, i32* %b.b.0.addr
        %2 = add i32 %0, %1
        store i32 %2, i32* %a.addr
        ret void
        ret void
}
define i32 @main()
{
    entry:
        %a.b.0.addr = alloca i32
        store i32 4, i32* %a.b.0.addr
        %b.b.0.addr = alloca i32
        store i32 2, i32* %b.b.0.addr
        %0 = load i32, i32* %b.b.0.addr
        call void @func(i32 %0)
        %1 = load i32, i32* %a.b.0.addr
        ret i32 %1
        ret i32 0
}
