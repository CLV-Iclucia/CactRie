; ModuleID = '/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/40_true_a_lot_of_whiles.cpp'
source_filename = "/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/40_true_a_lot_of_whiles.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = dso_local global i32 0, align 4
@__const.main.b = private unnamed_addr constant [10 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 7, i32 8, i32 9, i32 10], align 16

; Function Attrs: mustprogress noinline norecurse nounwind optnone sspstrong uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca [10 x i32], align 16
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %2, ptr align 16 @__const.main.b, i64 40, i1 false)
  br label %5

5:                                                ; preds = %0, %63
  br label %6

6:                                                ; preds = %58, %20, %5
  %7 = load i32, ptr @a, align 4
  %8 = icmp slt i32 %7, 114514
  br i1 %8, label %9, label %59

9:                                                ; preds = %6
  %10 = load i32, ptr @a, align 4
  %11 = icmp sgt i32 %10, 10
  br i1 %11, label %12, label %13

12:                                               ; preds = %9
  br label %59

13:                                               ; preds = %9
  %14 = load i32, ptr @a, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, ptr @a, align 4
  br label %16

16:                                               ; preds = %13
  %17 = load i32, ptr @a, align 4
  %18 = srem i32 %17, 2
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %20, label %21

20:                                               ; preds = %16
  br label %6, !llvm.loop !6

21:                                               ; preds = %16
  %22 = load i32, ptr @a, align 4
  %23 = srem i32 %22, 3
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %25, label %26

25:                                               ; preds = %21
  br label %59

26:                                               ; preds = %21
  %27 = load i32, ptr @a, align 4
  %28 = srem i32 %27, 5
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %31

30:                                               ; preds = %26
  store i32 114514, ptr @a, align 4
  br label %31

31:                                               ; preds = %30, %26
  br label %32

32:                                               ; preds = %31
  br label %33

33:                                               ; preds = %32
  br label %34

34:                                               ; preds = %35, %33
  br i1 false, label %35, label %36

35:                                               ; preds = %34
  store i32 0, ptr @a, align 4
  store i32 114514, ptr @a, align 4
  br label %34, !llvm.loop !8

36:                                               ; preds = %34
  br label %37

37:                                               ; preds = %57, %36
  %38 = load i32, ptr @a, align 4
  %39 = icmp sgt i32 %38, 100
  br i1 %39, label %40, label %58

40:                                               ; preds = %37
  %41 = load i32, ptr @a, align 4
  %42 = add nsw i32 %41, 1
  store i32 %42, ptr @a, align 4
  %43 = load i32, ptr @a, align 4
  %44 = add nsw i32 %43, 2
  store i32 %44, ptr %3, align 4
  %45 = load i32, ptr @a, align 4
  %46 = load i32, ptr %3, align 4
  %47 = add nsw i32 %45, %46
  store i32 %47, ptr @a, align 4
  br label %48

48:                                               ; preds = %51, %40
  %49 = load i32, ptr @a, align 4
  %50 = icmp slt i32 %49, 200
  br i1 %50, label %51, label %57

51:                                               ; preds = %48
  %52 = load i32, ptr @a, align 4
  %53 = sub nsw i32 2, %52
  store i32 %53, ptr %4, align 4
  %54 = load i32, ptr @a, align 4
  %55 = load i32, ptr %4, align 4
  %56 = sub nsw i32 %54, %55
  store i32 %56, ptr @a, align 4
  br label %48, !llvm.loop !9

57:                                               ; preds = %48
  br label %37, !llvm.loop !10

58:                                               ; preds = %37
  br label %6, !llvm.loop !6

59:                                               ; preds = %25, %12, %6
  %60 = load i32, ptr @a, align 4
  %61 = icmp sge i32 %60, 114514
  br i1 %61, label %62, label %63

62:                                               ; preds = %59
  br label %64

63:                                               ; preds = %59
  br label %5, !llvm.loop !11

64:                                               ; preds = %62
  ret i32 0
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

attributes #0 = { mustprogress noinline norecurse nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 18.1.8"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
