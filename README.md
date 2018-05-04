# Parse-Tree-in-C
An implemention of Parse Tree for a Parser in C

### Building
First, download the dependencies:
```bash
./download_dependencies.sh
```

Then, to build the static library, run the following commands from the terminal:
```bash
mkdir build ; cd build && cmake .. && make ; cd ..
```
This will build ```libParseTree.a``` in ```./lib``` directory.

### Usage
See ```include/ParseTree.h``` for information about functionality provided by this module
