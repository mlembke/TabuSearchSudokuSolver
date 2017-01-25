import random
import argparse

import sudoku_generator as sg


def main():
    random.seed()
    parser = argparse.ArgumentParser(
        description="Generates Sudoku puzzle with given number of fixed digits and write it to output file")
    parser.add_argument("-o", "--outfile", type=str, default="sudoku.txt", help="output file")
    parser.add_argument("-f", "--fixed", type=int, default=20, help="number of fixed digits")
    parser.add_argument("-b", "--boxsize", type=int, default=3, help="box size")
    args = parser.parse_args()

    with open(args.outfile, 'w') as f:
        puzzle = sg.random_puzzle(args.fixed, args.boxsize)
        f.write(sg._dict_to_string(puzzle.fixed, args.boxsize, 1, '\n'))


if __name__ == '__main__':
    main()
