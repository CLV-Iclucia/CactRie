; ModuleID = '20_true_builtin_func'
source_filename = "20_true_builtin_func.cact"

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
        %a.b.0.addr = alloca float
        %b.b.0.addr = alloca i32
        %0 = call float @get_float()
        store float %0, float* %a.b.0.addr
        %1 = load float, float* %a.b.0.addr
        call void @print_float(float %1)
        %2 = call i32 @get_int()
        store i32 %2, i32* %b.b.0.addr
        %3 = load i32, i32* %b.b.0.addr
        ret i32 %3
        ret i32 0
}
