# Matlab-C-Random

[![File Exchange Badge](https://www.mathworks.com/matlabcentral/images/matlab-file-exchange.svg)](https://de.mathworks.com/matlabcentral/fileexchange/183375-matlab-c-random) [![GitHub top language](https://img.shields.io/github/languages/top/mathworks/climatedatastore)](https://matlab.mathworks.com/)

Simple random number generator to create the same random numbers in C and Matlab.

## Testing

```shell
gcc -O2 main.c random_generator.c -o main -lm
./main
```

```matlab
lib_rand.test()
```
