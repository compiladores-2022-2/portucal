# Portucal

## Compilation of top-down parsers
Execute
```
make
```

One can also compile only the recursive parser by running
```
make recur
```

Or only the iterative parser
```
make iter
```

## Execution of parser
Simply run
```
./[PARSER] < [INPUT]
```
Where `[PARSER]` is either `recur` or `iter` (referring to the recursive and iterative parsers, respectively) and `[INPUT]` is an source code to be parsed.
  
Samples of source code are avaiable in `examples` directory. For instance, executing
```
./recur < examples/binarySearch
```
would run the recursive parser on the `binarySearch` file.
