#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def main():
    for line in sys.stdin:
        line = line.strip()
        data = line.split("\t")
        
        src_page = data[0].strip()
        page_rank = 1000000.0 - float(data[1].strip())

        print "%020.12f\t%s" % (page_rank, src_page)

if __name__ == "__main__":
    main()
