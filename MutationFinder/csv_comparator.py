#!/usr/bin/env python

import os, sys, argparse, csv

#*******************************************************************************

def parse_csv_file(path):
    s = set()
    with open(path, "r") as csv_file:
        csv_reader = csv.reader(csv_file)
        for row in csv_reader:
           s.add(tuple(row))
    return s

def jaccard_index(a, b):
    intersection = a.intersection(b)
    return len(intersection) / float(len(a) + len(b) - len(intersection))


#*******************************************************************************

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='''Calculates the Jaccard score
        between two files in CSV format by treating each line of a file as an
        element of the corresponding set.''',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    required_arguments = parser.add_argument_group('required arguments')
    required_arguments.add_argument('-a', help='''File containing set A in CSV
        format''', required=True)
    required_arguments.add_argument('-b', help='''File containing set B in CSV
        format''', required=True)

    args = parser.parse_args()

    a = parse_csv_file(args.a)
    b = parse_csv_file(args.b)

    print("Jaccard_sim = " + str(jaccard_index(a, b)))
    print("")


    file1 = open(args.a, "r")
    file2 = open(args.b, "r")

    lines1 = file1.readlines()
    lines2 = file2.readlines()

    dict1 = {}
    dict2 = {}
    positions = []

    for line in lines1:
        position = int(line.split(",")[1])
        dict1[position] = line.strip()
        positions.append(position)

    for line in lines2:
        position = int(line.split(",")[1])
        dict2[position] = line.strip()
        if not (position in positions):
            positions.append(position)

    positions.sort()

    for position in positions:
        if (position in dict1) and (position in dict2):
            print(dict1[position])
        elif (position in dict1):
            print(dict1[position] + "   \t- FN")
        elif (position in dict2):
            print(dict2[position] + "   \t+ FP")