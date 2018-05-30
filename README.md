## Generic Segment Tree

A generic segment tree build with template meta programming.

Initialization can be done either by passing
*  vector of nodes with similar structure
* default value for empty nodes
* objective function

or
Passing an expression of existing segment trees

Tree supports
* point update
* range query.
``` bash
# Generate test cases
$ make generate

# Compile segment tree
$ make tree

# Run test cases
$ make test
$ ./test --log_level=test_suite


# Compile, generate and test
$ make
```
