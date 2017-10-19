# stampsfinder-se106a-c

## Install
- `make` for Unix-like system.
- `mingw32-make` for Mingw.

## Run
- No parameters are required.

## Input & output
```shell=
./stampfinder
<Test cases>
<Test case #1 target value>
<Test case #1 number of stamps>
<Test case #1 stamp #1> <Test case #1 stamp #2> <Test case #1 stamp #3> ...
<Test case #2 target value>
<Test case #2 number of stamps>
<Test case #2 stamp #1> <Test case #2 stamp #2> <Test case #2 stamp #3> ...
...
```

```shell=
./stampfinder
1
29
5
2 3 5 6 7

[2, 3, 5, 6, 7]
[7, 7, 7, 7, 7]
35 to 29

[2, 3, 5, 6, 7]
[6, 7, 7, 7, 7]
34 to 29

[2, 3, 5, 6, 7]
[5, 7, 7, 7, 7]
33 to 29

[2, 3, 5, 6, 7]
[3, 7, 7, 7, 7]
31 to 29

[2, 3, 5, 6, 7]
[2, 7, 7, 7, 7]
30 to 29

[2, 3, 5, 6, 7]
[7, 7, 7, 7]
28 to 29

[2, 3, 5, 6, 7]
[6, 6, 7, 7, 7]
33 to 29

[2, 3, 5, 6, 7]
[5, 6, 7, 7, 7]
32 to 29

[2, 3, 5, 6, 7]
[3, 6, 7, 7, 7]
30 to 29

[2, 3, 5, 6, 7]
[2, 6, 7, 7, 7]
29 to 29
```
