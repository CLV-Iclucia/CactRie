; ModuleID = '32_true_int_float_init'
source_filename = "32_true_int_float_init.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
@a.global = global i32 0
@b.global = global i32 7
define i32 @main()
{
    entry:
        %c.b.0.addr = alloca float
        store float 0x38DC337200000000, float* %c.b.0.addr
        %0 = load i32, i32* @b.global
        ret i32 %0
        ret i32 0
}
