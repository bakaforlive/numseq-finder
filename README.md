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

### Example of usage
```bash
# ./numseq_finder
Hello, 555,3512 and 5223 World.
3512 5223
```

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

## Additional details
- This small project's goal was to train my dynamic memory and usage of complex dynamic data structures skill. 
- Program uses Linked List with dynamic array inside to store all number sequences and String Table (character matrix) to store results of search.
- Program was meant to be slightly overengineered to give me some sort of challenge.
