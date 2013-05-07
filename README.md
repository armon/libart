libart [![Build Status](https://travis-ci.org/armon/libart.png)](https://travis-ci.org/armon/libart)
=========

This library probides an ANCI C implementation of the Adaptive Radix
Tree or ART. The ART operates similar to a traditional Radix tree but
avoids the wasted space of internal nodes by changing the node size.
It makes use of 4 node sizes (4, 16, 48, 256), and can guarentee that
the overhead is no more than 52 bytes per key, though in practice it is
much lower.

As a Radix tree, it provides the following:
 * O(k) operations. In many cases, this can be faster than hash table since
   the hash is actually an O(k) operation, and hash table has very poor cache locality.
 * Ordered iteration
 * Minimum / Maximum value lookups


Usage
-------

Building the test code may generate errors if libcheck is not available.
To build the test code successfully, do the following::

    $ cd deps/check-0.9.8/
    $ ./configure
    $ make
    # make install
    # ldconfig (necessary on some Linux distros)
    $ cd ../../
    $ scons
    $ ./test_runner


References
----------

Related works:

* [The Adaptive Radix Tree: ARTful Indexing for Main-Memory Databases](http://www-db.in.tum.de/~leis/papers/ART.pdf)

