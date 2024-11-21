cc_binary(
    name = "overworld_generator",
    srcs = ["main.cc"],
    deps = [
        ":drunkards_walk",  # Dependency on drunkards_walk library
        ":create_map_png",  # Dependency on create_map_png library
    ],
)

cc_library(
    name = "drunkards_walk",
    srcs = ["drunkards_walk.cc"],
    hdrs = ["include/drunkards_walk.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "create_map_png",
    srcs = ["create_map_png.cc"],
    hdrs = ["include/create_map_png.h",
            "lib/stb_image_write.h"
    ],
    includes = ["lib"],
    deps = [
        ":drunkards_walk",
    ],
    visibility = ["//visibility:public"],
)