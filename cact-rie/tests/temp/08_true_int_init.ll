; ModuleID = '08_true_int_init'
source_filename = "08_true_int_init.cact"

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
        store i32 3, i32* @a.global
        ret i32 0
        ret i32 0
}
