; ModuleID = '40_true_a_lot_of_whiles'
source_filename = "40_true_a_lot_of_whiles.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
@a.global = global i32 0
define i32 @main()
{
    entry:
        %b.b.0.addr = alloca i32, i32 10
        %0 = getelementptr i32, i32* %b.b.0.addr, i32 0
        store i32 1, i32* %0
        %1 = getelementptr i32, i32* %b.b.0.addr, i32 1
        store i32 2, i32* %1
        %2 = getelementptr i32, i32* %b.b.0.addr, i32 2
        store i32 3, i32* %2
        %3 = getelementptr i32, i32* %b.b.0.addr, i32 3
        store i32 4, i32* %3
        %4 = getelementptr i32, i32* %b.b.0.addr, i32 4
        store i32 5, i32* %4
        %5 = getelementptr i32, i32* %b.b.0.addr, i32 5
        store i32 6, i32* %5
        %6 = getelementptr i32, i32* %b.b.0.addr, i32 6
        store i32 7, i32* %6
        %7 = getelementptr i32, i32* %b.b.0.addr, i32 7
        store i32 8, i32* %7
        %8 = getelementptr i32, i32* %b.b.0.addr, i32 8
        store i32 9, i32* %8
        %9 = getelementptr i32, i32* %b.b.0.addr, i32 9
        store i32 10, i32* %9
        %b.b.1.addr = alloca i32
        %b.b.2.addr = alloca i32
        br label %while0.cond
    while0.cond:
        br label %while0.loop
    while0.loop:
        br label %while0.while0.cond
    while0.while0.cond:
        %10 = load i32, i32* @a.global
        %11 = icmp slt i32 %10, 114514
        br i1 %11, label %while0.while0.loop, label %while0.while0.end
    while0.while0.loop:
        %12 = load i32, i32* @a.global
        %13 = icmp sgt i32 %12, 10
        br i1 %13, label %while0.while0.if0.then, label %while0.while0.if0.else
    while0.while0.if0.then:
        br label %while0.while0.end
    while0.while0.if0.else:
        %14 = load i32, i32* @a.global
        %15 = add i32 %14, 1
        store i32 %15, i32* @a.global
        br label %while0.while0.if0.end
    while0.while0.if0.end:
        %16 = load i32, i32* @a.global
        %17 = srem i32 %16, 2
        %18 = icmp eq i32 %17, 0
        br i1 %18, label %while0.while0.if1.then, label %while0.while0.if1.else
    while0.while0.if1.then:
        br label %while0.while0.cond
    while0.while0.if1.else:
        %19 = load i32, i32* @a.global
        %20 = srem i32 %19, 3
        %21 = icmp eq i32 %20, 0
        br i1 %21, label %while0.while0.if1.if2.then, label %while0.while0.if1.if2.else
    while0.while0.if1.if2.then:
        br label %while0.while0.end
    while0.while0.if1.if2.else:
        %22 = load i32, i32* @a.global
        %23 = srem i32 %22, 5
        %24 = icmp eq i32 %23, 0
        br i1 %24, label %while0.while0.if1.if2.if3.then, label %while0.while0.if1.if2.if3.end
    while0.while0.if1.if2.if3.then:
        store i32 114514, i32* @a.global
        br label %while0.while0.if1.if2.if3.end
    while0.while0.if1.if2.if3.end:
        br label %while0.while0.if1.if2.end
    while0.while0.if1.if2.end:
        br label %while0.while0.if1.end
    while0.while0.if1.end:
        br label %while0.while0.while0.cond
    while0.while0.while0.cond:
        %25 = load i32, i32* @a.global
        %26 = icmp sgt i32 %25, 100
        br i1 %26, label %while0.while0.while0.loop, label %while0.while0.while0.end
    while0.while0.while0.loop:
        %27 = load i32, i32* @a.global
        %28 = add i32 %27, 1
        store i32 %28, i32* @a.global
        %29 = load i32, i32* @a.global
        %30 = add i32 %29, 2
        store i32 %30, i32* %b.b.1.addr
        %31 = load i32, i32* @a.global
        %32 = load i32, i32* %b.b.1.addr
        %33 = add i32 %31, %32
        store i32 %33, i32* @a.global
        br label %while0.while0.while0.while0.cond
    while0.while0.while0.while0.cond:
        %34 = load i32, i32* @a.global
        %35 = icmp slt i32 %34, 200
        br i1 %35, label %while0.while0.while0.while0.loop, label %while0.while0.while0.while0.end
    while0.while0.while0.while0.loop:
        %36 = load i32, i32* @a.global
        %37 = sub i32 2, %36
        store i32 %37, i32* %b.b.2.addr
        %38 = load i32, i32* @a.global
        %39 = load i32, i32* %b.b.2.addr
        %40 = sub i32 %38, %39
        store i32 %40, i32* @a.global
        br label %while0.while0.while0.while0.cond
    while0.while0.while0.while0.end:
        br label %while0.while0.while0.cond
    while0.while0.while0.end:
        br label %while0.while0.cond
    while0.while0.end:
        %41 = load i32, i32* @a.global
        %42 = icmp sge i32 %41, 114514
        br i1 %42, label %while0.if0.then, label %while0.if0.else
    while0.if0.then:
        br label %while0.end
    while0.if0.else:
        br label %while0.cond
    while0.if0.end:
        br label %while0.cond
    while0.end:
        ret i32 0
        ret i32 0
}
