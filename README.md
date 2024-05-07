# EfficientNumberAnalyzer

The EfficientNumberAnalyzer is a C program aimed at simulating a system efficiently while exploring optimization techniques. It takes three integer parameters (`n`, `r1`, `r2`) from the command line, generates `n` positive random numbers within the range `[r1, r2]`, and stores them in a data structure. The program implements various functionalities such as searching for occurrences of a number, finding predecessors and successors, adding and deleting numbers, and finding the maximum or minimum number stored in the data structure. Additionally, it includes testing modes to ensure correct functionality.

## Usage

To use the EfficientNumberAnalyzer, compile the program using a C compiler (e.g., `cc`) and run the executable with appropriate command-line parameters (`n`, `r1`, `r2`). Ensure `r1` is greater than 0 and `r2` is greater than `r1`.

Example:
cc analyse_nums.c -o analyse_nums
./analyse_nums 100 10 50


## Performance Analysis

The program provides timings for each operation type, including the number of operations, average, and total time taken for each operation type. It also investigates techniques for efficient searching, adding, deleting, and finding extremum values in the data structure. Additionally, it discusses data compression techniques and their impact on memory usage and computational efficiency.

## File Structure

- `analyse_nums.c`: Source code for the EfficientNumberAnalyzer program.
- `nums_results.docx`: Report on testing and findings, including program output and performance analysis.

## Compilation

Compile the program using a C compiler. Example:
cc analyse_nums.c -o analyse_nums
