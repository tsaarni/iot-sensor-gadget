Import("env")
env.Append(LINKFLAGS=["--specs=nano.specs", "-u", "_printf_float"])
