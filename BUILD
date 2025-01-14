cc_binary(
    name = "serenity",
    srcs = ["src/main.cc"],
    copts = [
        "-I/usr/include/SDL2",  # SDL2 include path
        "-I.",
        "-Isrc",  # Include src directory
        "-D_REENTRANT",
    ],
    linkopts = ["-lSDL2", "-lSDL2_ttf"],
    deps = [":game_map",
            "@bazel_tools//tools/cpp/runfiles",  # ✅ Add Bazel runfiles
    ],
    data = ["//assets:assets"],  # ✅ Fix this to reference root assets
    visibility = ["//visibility:public"],
)

cc_library(
    name = "game_map",
    srcs = ["src/game_map.cc"],
    hdrs = ["src/game_map.h", "src/FastNoiseLite.h"],
    visibility = ["//visibility:public"],
)

