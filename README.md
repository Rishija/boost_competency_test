## Boost Competency Test
#### 5\. Enhancing Boost.Intrusive Library \[gsoc18\]

``` bash
# Generate test cases
$ g++ random.cpp -o random
$ ./random

# Run tests
$ g++ test.cpp -o test -lboost_unit_test_framework-mt -std=c++14
$ ./test --log_level=test_suite
```
