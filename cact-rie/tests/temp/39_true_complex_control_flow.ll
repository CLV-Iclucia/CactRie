; ModuleID = '39_true_complex_control_flow'
source_filename = "39_true_complex_control_flow.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
define void @really_complex_control_flow_func(i32 %a, double* %b, i32* %c, i1 %d, float* %g)
{
    entry:
        %a.addr = alloca i32
        store i32 %a, i32* %a.addr
        %d.addr = alloca i1
        store i1 %d, i1* %d.addr
        %e.b.0.addr = alloca i32
        store i32 114514, i32* %e.b.0.addr
        %f.b.0.addr = alloca float, i32 2
        %0 = getelementptr float, float* %f.b.0.addr, i32 0
        store float 0x44EFF99A00000000, float* %0
        %1 = getelementptr float, float* %f.b.0.addr, i32 1
        store float 0x3F80000000000000, float* %1
        br label %while0.cond
    while0.cond:
        br label %while0.loop
    while0.loop:
        %2 = load i32, i32* %a.addr
        %3 = icmp slt i32 %2, 5
        br i1 %3, label %while0.if0.then, label %while0.if0.else
    while0.if0.then:
        %4 = getelementptr i32, i32* %c, i32 1
        %5 = load i32, i32* %4
        %6 = icmp slt i32 %5, 3
        br i1 %6, label %while0.if0.if0.then, label %while0.if0.if0.else
    while0.if0.if0.then:
        %7 = load i32, i32* %a.addr
        %8 = icmp slt i32 %7, 2
        br i1 %8, label %while0.if0.if0.if0.then, label %while0.if0.if0.if0.else
    while0.if0.if0.if0.then:
        %9 = load i1, i1* %d.addr
        br i1 %9, label %while0.if0.if0.if0.if0.then, label %while0.if0.if0.if0.if0.else
    while0.if0.if0.if0.if0.then:
        store i32 1919, i32* %e.b.0.addr
        br label %while0.if0.if0.if0.if0.end
    while0.if0.if0.if0.if0.else:
        store i32 810, i32* %e.b.0.addr
        br label %while0.end
    while0.if0.if0.if0.if0.end:
        br label %while0.if0.if0.if0.end
    while0.if0.if0.if0.else:
        store i32 810, i32* %e.b.0.addr
        br label %while0.cond
    while0.if0.if0.if0.end:
        br label %while0.if0.if0.end
    while0.if0.if0.else:
        %10 = load i32, i32* %a.addr
        %11 = icmp sgt i32 %10, 1
        br i1 %11, label %while0.if0.if0.if1.then, label %while0.if0.if0.if1.else
    while0.if0.if0.if1.then:
        store i32 810, i32* %e.b.0.addr
        %12 = load i32, i32* %a.addr
        %13 = mul i32 %12, 1
        %14 = add i32 0, %13
        %15 = getelementptr float, float* %f.b.0.addr, i32 %14
        store float 0x444A800000000000, float* %15
        br label %while0.cond
    while0.if0.if0.if1.else:
        br label %while0.if0.if0.if1.end
    while0.if0.if0.if1.end:
        br label %while0.if0.if0.end
    while0.if0.if0.end:
        br label %while0.if0.end
    while0.if0.else:
        store i32 810, i32* %e.b.0.addr
        br label %while0.end
    while0.if0.end:
        %16 = load i32, i32* %a.addr
        %17 = add i32 %16, 1
        store i32 %17, i32* %a.addr
        %18 = load i32, i32* %a.addr
        %19 = mul i32 %18, 1
        %20 = add i32 0, %19
        %21 = getelementptr i32, i32* %c, i32 %20
        %22 = load i32, i32* %e.b.0.addr
        store i32 %22, i32* %21
        %23 = load i32, i32* %a.addr
        %24 = mul i32 %23, 1
        %25 = add i32 0, %24
        %26 = getelementptr i32, i32* %c, i32 %25
        %27 = load i32, i32* %26
        %28 = mul i32 %27, 9
        %29 = add i32 0, %28
        %30 = load i32, i32* %a.addr
        %31 = sub i32 %30, 1
        %32 = mul i32 %31, 3
        %33 = add i32 %29, %32
        %34 = load i32, i32* %a.addr
        %35 = mul i32 %34, 2
        %36 = mul i32 %35, 1
        %37 = add i32 %33, %36
        %38 = getelementptr double, double* %b, i32 %37
        store double 0x3FF0000000000000, double* %38
        br label %while0.cond
    while0.end:
        ret void
}
define i32 @main()
{
    entry:
        %a.b.0.addr = alloca i32
        store i32 0, i32* %a.b.0.addr
        %b.b.0.addr = alloca double, i32 18
        %0 = getelementptr double, double* %b.b.0.addr, i32 0
        store double 0x3FF0000000000000, double* %0
        %1 = getelementptr double, double* %b.b.0.addr, i32 1
        store double 0x4000000000000000, double* %1
        %2 = getelementptr double, double* %b.b.0.addr, i32 2
        store double 0x4008000000000000, double* %2
        %3 = getelementptr double, double* %b.b.0.addr, i32 3
        store double 0x4010000000000000, double* %3
        %4 = getelementptr double, double* %b.b.0.addr, i32 4
        store double 0x4014000000000000, double* %4
        %5 = getelementptr double, double* %b.b.0.addr, i32 5
        store double 0x4018000000000000, double* %5
        %6 = getelementptr double, double* %b.b.0.addr, i32 6
        store double 0x401C000000000000, double* %6
        %7 = getelementptr double, double* %b.b.0.addr, i32 7
        store double 0x4020000000000000, double* %7
        %8 = getelementptr double, double* %b.b.0.addr, i32 8
        store double 0x4022000000000000, double* %8
        %9 = getelementptr double, double* %b.b.0.addr, i32 9
        store double 0x3FF0000000000000, double* %9
        %10 = getelementptr double, double* %b.b.0.addr, i32 10
        store double 0x4000000000000000, double* %10
        %11 = getelementptr double, double* %b.b.0.addr, i32 11
        store double 0x4008000000000000, double* %11
        %12 = getelementptr double, double* %b.b.0.addr, i32 12
        store double 0x4010000000000000, double* %12
        %13 = getelementptr double, double* %b.b.0.addr, i32 13
        store double 0x4014000000000000, double* %13
        %14 = getelementptr double, double* %b.b.0.addr, i32 14
        store double 0x4018000000000000, double* %14
        %15 = getelementptr double, double* %b.b.0.addr, i32 15
        store double 0x401C000000000000, double* %15
        %16 = getelementptr double, double* %b.b.0.addr, i32 16
        store double 0x4020000000000000, double* %16
        %17 = getelementptr double, double* %b.b.0.addr, i32 17
        store double 0x4022000000000000, double* %17
        %c.b.0.addr = alloca i32, i32 2
        %18 = getelementptr i32, i32* %c.b.0.addr, i32 0
        store i32 1, i32* %18
        %19 = getelementptr i32, i32* %c.b.0.addr, i32 1
        store i32 2, i32* %19
        %d.b.0.addr = alloca i1
        store i1 1, i1* %d.b.0.addr
        %e.b.0.addr = alloca float, i32 2
        %20 = getelementptr float, float* %e.b.0.addr, i32 0
        store float 0x3F80000000000000, float* %20
        %21 = getelementptr float, float* %e.b.0.addr, i32 1
        store float 0x4000000000000000, float* %21
        %22 = load i32, i32* %a.b.0.addr
        %23 = load i1, i1* %d.b.0.addr
        call void @really_complex_control_flow_func(i32 %22, double* %b.b.0.addr, i32* %c.b.0.addr, i1 %23, float* %e.b.0.addr)
        ret i32 0
        ret i32 0
}
