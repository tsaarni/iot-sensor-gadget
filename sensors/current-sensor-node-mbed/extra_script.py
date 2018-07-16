Import("env")

env.Append(CXXFLAGS=["-std=c++17",
                     "-Wno-register"])

env.Append(LINKFLAGS=["--specs=nano.specs",
                      "-u", "_printf_float"])

#env.Append(
#  LINKFLAGS=[
#      "-specs=nosys.specs",
#      "-lrdimon",
#  ]
#)
#      "-lrdimon",
#      "-lc",

#      "-specs=rdimon.specs",
#      "-specs=nosys.specs",
