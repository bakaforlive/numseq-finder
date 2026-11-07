# numseq-finder
A maximum length number sequence finder.

## Usage
```bash
$ ./numseq_finder < {text file}
```
or
```bash
$ ./numseq_finder
{your input here}
```
To end your input from keyboard, press Ctrl+D.

## Build
To build numseq-finder, you need to install gcc, clang or other C Compiler with your package manager.


```bash
# Arch Linux
sudo pacman -S --needed gcc

git clone https://github.com/bakaforlive/numseq-finder.git
cd numseq-finder
gcc numseq_finder.c -o numseq_finder
```

Or you can install it [manually](https://gcc.gnu.org/releases.html#download).

## Contributing

PRs and issues are welcome. Fork the repo, create a branch, and submit a pull request.
