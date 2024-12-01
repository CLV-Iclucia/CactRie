; ModuleID = '11_true_unaop'
source_filename = "11_true_unaop.cact"

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
        store i32 2, i32* %a.b.0.addr
        %b.b.0.addr = alloca i32
        %c.b.0.addr = alloca i32
        %d.b.0.addr = alloca i1
        store i1 0, i1* %d.b.0.addr
        %e.b.0.addr = alloca i1
        store i32 -2, i32* %b.b.0.addr
        %0 = load i32, i32* %b.b.0.addr
        store i32 %0, i32* %c.b.0.addr
        %1 = load i1, i1* %d.b.0.addr
        %2 = xor i1 %1, 1
        store i1 %2, i1* %e.b.0.addr
        %3 = load i32, i32* %c.b.0.addr
        ret i32 %3
        ret i32 0
}
