// swift-tools-version: 5.9

import PackageDescription

let package = Package(
  name: "opennurbs",
  products: [
    .library(
      name: "opennurbs",
      targets: ["opennurbs"]
    ),
    .library(name: "WrapperObjc", targets: ["WrapperObjc"]),
    .library(name: "WrapperSwift", targets: ["WrapperSwift"]),
    .executable(name: "app", targets: ["app"])
  ],
  targets: [
    .target(
      name: "opennurbs",
      path: ".",
      exclude: [
        "Examples/",
        "opennurbs_unicode_cp949.cpp",
        "opennurbs_unicode_cp932.cpp",
        "opennurbs_gl.cpp"
      ],
      sources: ["."],
      cxxSettings: [
        .unsafeFlags(["-Wno-elaborated-enum-class"]),
        .define("ON_COMPILING_OPENNURBS")
      ]
    ),
    .target(
      name: "WrapperObjc",
      dependencies: ["opennurbs"],
      path: "Examples/WrapperObjc"
    ),
    .target(
      name: "WrapperSwift",
      dependencies: ["WrapperObjc"],
      path: "Examples/WrapperSwift",
      sources: ["."]
    ),
    .executableTarget(
      name: "app",
      dependencies: ["WrapperSwift"],
      path: "Examples/App/",
      sources: ["."]
    )
  ],
  cxxLanguageStandard: .cxx17
)
