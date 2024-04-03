@_exported import WrapperObjc
import simd

extension Array {
  func convertToUnsafePointer() -> UnsafePointer<Element> {
    let pointer = UnsafeMutablePointer<Element>.allocate(capacity: count)
    pointer.initialize(from: self, count: count)
    return UnsafePointer(pointer)
  }
}

struct NurbsData: Decodable {
    let degree: Int32
    let controlPoints: [simd_float4]
    let knotVector: [Float]
}

public enum NurbsSplineError: Error {
  case fileNotFound
  case noJsonData
}

public extension NurbsSpline {
  convenience init(degree: Int32, controlPoints: [simd_float4], knots: [Float]) {
    self.init(
      degree: degree,
      controlPoints: controlPoints.convertToUnsafePointer(),
      count: Int32(controlPoints.count),
      knots: knots.convertToUnsafePointer(),
      knotCount: Int32(knots.count)
    )
  }

  convenience init(from filename: String, bundle: Bundle = .main) throws {
    let decoder = JSONDecoder()

    guard let fileURL = bundle.url(forResource: filename, withExtension: nil) else {
      throw NurbsSplineError.fileNotFound
    }

    let data = try Data(contentsOf: fileURL)
    let nurbsData = try decoder.decode([NurbsData].self, from: data)

    guard let firstNurbs = nurbsData.first else {
      throw NurbsSplineError.noJsonData
    }

    self.init(
      degree: firstNurbs.degree,
      controlPoints: firstNurbs.controlPoints,
      knots: firstNurbs.knotVector
    )
  }
}
