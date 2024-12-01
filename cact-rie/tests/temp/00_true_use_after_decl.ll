; ModuleID = '00_true_use_after_decl'
source_filename = "00_true_use_after_decl.cact"

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
        store i32 0, i32* %a.b.0.addr
        %0 = load i32, i32* %a.b.0.addr
        ret i32 %0
        ret i32 0
}
