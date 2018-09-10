# Cruthu: Terrain Generation
Cruthú (Gaelic for "creation", pronounced cra-HU), provides a platform world generation.
Cruthú is highly modular, allowing modules to be swapped in, swapped out, or re-ordered to achieve desired results.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and or use.

### Prerequisites
Currently only tested on Linux 4.18.5, there are somethings that would not transfer crossplatform well, but that can be changed.
* CMake >= 3.9
* GLM
* C++ Compiler
* STDC++17

#### Arch Linux
```bash
pacman -S cmake glm clang
```

### Installing
Clone the project to the where ever, I will assume that PROJECT_ROOT is that place.

First, CMake supports out-of-source builds , so lets use that to advatage and not dirty the repo. So we will make a build directory, I will reference it as BUILD_DIR
```bash
cd <PROJECT_ROOT>
mkdir <BUILD_DIR>
```

After we have a place to build our system, we will move into it and execute CMake to generate the build structure
```bash
cd <BUILD_DIR>
cmake ..
```
**NOTE:** CMake defaults the install path of ```make install``` [to /usr/local on UNIX and c:/Program Files/${PROJECT_NAME} on Windows.][1] If you would like to install this else where, add `-DCMAKE_INSTALL_PREFIX` onto the cmake command
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=~/.local
```
Now that the build files are prepared, we can proceede to compiling.
```bash
make
```
And then to install it.
```bash
make install
```

**NOTE:** CMake does not require you to use make, you could use ninja. I have not tested this with other other than make though.

### Uninstalling
Since this is not a package from a package manager, it cannot be removed this way. I reccomend keeping the build files around, as they leave a file called `install_manifest.txt` that can be used to find the isntalled files. Below is an example:
```bash
cat install_manifest.txt | xargs rm {}
```

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* My committee members on my Thesis
* Every walk through and such for the code help
  * Really would like to point out [theo-pnv][2], and the code he set up in a turorial for the DLLoader class.

[1]: https://cmake.org/cmake/help/v3.9/variable/CMAKE_INSTALL_PREFIX.html
[2]: https://github.com/theo-pnv/Dynamic-Loading
