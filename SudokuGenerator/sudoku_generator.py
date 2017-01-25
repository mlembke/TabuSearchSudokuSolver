#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# Based on:
# Sean Davis, Matthew Henderson, Andrew Smith (Berea) 4.1.2010
# https://conference.scipy.org/scipy2010/slides/matthew_henderson_sudoku.pdf

import copy
import itertools
import operator
import random
import string

import constraint


#
# Basic parameters
#

def n_rows(boxsize):
    return boxsize ** 2


def n_cols(boxsize):
    return boxsize ** 2


def n_boxes(boxsize):
    return boxsize ** 2


def n_symbols(boxsize):
    return max(n_rows(boxsize), n_cols(boxsize))


def n_cells(boxsize):
    return n_rows(boxsize) * n_cols(boxsize)


#
# Cell label functions
#

def get_cell(row, column, boxsize):
    return (row - 1) * n_rows(boxsize) + column


def get_column(cell, boxsize):
    return (cell - 1) % n_rows(boxsize) + 1


def get_row(cell, boxsize):
    return (cell - 1) // n_cols(boxsize) + 1


def box_representative(box, boxsize):
    i = boxsize * ((box - 1) // boxsize)
    j = boxsize * ((box - 1) % boxsize) + 1
    return boxsize ** 2 * i + j


#
# Convenient ranges
#

def cells(boxsize):
    return range(1, n_cells(boxsize) + 1)


def symbols(boxsize):
    return range(1, n_symbols(boxsize) + 1)


def rows(boxsize):
    return range(1, n_rows(boxsize) + 1)


def cols(boxsize):
    return range(1, n_cols(boxsize) + 1)


def boxes(boxsize):
    return range(1, n_boxes(boxsize) + 1)


def row_r(row, boxsize):
    """Cell labels in 'row' of Sudoku puzzle of dimension 'boxsize'."""
    nr = n_rows(boxsize)
    return range(nr * (row - 1) + 1, nr * row + 1)


def col_r(column, boxsize):
    """Cell labels in 'column' of Sudoku puzzle of dimension 'boxsize'."""
    nc = n_cols(boxsize)
    ncl = n_cells(boxsize)
    return range(column, ncl + 1 - (nc - column), nc)


def box_r(box, boxsize):
    """Cell labels in 'box' of Sudoku puzzle of dimension 'boxsize'."""
    return [box_representative(box, boxsize) + j + k - 1 for j in range(0, boxsize * n_rows(boxsize), n_cols(boxsize))
            for k in range(1, boxsize + 1)]


def cells_by_row(boxsize):
    """cells_by_row(boxsize) -> list

    Returns a list of cell labels ordered by row for the given boxsize."""
    return [row_r(row, boxsize) for row in rows(boxsize)]


def cells_by_col(boxsize):
    """cells_by_col(boxsize) -> list

    Returns a list of cell labels ordered by column for the given boxsize."""
    return [col_r(column, boxsize) for column in cols(boxsize)]


def cells_by_box(boxsize):
    """cells_by_box(boxsize) -> list

    Returns a list of cell labels ordered by box for the given boxsize."""
    return [box_r(box, boxsize) for box in boxes(boxsize)]


def puzzle_rows(puzzle, boxsize):
    """Cell values, ordered by row."""
    return [map(puzzle.get, row_r(row, boxsize)) for row in rows(boxsize)]


def puzzle_columns(puzzle, boxsize):
    """Cell values, ordered by column."""
    return [map(puzzle.get, col_r(column, boxsize)) for column in cols(boxsize)]


def puzzle_boxes(puzzle, boxsize):
    """Cell values, ordered by box."""
    return [map(puzzle.get, box_r(box, boxsize)) for box in boxes(boxsize)]


#
# Convenient functions
#

def ordered_pairs(r):
    """All ordered pairs from objects in range 'r'."""
    return itertools.combinations(r, 2)


def are_all_different(l):
    """Test whether all elements in range 'l' are different."""
    return all(itertools.starmap(operator.ne, ordered_pairs(l)))


def are_all_different_nested(l):
    """Test whether every range in range 'l' is a range of all different
    elements."""
    return all(map(are_all_different, l))


def strip_ws(puzzle_string):
    """Remove newline and space characters from a string."""
    return puzzle_string.replace('\n', '').replace(' ', '')


def int_to_printable(i):
    """Convert an integer to a printable character."""
    return string.printable[i]


def printable_to_int(c):
    """Convert a printable character to a integer."""
    return string.printable.index(c)


#
# String/dictionary conversions
#

def _dict_to_string(fixed, boxsize, padding=0, rowend="", row_sep="", box_sep="", col_sep="", last_row_hack=""):
    """Returns a puzzle string of dimension 'boxsize' from a dictionary of
    'fixed' cells."""
    s = ''
    s += row_sep
    for row in rows(boxsize):
        s += box_sep
        for col in cols(boxsize):
            symbol = fixed.get(get_cell(row, col, boxsize))
            if symbol:
                s += int_to_printable(symbol) + " " * padding
            else:
                s += '.' + ' ' * padding
            if col % boxsize == 0:
                s += box_sep
            if col < boxsize * boxsize:
                s += col_sep
        s += rowend
        if row % boxsize == 0 and row < boxsize * boxsize:
            s += row_sep
        elif row == boxsize * boxsize:
            s += last_row_hack
    s += row_sep
    return s


def dict_to_string(fixed, boxsize, padding=0, rowend=""):
    """Returns a puzzle string of dimension 'boxsize' from a dictionary of
    'fixed' cells with some suitably chosen row/column seperators."""
    row_sep = boxsize * ('+' + (2 * boxsize + 1) * '-') + '+' + '\n'
    box_sep = '| '
    return _dict_to_string(fixed, boxsize, padding, rowend, row_sep, box_sep, "")


def string_to_dict(puzzle, boxsize):
    """Returns a dictionary based on a Sudoku puzzle string."""
    puzzle = strip_ws(puzzle)
    d = {}
    for cell in cells(boxsize):
        if puzzle[cell - 1] != '.':
            d[cell] = int(printable_to_int(puzzle[cell - 1]))
    return d


#
# Constraint models
#

def add_row_constraints(problem, boxsize):
    """add_row_constraints(problem, boxsize)

    Adds to constraint problem 'problem', all_different constraints on rows."""
    for row in cells_by_row(boxsize):
        problem.addConstraint(constraint.AllDifferentConstraint(), row)


def add_col_constraints(problem, boxsize):
    """add_col_constraints(problem, boxsize)

    Adds to constraint problem 'problem', all_different constraints on columns."""
    for col in cells_by_col(boxsize):
        problem.addConstraint(constraint.AllDifferentConstraint(), col)


def add_box_constraints(problem, boxsize):
    """add_box_constraints(problem, boxsize)

    Adds to constraint problem 'problem', all_different constraints on boxes."""
    for box in cells_by_box(boxsize):
        problem.addConstraint(constraint.AllDifferentConstraint(), box)


def empty_puzzle_as_cp(boxsize):
    """empty_puzzle(boxsize) -> constraint.Problem

    Returns a constraint problem representing an empty Sudoku puzzle of
    box-dimension 'boxsize'."""
    p = constraint.Problem()
    p.addVariables(cells(boxsize), symbols(boxsize))
    add_row_constraints(p, boxsize)
    add_col_constraints(p, boxsize)
    add_box_constraints(p, boxsize)
    return p


def puzzle_as_cp(fixed, boxsize):
    """puzzle_as_CP(fixed, boxsize) -> constraint.Problem

    Returns a constraint problem representing a Sudoku puzzle, based on
    'fixed' cell dictionary."""
    p = empty_puzzle_as_cp(boxsize)
    for cell in fixed:
        p.addConstraint(constraint.ExactSumConstraint(fixed[cell]), [cell])
    return p


#
# Puzzle solving
#
def solve_as_cp(fixed, boxsize):
    """Use constraint programming to solve Sudoku puzzle of dimension 'boxsize'
    with 'fixed' cells."""
    return puzzle_as_cp(fixed, boxsize).getSolution()


def solve_puzzles(puzzles, boxsize):
    """Solve every puzzle in iterable 'puzzles'."""
    return [solve_as_cp(puzzle, boxsize) for puzzle in puzzles]


def solve_puzzles_s(puzzles_s, boxsize):
    """Solve every puzzle string in iterable 'puzzles'."""
    return solve_puzzles(map(lambda puzzle: string_to_dict(puzzle, boxsize), puzzles_s), boxsize)


#
# Puzzle generating
#

def random_puzzle(n_fixed, boxsize):
    return Puzzle(random_fixed(n_fixed, boxsize), boxsize)


def random_fixed(n_fixed, boxsize):
    """Random puzzle generator, based on solution of empty puzzle."""
    s = solve_as_cp({random.randint(1, n_cells(boxsize)): random.randint(1, n_symbols(boxsize))}, boxsize)
    return random_filter(s, n_fixed)


def random_filter(puzzle_d, n_fixed):
    """A puzzle dictionary of a random Sudoku puzzle of 'fixed' size
    based on the Sudoku 'puzzle' dictionary."""
    fixed = copy.deepcopy(puzzle_d)
    keys = list(fixed.keys())
    random.shuffle(keys)
    indices = keys[:len(keys) - n_fixed]
    for i in indices:
        del fixed[i]
    return fixed


#
# Verification
#

def is_row_latin(puzzle, boxsize):
    """Test latin-ness of 'puzzle' rows."""
    return are_all_different_nested(puzzle_rows(puzzle, boxsize))


def is_column_latin(puzzle, boxsize):
    """Test latin-ness of 'puzzle' columns."""
    return are_all_different_nested(puzzle_columns(puzzle, boxsize))


def is_box_latin(puzzle, boxsize):
    """Test latin-ness of 'puzzle' boxes."""
    return are_all_different_nested(puzzle_boxes(puzzle, boxsize))


def is_sudoku(puzzle, boxsize):
    """Test whether 'puzzle' is a Sudoku puzzle of dimension 'boxsize'."""
    return is_row_latin(puzzle, boxsize) and is_column_latin(puzzle, boxsize) and is_box_latin(puzzle, boxsize)


def is_solution(fixed, puzzle):
    """Test whether 'fixed' cells have same values in 'puzzle'."""
    return all(map(lambda x: fixed[x] == puzzle[x], fixed))


def is_sudoku_solution_d(fixed, puzzle, boxsize):
    """Test whether 'puzzle' is a solution of 'fixed'."""
    return is_sudoku(puzzle, boxsize) and is_solution(fixed, puzzle)


def is_sudoku_solution_s(fixed_s, puzzle_s, boxsize):
    """Test whether 'puzzle_s' string is a solution of 'fixed_s' string."""
    fixed = string_to_dict(fixed_s, boxsize)
    puzzle = string_to_dict(puzzle_s, boxsize)
    return is_sudoku_solution_d(fixed, puzzle, boxsize)


def verify_solutions(puzzles, solutions, boxsize, verify_solution=is_sudoku_solution_d):
    """Test whether the iterable 'puzzles' has a solution in the
    corresponding position of iterable 'solutions'."""
    return all(map(lambda puzzle, solution: verify_solution(puzzle, solution, boxsize), puzzles, solutions))


#
# Puzzle
#
class Cell:
    def __init__(self, value, fixed=False):
        self.__value = value
        self.__fixed = fixed

    def __repr__(self):
        return self.__value

    def __str__(self):
        return str(self.__repr__())

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, value):
        self.__value = value

    def is_fixed(self):
        return self.__fixed


class Puzzle:
    def __init__(self, fixed, boxsize, repr_format='d'):
        self.boxsize = boxsize
        if repr_format == 'd':
            self.fixed = fixed
        elif repr_format == 's':
            self.fixed = string_to_dict(fixed, boxsize)
        else:
            raise NameError('No such format: ' + repr_format)

    def __repr__(self):
        return dict_to_string(self.fixed, self.boxsize, padding=1, rowend="\n")

    def _repr_latex_(self):
        s = r"""$$\begin{array}"""
        s += '{' + self.boxsize * ('|' + self.boxsize * 'c') + '|' + '}'
        s += _dict_to_string(self.fixed, self.boxsize, padding=0, rowend="\\\\ \n", row_sep="\hline ", box_sep="",
                             col_sep=" & ", last_row_hack="\hline")
        s += r"""\end{array}$$"""
        return s

    def __str__(self):
        return self.__repr__()

    def get_boxsize(self):
        return self.boxsize

    def get_fixed(self):
        return self.fixed


if __name__ == '__main__':
    print('This file is a module and cannot be run independently!')
