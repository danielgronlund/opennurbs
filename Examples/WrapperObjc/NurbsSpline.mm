#import "NurbsSpline.h"
#import <opennurbs.h>

@interface NurbsSpline () {
  ON_NurbsCurve *_nurbsCurve;
}

@end

@implementation NurbsSpline
- (instancetype)initWithDegree:(int)degree
                 controlPoints:(const simd_float4 *)controlPoints
                         count:(int)count
                         knots:(const float *)knots
                     knotCount:(int)knotCount {
  self = [super init];
  if (self) {
    _nurbsCurve = new ON_NurbsCurve();
    _nurbsCurve->Create(degree, false, degree + 1, count);
    for (int i = 0; i < count; ++i) {
      ON_4dPoint cv(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z, controlPoints[i].w);
      _nurbsCurve->SetCV(i, cv);
    }

    for (int i = 0; i < knotCount; ++i) {
      _nurbsCurve->SetKnot(i, knots[i]);
    }
  }
  return self;
}

- (simd_float3)evaluateAt:(float)parameter {
  ON_3dPoint resultPoint;
  if (_nurbsCurve->Evaluate(parameter, false, 0, resultPoint)) {
    return simd_make_float3(static_cast<float>(resultPoint.x), static_cast<float>(resultPoint.y), static_cast<float>(resultPoint.z));
  }

  return simd_make_float3(0.0f, 0.0f, 0.0f);
}

- (void)dealloc {
  delete _nurbsCurve;
}

@end
