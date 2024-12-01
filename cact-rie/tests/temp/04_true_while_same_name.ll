; ModuleID = '04_true_while_same_name'
source_filename = "04_true_while_same_name.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
define i32 @main()
{
    entry:
        %i.b.0.addr = alloca i32
        store i32 0, i32* %i.b.0.addr
        %b.b.0.addr = alloca i32
        store i32 0, i32* %b.b.0.addr
        %b.b.1.addr = alloca i32
        store i32 1, i32* %b.b.1.addr
        br label %while0.cond
    while0.cond:
        %0 = load i32, i32* %i.b.0.addr
        %1 = icmp slt i32 %0, 3
        br i1 %1, label %while0.loop, label %while0.end
    while0.loop:
        %2 = load i32, i32* %i.b.0.addr
        %3 = load i32, i32* %b.b.1.addr
        %4 = add i32 %2, %3
        store i32 %4, i32* %i.b.0.addr
        br label %while0.cond
    while0.end:
        %5 = load i32, i32* %b.b.0.addr
        ret i32 %5
        ret i32 0
}
