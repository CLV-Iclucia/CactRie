; ModuleID = '41_true_short_circuit'
source_filename = "41_true_short_circuit.cact"

declare void @print_int(i32)

declare void @print_float(float)

declare void @print_double(double)

declare void @print_bool(i1)

declare i32 @get_int()

declare float @get_float()

declare double @get_double()
@a_global.global = global i32 1
define i1 @fucking_bool(i32 %a)
{
    entry:
        %a.addr = alloca i32
        store i32 %a, i32* %a.addr
        %0 = load i32, i32* @a_global.global
        %1 = add i32 %0, 1
        store i32 %1, i32* @a_global.global
        %2 = load i32, i32* @a_global.global
        %3 = load i32, i32* %a.addr
        %4 = icmp sgt i32 %2, %3
        br i1 %4, label %if0.then, label %if0.else
    if0.then:
        ret i1 1
    if0.else:
        ret i1 0
    if0.end:
        ret i1 0
}
define i32 @main()
{
    entry:
        %a.b.0.addr = alloca i32
        store i32 1, i32* %a.b.0.addr
        %b.b.0.addr = alloca i32
        store i32 0, i32* %b.b.0.addr
        %c.b.0.addr = alloca i32
        store i32 5, i32* %c.b.0.addr
        %d.b.0.addr = alloca i32
        store i32 2, i32* %d.b.0.addr
        %arr.b.0.addr = alloca i32, i32 5
        %0 = getelementptr i32, i32* %arr.b.0.addr, i32 0
        store i32 0, i32* %0
        %1 = getelementptr i32, i32* %arr.b.0.addr, i32 1
        store i32 1, i32* %1
        %2 = getelementptr i32, i32* %arr.b.0.addr, i32 2
        store i32 2, i32* %2
        %3 = getelementptr i32, i32* %arr.b.0.addr, i32 3
        store i32 3, i32* %3
        %4 = getelementptr i32, i32* %arr.b.0.addr, i32 4
        store i32 4, i32* %4
        %flag.b.0.addr = alloca i1
        store i1 0, i1* %flag.b.0.addr
        %a.b.1.addr = alloca i1
        store i1 0, i1* %a.b.1.addr
        %b.b.2.addr = alloca i32
        store i32 1919810, i32* %b.b.2.addr
        %flag_dummy.b.3.addr = alloca i1
        store i1 1, i1* %flag_dummy.b.3.addr
        %flag_dummy.b.4.addr = alloca i1
        %5 = load i32, i32* %a.b.0.addr
        %6 = add i32 %5, 1
        store i32 %6, i32* %a.b.0.addr
        %7 = load i32, i32* %b.b.0.addr
        %8 = add i32 %7, 3
        %9 = load i32, i32* %a.b.0.addr
        %10 = mul i32 %9, 1
        %11 = add i32 0, %10
        %12 = getelementptr i32, i32* %arr.b.0.addr, i32 %11
        %13 = load i32, i32* %12
        %14 = add i32 %8, %13
        store i32 %14, i32* %b.b.0.addr
        %15 = load i32, i32* %a.b.0.addr
        %16 = icmp eq i32 %15, 1
        br i1 %16, label %if0.sc.then, label %if0.else
    if0.sc.then:
        %17 = load i32, i32* %b.b.0.addr
        %18 = call i1 @fucking_bool(i32 %17)
        br i1 %18, label %if0.then, label %if0.else
    if0.then:
        ret i32 1
    if0.else:
        %19 = load i32, i32* %a.b.0.addr
        %20 = icmp eq i32 %19, 1
        br i1 %20, label %if0.if1.then, label %if0.if1.sc.else
    if0.if1.sc.else:
        %21 = load i32, i32* %b.b.0.addr
        %22 = icmp sgt i32 %21, 1
        br i1 %22, label %if0.if1.then, label %if0.if1.end
    if0.if1.then:
        ret i32 2
    if0.if1.end:
        br label %if0.end
    if0.end:
        %23 = load i32, i32* %a.b.0.addr
        %24 = icmp sgt i32 %23, 1
        br i1 %24, label %if2.sc.left.sc.then, label %if2.sc.else
    if2.sc.left.sc.then:
        %25 = getelementptr i32, i32* %arr.b.0.addr, i32 0
        %26 = load i32, i32* %25
        %27 = icmp sgt i32 %26, 0
        br i1 %27, label %if2.then, label %if2.sc.else
    if2.sc.else:
        %28 = getelementptr i32, i32* %arr.b.0.addr, i32 1
        %29 = load i32, i32* %28
        %30 = icmp sgt i32 %29, 1
        br i1 %30, label %if2.sc.else.sc.then, label %if2.end
    if2.sc.else.sc.then:
        %31 = load i32, i32* %c.b.0.addr
        %32 = icmp sgt i32 %31, 3
        br i1 %32, label %if2.then, label %if2.end
    if2.then:
        ret i32 3
    if2.end:
        %33 = load i32, i32* %d.b.0.addr
        %34 = add i32 %33, 2
        %35 = icmp sgt i32 %34, 2
        br i1 %35, label %if3.sc.left.sc.then, label %if3.sc.else
    if3.sc.left.sc.then:
        %36 = getelementptr i32, i32* %arr.b.0.addr, i32 4
        %37 = load i32, i32* %36
        %38 = icmp sgt i32 %37, 4
        br i1 %38, label %if3.then, label %if3.sc.else
    if3.sc.else:
        %39 = load i32, i32* %c.b.0.addr
        %40 = icmp sgt i32 %39, 2
        br i1 %40, label %if3.then, label %if3.end
    if3.then:
        ret i32 4
    if3.end:
        %41 = load i32, i32* %b.b.0.addr
        %42 = icmp sgt i32 %41, 1
        br i1 %42, label %if4.sc.left.sc.then, label %if4.sc.else
    if4.sc.left.sc.then:
        %43 = getelementptr i32, i32* %arr.b.0.addr, i32 2
        %44 = load i32, i32* %43
        %45 = icmp sgt i32 %44, 2
        br i1 %45, label %if4.then, label %if4.sc.else
    if4.sc.else:
        %46 = getelementptr i32, i32* %arr.b.0.addr, i32 3
        %47 = load i32, i32* %46
        %48 = icmp eq i32 %47, 3
        br i1 %48, label %if4.then, label %if4.end
    if4.then:
        ret i32 5
    if4.end:
        %49 = load i32, i32* %a.b.0.addr
        %50 = icmp sgt i32 %49, 1
        br i1 %50, label %if5.then, label %if5.sc.else
    if5.sc.else:
        %51 = load i32, i32* %b.b.0.addr
        %52 = icmp sgt i32 %51, 0
        br i1 %52, label %if5.sc.else.sc.left.sc.then, label %if5.end
    if5.sc.else.sc.left.sc.then:
        %53 = load i32, i32* %c.b.0.addr
        %54 = icmp ne i32 %53, 5
        br i1 %54, label %if5.sc.else.sc.then, label %if5.end
    if5.sc.else.sc.then:
        %55 = load i32, i32* %d.b.0.addr
        %56 = icmp sgt i32 %55, 2
        br i1 %56, label %if5.then, label %if5.end
    if5.then:
        ret i32 6
    if5.end:
        %57 = load i32, i32* %a.b.0.addr
        %58 = icmp eq i32 %57, 2
        br i1 %58, label %if6.sc.left.sc.then, label %if6.sc.else
    if6.sc.left.sc.then:
        %59 = load i32, i32* %b.b.0.addr
        %60 = icmp sgt i32 %59, 3
        br i1 %60, label %if6.then, label %if6.sc.else
    if6.sc.else:
        %61 = load i32, i32* %c.b.0.addr
        %62 = icmp sgt i32 %61, 4
        br i1 %62, label %if6.then, label %if6.end
    if6.then:
        ret i32 7
    if6.end:
        %63 = load i32, i32* %a.b.0.addr
        %64 = icmp sgt i32 %63, 2
        br i1 %64, label %if7.sc.left.sc.then, label %if7.end
    if7.sc.left.sc.then:
        %65 = load i32, i32* %b.b.0.addr
        %66 = icmp sgt i32 %65, 3
        br i1 %66, label %if7.sc.then, label %if7.end
    if7.sc.then:
        %67 = load i32, i32* %c.b.0.addr
        %68 = icmp sgt i32 %67, 4
        br i1 %68, label %if7.then, label %if7.end
    if7.then:
        ret i32 8
    if7.end:
        %69 = getelementptr i32, i32* %arr.b.0.addr, i32 0
        %70 = load i32, i32* %69
        %71 = icmp sgt i32 %70, 0
        br i1 %71, label %if8.sc.then, label %if8.end
    if8.sc.then:
        %72 = getelementptr i32, i32* %arr.b.0.addr, i32 2
        %73 = load i32, i32* %72
        %74 = icmp sgt i32 %73, 2
        br i1 %74, label %if8.then, label %if8.end
    if8.then:
        ret i32 9
    if8.end:
        %75 = load i32, i32* %a.b.0.addr
        %76 = icmp sgt i32 %75, 2
        br i1 %76, label %if9.then, label %if9.sc.left.sc.else
    if9.sc.left.sc.else:
        %77 = load i32, i32* %b.b.0.addr
        %78 = icmp sgt i32 %77, 1
        br i1 %78, label %if9.sc.left.sc.else.sc.left.sc.then, label %if9.sc.else
    if9.sc.left.sc.else.sc.left.sc.then:
        %79 = getelementptr i32, i32* %arr.b.0.addr, i32 3
        %80 = load i32, i32* %79
        %81 = icmp sle i32 %80, 2
        br i1 %81, label %if9.sc.left.sc.else.sc.then, label %if9.sc.else
    if9.sc.left.sc.else.sc.then:
        %82 = load i32, i32* %d.b.0.addr
        %83 = icmp ne i32 %82, 0
        br i1 %83, label %if9.then, label %if9.sc.else
    if9.sc.else:
        %84 = getelementptr i32, i32* %arr.b.0.addr, i32 1
        %85 = load i32, i32* %84
        %86 = icmp sgt i32 %85, 1
        br i1 %86, label %if9.then, label %if9.end
    if9.then:
        store i32 114514, i32* %a.b.0.addr
        br label %if9.end
    if9.end:
        %87 = load i1, i1* %flag.b.0.addr
        br i1 %87, label %if10.then, label %if10.else
    if10.then:
        %88 = load i32, i32* %a.b.0.addr
        %89 = add i32 %88, 1
        store i32 %89, i32* %a.b.0.addr
        br label %if10.end
    if10.else:
        %90 = load i32, i32* %a.b.0.addr
        %91 = icmp sgt i32 %90, 114514
        br i1 %91, label %if10.if11.then, label %if10.if11.sc.else
    if10.if11.sc.else:
        %92 = load i32, i32* %a.b.0.addr
        %93 = call i1 @fucking_bool(i32 %92)
        br i1 %93, label %if10.if11.then, label %if10.if11.else
    if10.if11.then:
        br label %if10.if11.while0.cond
    if10.if11.while0.cond:
        %94 = load i32, i32* %a.b.0.addr
        %95 = icmp sgt i32 %94, 1
        br i1 %95, label %if10.if11.while0.loop, label %if10.if11.while0.sc.else
    if10.if11.while0.sc.else:
        %96 = load i32, i32* %b.b.0.addr
        %97 = icmp sgt i32 %96, 0
        br i1 %97, label %if10.if11.while0.sc.else.sc.then, label %if10.if11.while0.end
    if10.if11.while0.sc.else.sc.then:
        %98 = getelementptr i32, i32* %arr.b.0.addr, i32 2
        %99 = load i32, i32* %98
        %100 = icmp sgt i32 %99, 2
        br i1 %100, label %if10.if11.while0.loop, label %if10.if11.while0.end
    if10.if11.while0.loop:
        %101 = load i32, i32* %a.b.0.addr
        %102 = add i32 %101, 1
        store i32 %102, i32* %a.b.0.addr
        %103 = load i32, i32* %a.b.0.addr
        %104 = call i1 @fucking_bool(i32 %103)
        br i1 %104, label %if10.if11.while0.if0.sc.left.sc.then, label %if10.if11.while0.if0.end
    if10.if11.while0.if0.sc.left.sc.then:
        %105 = load i32, i32* %b.b.0.addr
        %106 = add i32 %105, 1
        %107 = mul i32 %106, 1
        %108 = add i32 0, %107
        %109 = getelementptr i32, i32* %arr.b.0.addr, i32 %108
        %110 = load i32, i32* %109
        %111 = icmp sgt i32 %110, 3
        br i1 %111, label %if10.if11.while0.if0.sc.then, label %if10.if11.while0.if0.end
    if10.if11.while0.if0.sc.then:
        %112 = load i32, i32* %c.b.0.addr
        %113 = call i1 @fucking_bool(i32 %112)
        br i1 %113, label %if10.if11.while0.if0.then, label %if10.if11.while0.if0.end
    if10.if11.while0.if0.then:
        store i1 1, i1* %flag.b.0.addr
        br label %if10.if11.while0.if0.end
    if10.if11.while0.if0.end:
        br label %if10.if11.while0.cond
    if10.if11.while0.end:
        br label %if10.if11.end
    if10.if11.else:
        %114 = load i1, i1* %flag.b.0.addr
        br i1 %114, label %if10.if11.if12.sc.left.sc.then, label %if10.if11.if12.sc.else
    if10.if11.if12.sc.left.sc.then:
        %115 = getelementptr i32, i32* %arr.b.0.addr, i32 1
        %116 = load i32, i32* %115
        %117 = icmp sgt i32 %116, 1
        br i1 %117, label %if10.if11.if12.then, label %if10.if11.if12.sc.else
    if10.if11.if12.sc.else:
        %118 = load i32, i32* %c.b.0.addr
        %119 = icmp sgt i32 %118, 5
        br i1 %119, label %if10.if11.if12.then, label %if10.if11.if12.else
    if10.if11.if12.then:
        %120 = load i32, i32* %a.b.0.addr
        %121 = add i32 %120, 2
        store i32 %121, i32* %a.b.0.addr
        br label %if10.if11.if12.end
    if10.if11.if12.else:
        %122 = load i32, i32* %a.b.0.addr
        %123 = icmp sgt i32 %122, 1
        br i1 %123, label %if10.if11.if12.if13.sc.left.sc.then, label %if10.if11.if12.if13.sc.else
    if10.if11.if12.if13.sc.left.sc.then:
        %124 = load i32, i32* %d.b.0.addr
        %125 = sub i32 %124, 2
        %126 = icmp sgt i32 %125, 2
        br i1 %126, label %if10.if11.if12.if13.then, label %if10.if11.if12.if13.sc.else
    if10.if11.if12.if13.sc.else:
        %127 = load i32, i32* %c.b.0.addr
        %128 = add i32 %127, 5
        %129 = icmp sgt i32 %128, 6
        br i1 %129, label %if10.if11.if12.if13.then, label %if10.if11.if12.if13.else
    if10.if11.if12.if13.then:
        %130 = load i32, i32* %c.b.0.addr
        %131 = mul i32 %130, 114514
        store i32 %131, i32* %c.b.0.addr
        %132 = call i1 @fucking_bool(i32 114515)
        store i1 %132, i1* %a.b.1.addr
        %133 = load i1, i1* %a.b.1.addr
        br i1 %133, label %if10.if11.if12.if13.if0.then, label %if10.if11.if12.if13.if0.end
    if10.if11.if12.if13.if0.then:
        %134 = load i32, i32* %b.b.2.addr
        %135 = add i32 %134, 1
        store i32 %135, i32* %b.b.2.addr
        %136 = load i32, i32* %c.b.0.addr
        %137 = load i32, i32* %b.b.2.addr
        %138 = add i32 %136, %137
        %139 = add i32 %138, 1
        store i32 %139, i32* %c.b.0.addr
        br label %if10.if11.if12.if13.if0.end
    if10.if11.if12.if13.if0.end:
        br label %if10.if11.if12.if13.end
    if10.if11.if12.if13.else:
        br label %if10.if11.if12.if13.if14.else
    if10.if11.if12.if13.if14.then:
        %140 = load i32, i32* %c.b.0.addr
        %141 = mul i32 %140, 998244353
        store i32 %141, i32* %c.b.0.addr
        br label %if10.if11.if12.if13.if14.end
    if10.if11.if12.if13.if14.else:
        br label %if10.if11.if12.if13.if14.if15.then
    if10.if11.if12.if13.if14.if15.then:
        %142 = load i32, i32* %d.b.0.addr
        %143 = mul i32 %142, 19260817
        store i32 %143, i32* %d.b.0.addr
        br label %if10.if11.if12.if13.if14.if15.end
    if10.if11.if12.if13.if14.if15.else:
        br label %if10.if11.if12.if13.if14.if15.end
    if10.if11.if12.if13.if14.if15.end:
        br label %if10.if11.if12.if13.if14.end
    if10.if11.if12.if13.if14.end:
        br label %if10.if11.if12.if13.end
    if10.if11.if12.if13.end:
        br label %if10.if11.if12.end
    if10.if11.if12.end:
        br label %if10.if11.end
    if10.if11.end:
        br label %if10.end
    if10.end:
        ret i32 0
        ret i32 0
}
