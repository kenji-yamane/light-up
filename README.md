# light-up

Agent developed for the game [light up](https://www.chiark.greenend.org.uk/~sgtatham/puzzles/js/lightup.html).
It treats the game as a CSP (constraint satisfaction problem), using a depth-first search
policy. It uses the following heuristics:

- Minimum remaining values
- Degree heuristic
- Forward test

It has been tested on several games of 7x7, demonstrating correctness
on every tested game and in a fair amount of time (usually imperceptible,
sometimes slightly longer than 1 second).

## Execution instructions

Create a build folder, and cd into it:
```bash
mkdir -p build
cd build
```
Then, execute cmake (version 3.23 or higher required):
```bash
cmake ..
```
Now, build and execute one of two possible targets:
- `test-main`: integration tests using existing fixtures
```bash
make test-main
./test-main
```
- `agent`: executes the solution deduction given an input file game
```bash
make agent
./agent <name-of-file-input>
```

An example of a valid input file for the `agent` target follows:
```text
o o o o - o o
o o o 3 o o o
0 o o o o o o
o 1 o o o - o
o o o o o o 3
o o o - o o o
o o 2 o o o o
```
- `o` implies an empty space
- a number implies a restriction in the game
- a hyphen implies a wall in the game

## Folder structure

The project is organized as follows:
- src/
  - decision_making/
  - modeling/
  - parser/
- tst/
  - fixtures/
- bin/

Explanation of what each folder holds:

| Folder               | Contents                                                                    |
|----------------------|-----------------------------------------------------------------------------|
| src/                 | `C++` source code, holding the main for the `agent` target                  |
| src/decision_making/ | holds source code for the game search algorithm                             |
| src/modeling         | models abstracting the board world from the game                            |
| src/parser           | helper functions that parse the input into the world model                  |
| tst/                 | integration tests and fixtures, holding the main for the `test-main` target |
| tst/fixtures/        | input tests for easy application manual test                                |
| bin/                 | executable files, i.e. the generated output from build                      |
