This assumes that you are root and have Python (pip) installed.

## Installation
```bash
rm /bin/cmake

pip install cmake --upgrade

source ~/.profile

apt install clang
```

## Compiling
```bash
cmake .
cmake --build .
```

## Running
```bash
./semaphores
```