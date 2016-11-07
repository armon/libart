import os

# assume check was installed into /usr/local/
env_with_err = Environment(
	ENV = os.environ,
	CPPPATH = ['#/src', '#/deps/check-0.9.8/src', '/usr/local/include'])

if "CC" in os.environ:
	env_with_err["CC"] = os.environ["CC"]
if "CCFLAGS" not in os.environ:
	env_with_err["CCFLAGS"] = '-g -std=c99 -D_GNU_SOURCE -Wall -Werror -O3'
if "SHLINKFLAGS" not in os.environ:
	env_with_err['SHLINKFLAGS'] = '-shared'
#print "CCCOM is:", env_with_err.subst('$CCCOM')

shared_object = env_with_err.SharedLibrary('art', ['src/art.c'])
test_runner = env_with_err.Program('test_runner',
            ["tests/runner.c"],
            LIBS=["check", "art"],
            LIBPATH = ['#', '#/deps/check-0.9.8/src/.libs', '/usr/lib', '/usr/local/lib'])
Default(shared_object, test_runner)
