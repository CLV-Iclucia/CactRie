; ModuleID = '/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/39_true_complex_control_flow.cpp'
source_filename = "/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/39_true_complex_control_flow.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@__const._Z32really_complex_control_flow_funciPA3_A3_dPibPf.f = private unnamed_addr constant [2 x float] [float 0x409DFF3340000000, float 1.000000e+00], align 4
@__const.main.b = private unnamed_addr constant [2 x [3 x [3 x double]]] [[3 x [3 x double]] [[3 x double] [double 1.000000e+00, double 2.000000e+00, double 3.000000e+00], [3 x double] [double 4.000000e+00, double 5.000000e+00, double 6.000000e+00], [3 x double] [double 7.000000e+00, double 8.000000e+00, double 9.000000e+00]], [3 x [3 x double]] [[3 x double] [double 1.000000e+00, double 2.000000e+00, double 3.000000e+00], [3 x double] [double 4.000000e+00, double 5.000000e+00, double 6.000000e+00], [3 x double] [double 7.000000e+00, double 8.000000e+00, double 9.000000e+00]]], align 16
@__const.main.c = private unnamed_addr constant [2 x i32] [i32 1, i32 2], align 4
@__const.main.e = private unnamed_addr constant [2 x float] [float 1.000000e+00, float 2.000000e+00], align 4

; Function Attrs: mustprogress noinline nounwind optnone sspstrong uwtable
define dso_local void @_Z32really_complex_control_flow_funciPA3_A3_dPibPf(i32 noundef %0, ptr noundef %1, ptr noundef %2, i1 noundef zeroext %3, ptr noundef %4) #0 {
  %6 = alloca i32, align 4
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca i8, align 1
  %10 = alloca ptr, align 8
  %11 = alloca i32, align 4
  %12 = alloca [2 x float], align 4
  store i32 %0, ptr %6, align 4
  store ptr %1, ptr %7, align 8
  store ptr %2, ptr %8, align 8
  %13 = zext i1 %3 to i8
  store i8 %13, ptr %9, align 1
  store ptr %4, ptr %10, align 8
  store i32 114514, ptr %11, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 4 %12, ptr align 4 @__const._Z32really_complex_control_flow_funciPA3_A3_dPibPf.f, i64 8, i1 false)
  br label %14

14:                                               ; preds = %5, %31, %36, %44
  %15 = load i32, ptr %6, align 4
  %16 = icmp slt i32 %15, 5
  br i1 %16, label %17, label %43

17:                                               ; preds = %14
  %18 = load ptr, ptr %8, align 8
  %19 = getelementptr inbounds i32, ptr %18, i64 1
  %20 = load i32, ptr %19, align 4
  %21 = icmp slt i32 %20, 3
  br i1 %21, label %22, label %33

22:                                               ; preds = %17
  %23 = load i32, ptr %6, align 4
  %24 = icmp slt i32 %23, 2
  br i1 %24, label %25, label %31

25:                                               ; preds = %22
  %26 = load i8, ptr %9, align 1
  %27 = trunc i8 %26 to i1
  br i1 %27, label %28, label %29

28:                                               ; preds = %25
  store i32 1919, ptr %11, align 4
  br label %30

29:                                               ; preds = %25
  store i32 810, ptr %11, align 4
  br label %68

30:                                               ; preds = %28
  br label %32

31:                                               ; preds = %22
  store i32 810, ptr %11, align 4
  br label %14, !llvm.loop !6

32:                                               ; preds = %30
  br label %42

33:                                               ; preds = %17
  %34 = load i32, ptr %6, align 4
  %35 = icmp sgt i32 %34, 1
  br i1 %35, label %36, label %40

36:                                               ; preds = %33
  store i32 810, ptr %11, align 4
  %37 = load i32, ptr %6, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds [2 x float], ptr %12, i64 0, i64 %38
  store float 8.100000e+02, ptr %39, align 4
  br label %14, !llvm.loop !6

40:                                               ; preds = %33
  br label %41

41:                                               ; preds = %40
  br label %42

42:                                               ; preds = %41, %32
  br label %44

43:                                               ; preds = %14
  store i32 810, ptr %11, align 4
  br label %68

44:                                               ; preds = %42
  %45 = load i32, ptr %6, align 4
  %46 = add nsw i32 %45, 1
  store i32 %46, ptr %6, align 4
  %47 = load i32, ptr %11, align 4
  %48 = load ptr, ptr %8, align 8
  %49 = load i32, ptr %6, align 4
  %50 = sext i32 %49 to i64
  %51 = getelementptr inbounds i32, ptr %48, i64 %50
  store i32 %47, ptr %51, align 4
  %52 = load ptr, ptr %7, align 8
  %53 = load ptr, ptr %8, align 8
  %54 = load i32, ptr %6, align 4
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds i32, ptr %53, i64 %55
  %57 = load i32, ptr %56, align 4
  %58 = sext i32 %57 to i64
  %59 = getelementptr inbounds [3 x [3 x double]], ptr %52, i64 %58
  %60 = load i32, ptr %6, align 4
  %61 = sub nsw i32 %60, 1
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds [3 x [3 x double]], ptr %59, i64 0, i64 %62
  %64 = load i32, ptr %6, align 4
  %65 = mul nsw i32 %64, 2
  %66 = sext i32 %65 to i64
  %67 = getelementptr inbounds [3 x double], ptr %63, i64 0, i64 %66
  store double 1.000000e+00, ptr %67, align 8
  br label %14, !llvm.loop !6

68:                                               ; preds = %43, %29
  ret void
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #1

; Function Attrs: mustprogress noinline norecurse nounwind optnone sspstrong uwtable
define dso_local noundef i32 @main() #2 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca [2 x [3 x [3 x double]]], align 16
  %4 = alloca [2 x i32], align 4
  %5 = alloca i8, align 1
  %6 = alloca [2 x float], align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %3, ptr align 16 @__const.main.b, i64 144, i1 false)
  call void @llvm.memcpy.p0.p0.i64(ptr align 4 %4, ptr align 4 @__const.main.c, i64 8, i1 false)
  store i8 1, ptr %5, align 1
  call void @llvm.memcpy.p0.p0.i64(ptr align 4 %6, ptr align 4 @__const.main.e, i64 8, i1 false)
  %7 = load i32, ptr %2, align 4
  %8 = getelementptr inbounds [2 x [3 x [3 x double]]], ptr %3, i64 0, i64 0
  %9 = getelementptr inbounds [2 x i32], ptr %4, i64 0, i64 0
  %10 = load i8, ptr %5, align 1
  %11 = trunc i8 %10 to i1
  %12 = getelementptr inbounds [2 x float], ptr %6, i64 0, i64 0
  call void @_Z32really_complex_control_flow_funciPA3_A3_dPibPf(i32 noundef %7, ptr noundef %8, ptr noundef %9, i1 noundef zeroext %11, ptr noundef %12)
  ret i32 0
}

attributes #0 = { mustprogress noinline nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress noinline norecurse nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

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
