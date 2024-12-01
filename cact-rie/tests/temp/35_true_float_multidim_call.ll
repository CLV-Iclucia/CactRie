; ModuleID = '35_true_float_multidim_call'
source_filename = "35_true_float_multidim_call.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
define double @foo(double* %x, double* %y)
{
    entry:
        %0 = getelementptr double, double* %x, i32 0
        %1 = load double, double* %0
        %2 = getelementptr double, double* %y, i32 0
        %3 = load double, double* %2
        %4 = fadd double %1, %3
        ret double %4
        ret double 0.0
}
define i32 @main()
{
    entry:
        %a.b.0.addr = alloca double, i32 4
        %0 = getelementptr double, double* %a.b.0.addr, i32 0
        store double 0x3FF0000000000000, double* %0
        %1 = getelementptr double, double* %a.b.0.addr, i32 1
        store double 0x4000000000000000, double* %1
        %2 = getelementptr double, double* %a.b.0.addr, i32 2
        store double 0x3FA70A3D70A3D70A, double* %2
        %3 = getelementptr double, double* %a.b.0.addr, i32 3
        store double 0x0000000000000000, double* %3
        %4 = getelementptr double, double* %a.b.0.addr, i32 0
        %5 = getelementptr double, double* %a.b.0.addr, i32 2
        %6 = call double @foo(double* %4, double* %5)
        ret i32 0
        ret i32 0
}
