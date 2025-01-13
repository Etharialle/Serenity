new_local_repository(
    name = "sdl2",
    path = "/usr",
    build_file_content = """
cc_library(
    name = "SDL2",
    hdrs = glob(["include/SDL2/*.h"]),
    includes = ["include/SDL2"],
    linkopts = ["-lSDL2"],
    visibility = ["//visibility:public"],
)
"""
)
