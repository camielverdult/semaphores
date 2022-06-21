This assumes that you are root and have Python (pip) installed.

```bash
rm /bin/cmake

pip install cmake --upgrade

source ~/.profile

apt install clang

cmake .
cmake --build .
```
