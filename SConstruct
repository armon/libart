import os

# assume check was installed into /usr/local/
env_with_err = Environment(
	ENV = os.environ,
	CPPPATH = ['#/src', '/usr/local/include'])
if "CC" in os.environ:
	env_with_err["CC"] = os.environ["CC"]
if "CCFLAGS" not in os.environ:
	env_with_err["CCFLAGS"] = '-g -std=c99 -D_GNU_SOURCE -Wall -Werror -O3'
#print "CCCOM is:", env_with_err.subst('$CCCOM')

objs = env_with_err.Object('src/art', 'src/art.c')
test_runner = env_with_err.Program('test_runner',
            objs + ["tests/runner.c"],
            LIBS=["check"],
            LIBPATH = ['/usr/lib', '/usr/local/lib'])
Default(test_runner)
