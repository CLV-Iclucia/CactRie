; ModuleID = '/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/41_true_short_circuit.cpp'
source_filename = "/home/creeper/CLionProjects/CactRie/cact-rie/tests/temp/41_true_short_circuit.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a_global = dso_local global i32 1, align 4
@__const.main.arr = private unnamed_addr constant [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4], align 16

; Function Attrs: mustprogress noinline nounwind optnone sspstrong uwtable
define dso_local noundef zeroext i1 @_Z12fucking_booli(i32 noundef %0) #0 {
  %2 = alloca i1, align 1
  %3 = alloca i32, align 4
  store i32 %0, ptr %3, align 4
  %4 = load i32, ptr @a_global, align 4
  %5 = add nsw i32 %4, 1
  store i32 %5, ptr @a_global, align 4
  %6 = load i32, ptr @a_global, align 4
  %7 = load i32, ptr %3, align 4
  %8 = icmp sgt i32 %6, %7
  br i1 %8, label %9, label %10

9:                                                ; preds = %1
  store i1 true, ptr %2, align 1
  br label %11

10:                                               ; preds = %1
  store i1 false, ptr %2, align 1
  br label %11

11:                                               ; preds = %10, %9
  %12 = load i1, ptr %2, align 1
  ret i1 %12
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone sspstrong uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca [5 x i32], align 16
  %7 = alloca i8, align 1
  %8 = alloca i8, align 1
  %9 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 1, ptr %2, align 4
  store i32 0, ptr %3, align 4
  store i32 5, ptr %4, align 4
  store i32 2, ptr %5, align 4
  call void @llvm.memcpy.p0.p0.i64(ptr align 16 %6, ptr align 16 @__const.main.arr, i64 20, i1 false)
  store i8 0, ptr %7, align 1
  %10 = load i32, ptr %2, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, ptr %2, align 4
  %12 = load i32, ptr %3, align 4
  %13 = add nsw i32 %12, 3
  %14 = load i32, ptr %2, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 %15
  %17 = load i32, ptr %16, align 4
  %18 = add nsw i32 %13, %17
  store i32 %18, ptr %3, align 4
  %19 = load i32, ptr %2, align 4
  %20 = icmp eq i32 %19, 1
  br i1 %20, label %21, label %25

21:                                               ; preds = %0
  %22 = load i32, ptr %3, align 4
  %23 = call noundef zeroext i1 @_Z12fucking_booli(i32 noundef %22)
  br i1 %23, label %24, label %25

24:                                               ; preds = %21
  store i32 1, ptr %1, align 4
  br label %223

25:                                               ; preds = %21, %0
  %26 = load i32, ptr %2, align 4
  %27 = icmp eq i32 %26, 1
  br i1 %27, label %31, label %28

28:                                               ; preds = %25
  %29 = load i32, ptr %3, align 4
  %30 = icmp sgt i32 %29, 1
  br i1 %30, label %31, label %32

31:                                               ; preds = %28, %25
  store i32 2, ptr %1, align 4
  br label %223

32:                                               ; preds = %28
  br label %33

33:                                               ; preds = %32
  %34 = load i32, ptr %2, align 4
  %35 = icmp sgt i32 %34, 1
  br i1 %35, label %36, label %40

36:                                               ; preds = %33
  %37 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 0
  %38 = load i32, ptr %37, align 16
  %39 = icmp sgt i32 %38, 0
  br i1 %39, label %47, label %40

40:                                               ; preds = %36, %33
  %41 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 1
  %42 = load i32, ptr %41, align 4
  %43 = icmp sgt i32 %42, 1
  br i1 %43, label %44, label %48

44:                                               ; preds = %40
  %45 = load i32, ptr %4, align 4
  %46 = icmp sgt i32 %45, 3
  br i1 %46, label %47, label %48

47:                                               ; preds = %44, %36
  store i32 3, ptr %1, align 4
  br label %223

48:                                               ; preds = %44, %40
  %49 = load i32, ptr %5, align 4
  %50 = add nsw i32 %49, 2
  %51 = icmp sgt i32 %50, 2
  br i1 %51, label %52, label %56

52:                                               ; preds = %48
  %53 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 4
  %54 = load i32, ptr %53, align 16
  %55 = icmp sgt i32 %54, 4
  br i1 %55, label %59, label %56

56:                                               ; preds = %52, %48
  %57 = load i32, ptr %4, align 4
  %58 = icmp sgt i32 %57, 2
  br i1 %58, label %59, label %60

59:                                               ; preds = %56, %52
  store i32 4, ptr %1, align 4
  br label %223

60:                                               ; preds = %56
  %61 = load i32, ptr %3, align 4
  %62 = icmp sgt i32 %61, 1
  br i1 %62, label %63, label %67

63:                                               ; preds = %60
  %64 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 2
  %65 = load i32, ptr %64, align 8
  %66 = icmp sgt i32 %65, 2
  br i1 %66, label %71, label %67

67:                                               ; preds = %63, %60
  %68 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 3
  %69 = load i32, ptr %68, align 4
  %70 = icmp eq i32 %69, 3
  br i1 %70, label %71, label %72

71:                                               ; preds = %67, %63
  store i32 5, ptr %1, align 4
  br label %223

72:                                               ; preds = %67
  %73 = load i32, ptr %2, align 4
  %74 = icmp sgt i32 %73, 1
  br i1 %74, label %84, label %75

75:                                               ; preds = %72
  %76 = load i32, ptr %3, align 4
  %77 = icmp sgt i32 %76, 0
  br i1 %77, label %78, label %85

78:                                               ; preds = %75
  %79 = load i32, ptr %4, align 4
  %80 = icmp ne i32 %79, 5
  br i1 %80, label %81, label %85

81:                                               ; preds = %78
  %82 = load i32, ptr %5, align 4
  %83 = icmp sgt i32 %82, 2
  br i1 %83, label %84, label %85

84:                                               ; preds = %81, %72
  store i32 6, ptr %1, align 4
  br label %223

85:                                               ; preds = %81, %78, %75
  %86 = load i32, ptr %2, align 4
  %87 = icmp eq i32 %86, 2
  br i1 %87, label %88, label %91

88:                                               ; preds = %85
  %89 = load i32, ptr %3, align 4
  %90 = icmp sgt i32 %89, 3
  br i1 %90, label %94, label %91

91:                                               ; preds = %88, %85
  %92 = load i32, ptr %4, align 4
  %93 = icmp sgt i32 %92, 4
  br i1 %93, label %94, label %95

94:                                               ; preds = %91, %88
  store i32 7, ptr %1, align 4
  br label %223

95:                                               ; preds = %91
  %96 = load i32, ptr %2, align 4
  %97 = icmp sgt i32 %96, 2
  br i1 %97, label %98, label %105

98:                                               ; preds = %95
  %99 = load i32, ptr %3, align 4
  %100 = icmp sgt i32 %99, 3
  br i1 %100, label %101, label %105

101:                                              ; preds = %98
  %102 = load i32, ptr %4, align 4
  %103 = icmp sgt i32 %102, 4
  br i1 %103, label %104, label %105

104:                                              ; preds = %101
  store i32 8, ptr %1, align 4
  br label %223

105:                                              ; preds = %101, %98, %95
  %106 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 0
  %107 = load i32, ptr %106, align 16
  %108 = icmp sgt i32 %107, 0
  br i1 %108, label %109, label %114

109:                                              ; preds = %105
  %110 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 2
  %111 = load i32, ptr %110, align 8
  %112 = icmp sgt i32 %111, 2
  br i1 %112, label %113, label %114

113:                                              ; preds = %109
  store i32 9, ptr %1, align 4
  br label %223

114:                                              ; preds = %109, %105
  %115 = load i32, ptr %2, align 4
  %116 = icmp sgt i32 %115, 2
  br i1 %116, label %131, label %117

117:                                              ; preds = %114
  %118 = load i32, ptr %3, align 4
  %119 = icmp sgt i32 %118, 1
  br i1 %119, label %120, label %127

120:                                              ; preds = %117
  %121 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 3
  %122 = load i32, ptr %121, align 4
  %123 = icmp sle i32 %122, 2
  br i1 %123, label %124, label %127

124:                                              ; preds = %120
  %125 = load i32, ptr %5, align 4
  %126 = icmp ne i32 %125, 0
  br i1 %126, label %131, label %127

127:                                              ; preds = %124, %120, %117
  %128 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 1
  %129 = load i32, ptr %128, align 4
  %130 = icmp sgt i32 %129, 1
  br i1 %130, label %131, label %132

131:                                              ; preds = %127, %124, %114
  store i32 114514, ptr %2, align 4
  br label %132

132:                                              ; preds = %131, %127
  %133 = load i8, ptr %7, align 1
  %134 = trunc i8 %133 to i1
  br i1 %134, label %135, label %138

135:                                              ; preds = %132
  %136 = load i32, ptr %2, align 4
  %137 = add nsw i32 %136, 1
  store i32 %137, ptr %2, align 4
  br label %222

138:                                              ; preds = %132
  %139 = load i32, ptr %2, align 4
  %140 = icmp sgt i32 %139, 114514
  br i1 %140, label %144, label %141

141:                                              ; preds = %138
  %142 = load i32, ptr %2, align 4
  %143 = call noundef zeroext i1 @_Z12fucking_booli(i32 noundef %142)
  br i1 %143, label %144, label %177

144:                                              ; preds = %141, %138
  br label %145

145:                                              ; preds = %175, %144
  %146 = load i32, ptr %2, align 4
  %147 = icmp sgt i32 %146, 1
  br i1 %147, label %157, label %148

148:                                              ; preds = %145
  %149 = load i32, ptr %3, align 4
  %150 = icmp sgt i32 %149, 0
  br i1 %150, label %151, label %155

151:                                              ; preds = %148
  %152 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 2
  %153 = load i32, ptr %152, align 8
  %154 = icmp sgt i32 %153, 2
  br label %155

155:                                              ; preds = %151, %148
  %156 = phi i1 [ false, %148 ], [ %154, %151 ]
  br label %157

157:                                              ; preds = %155, %145
  %158 = phi i1 [ true, %145 ], [ %156, %155 ]
  br i1 %158, label %159, label %176

159:                                              ; preds = %157
  %160 = load i32, ptr %2, align 4
  %161 = add nsw i32 %160, 1
  store i32 %161, ptr %2, align 4
  %162 = load i32, ptr %2, align 4
  %163 = call noundef zeroext i1 @_Z12fucking_booli(i32 noundef %162)
  br i1 %163, label %164, label %175

164:                                              ; preds = %159
  %165 = load i32, ptr %3, align 4
  %166 = add nsw i32 %165, 1
  %167 = sext i32 %166 to i64
  %168 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 %167
  %169 = load i32, ptr %168, align 4
  %170 = icmp sgt i32 %169, 3
  br i1 %170, label %171, label %175

171:                                              ; preds = %164
  %172 = load i32, ptr %4, align 4
  %173 = call noundef zeroext i1 @_Z12fucking_booli(i32 noundef %172)
  br i1 %173, label %174, label %175

174:                                              ; preds = %171
  store i8 1, ptr %7, align 1
  br label %175

175:                                              ; preds = %174, %171, %164, %159
  br label %145, !llvm.loop !6

176:                                              ; preds = %157
  br label %221

177:                                              ; preds = %141
  %178 = load i8, ptr %7, align 1
  %179 = trunc i8 %178 to i1
  br i1 %179, label %180, label %184

180:                                              ; preds = %177
  %181 = getelementptr inbounds [5 x i32], ptr %6, i64 0, i64 1
  %182 = load i32, ptr %181, align 4
  %183 = icmp sgt i32 %182, 1
  br i1 %183, label %187, label %184

184:                                              ; preds = %180, %177
  %185 = load i32, ptr %4, align 4
  %186 = icmp sgt i32 %185, 5
  br i1 %186, label %187, label %190

187:                                              ; preds = %184, %180
  %188 = load i32, ptr %2, align 4
  %189 = add nsw i32 %188, 2
  store i32 %189, ptr %2, align 4
  br label %220

190:                                              ; preds = %184
  %191 = load i32, ptr %2, align 4
  %192 = icmp sgt i32 %191, 1
  br i1 %192, label %193, label %197

193:                                              ; preds = %190
  %194 = load i32, ptr %5, align 4
  %195 = sub nsw i32 %194, 2
  %196 = icmp sgt i32 %195, 2
  br i1 %196, label %201, label %197

197:                                              ; preds = %193, %190
  %198 = load i32, ptr %4, align 4
  %199 = add nsw i32 %198, 5
  %200 = icmp sgt i32 %199, 6
  br i1 %200, label %201, label %216

201:                                              ; preds = %197, %193
  %202 = load i32, ptr %4, align 4
  %203 = mul nsw i32 %202, 114514
  store i32 %203, ptr %4, align 4
  store i8 0, ptr %8, align 1
  %204 = call noundef zeroext i1 @_Z12fucking_booli(i32 noundef 114515)
  %205 = zext i1 %204 to i8
  store i8 %205, ptr %8, align 1
  %206 = load i8, ptr %8, align 1
  %207 = trunc i8 %206 to i1
  br i1 %207, label %208, label %215

208:                                              ; preds = %201
  store i32 1919810, ptr %9, align 4
  %209 = load i32, ptr %9, align 4
  %210 = add nsw i32 %209, 1
  store i32 %210, ptr %9, align 4
  %211 = load i32, ptr %4, align 4
  %212 = load i32, ptr %9, align 4
  %213 = add nsw i32 %211, %212
  %214 = add nsw i32 %213, 1
  store i32 %214, ptr %4, align 4
  br label %215

215:                                              ; preds = %208, %201
  br label %219

216:                                              ; preds = %197
  %217 = load i32, ptr %5, align 4
  %218 = mul nsw i32 %217, 19260817
  store i32 %218, ptr %5, align 4
  br label %219

219:                                              ; preds = %216, %215
  br label %220

220:                                              ; preds = %219, %187
  br label %221

221:                                              ; preds = %220, %176
  br label %222

222:                                              ; preds = %221, %135
  store i32 0, ptr %1, align 4
  br label %223

223:                                              ; preds = %222, %113, %104, %94, %84, %71, %59, %47, %31, %24
  %224 = load i32, ptr %1, align 4
  ret i32 %224
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #2

attributes #0 = { mustprogress noinline nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: readwrite) }

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
