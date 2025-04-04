![wc tool banner image](./docs/images/banner_wctool.png)
# WC Tool in C++

![C++](https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-BuildSystem-blue?style=for-the-badge&logo=cmake&logoColor=white)
![GoogleTest](https://img.shields.io/badge/GoogleTest-UnitTesting-red?style=for-the-badge)
![License](https://img.shields.io/badge/MIT-License-green?style=for-the-badge)

## Features

```bash
Usage: ccwc [OPTION] [FILE]

Options:
  -c     print the byte counts
  -w     print the word counts
  -l     print the newline counts
```

## Building

- Clone the repository.
```bash
git clone git@github.com:PrashanthaTP/wc-cpp.git
```
- Run `build.sh`. Executable `ccwc.exe` gets generated in `build` folder.
```bash
cd wc-cpp; ./build.sh
```

## Testing

- Tests are written using [GoogleTest](git@github.com:PrashanthaTP/wc-cpp.git) library.
- Run tests using `test.sh`
```bash
./test.sh
```


