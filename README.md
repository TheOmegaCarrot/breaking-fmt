This tiny code snippet imports `fmtlib`, and asks it to format a variant which is valueless by exception.
Both the upstream version and the proposed changes will be pulled down by cmake for easy building.

Building with upstream `fmtlib` is as simple as:
```
cmake -S . -B upstream
cd upstream
make
```

Building with the proposed `fmtlib` change requires only one cmake option
```
cmake -S . -B fork -DUSE_MY_FORK=YES
cd fork
make
```
