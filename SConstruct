import os

env_with_err = Environment(CCFLAGS = '-g -std=c99 -D_GNU_SOURCE -Wall -Werror -O3 -pthread -Isrc/')

# Copy the CC environment variable
if "CC" in os.environ:
    env_with_err["CC"] = os.environ["CC"]

objs = env_with_err.Object('src/art', 'src/art.c')
test_runner = env_with_err.Program('test_runner', objs + ["tests/runner.c"], LIBS=["check"])
Default(test_runner)
