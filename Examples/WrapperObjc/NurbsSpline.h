#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@interface NurbsSpline : NSObject
- (instancetype)initWithDegree:(int)degree
                 controlPoints:(const simd_float4 *)controlPoints
                         count:(int)count 
                         knots:(const float *)knots
                     knotCount:(int)knotCount;

- (simd_float3)evaluateAt:(float)parameter;

@end

NS_ASSUME_NONNULL_END
