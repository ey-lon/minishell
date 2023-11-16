# minishell

A simplified version of a real shell to learn about processes.

## Usage
| command | description |
| ------- | ----------- |
| `make` | compile *minishell* |
| `make clean` | remove tmp files |
| `make fclean` | remove tmp files and executable |
| `make re` | force recompile |

## How to launch
```shell
./minishell
```
## How to launch with suppression file
```shell
valgrind --suppressions=readline.supp ./minishell
```
