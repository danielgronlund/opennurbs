// swift-tools-version: 5.9

import PackageDescription

let package = Package(
  name: "opennurbs",
  products: [
    .library(
      name: "opennurbs",
      targets: ["opennurbs"]),
  ],
  targets: [
    .target(
      name: "opennurbs",
      path: ".",
      exclude: [
        "android_uuid/",
        "example_brep/",
        "example_convert/",
        "example_files/",
        "example_gl/",
        "example_read/",
        "example_roundtrip/",
        "example_test/",
        "example_userdata/",
        "example_write/",
        "freetype263/",
        "opennurbs_unicode_cp949.cpp",
        "opennurbs_unicode_cp932.cpp",
        "opennurbs_gl.cpp"
      ],
      sources: ["."],
      cxxSettings: [
        .unsafeFlags(["-Wno-elaborated-enum-class"]),
        .define("ON_COMPILING_OPENNURBS"),
      ]
    ),
  ],
  cxxLanguageStandard: .cxx17
)
