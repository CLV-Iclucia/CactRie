; ModuleID = '17_true_simple_if_else'
source_filename = "17_true_simple_if_else.cact"

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
        %a.b.0.addr = alloca i32
        store i32 3, i32* %a.b.0.addr
        %b.b.0.addr = alloca i32
        %0 = load i32, i32* %a.b.0.addr
        %1 = icmp eq i32 %0, 0
        br i1 %1, label %if0.then, label %if0.else
    if0.then:
        store i32 1, i32* %b.b.0.addr
        br label %if0.end
    if0.else:
        store i32 2, i32* %b.b.0.addr
        br label %if0.end
    if0.end:
        %2 = load i32, i32* %b.b.0.addr
        ret i32 %2
        ret i32 0
}
