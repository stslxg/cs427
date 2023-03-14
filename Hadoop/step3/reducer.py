#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def main(c = 0.5):
    for line in sys.stdin:
        line = line.strip()
        data = line.split("\t")
        print "%s\t%f" % (data[1].strip(), 1000000.0 - float(data[0].strip()))

if __name__ == "__main__":
    main()
