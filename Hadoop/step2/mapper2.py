#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def main():
    for line in sys.stdin:
        line = line.strip()
        data = line.split("\t")
        
        dest_page = data[0].strip()
        page_rank = float(data[1].strip())
        del data[0]
        del data[0]

        print "%s\t%f\t%f" % (dest_page, page_rank, page_rank)
        for in_link in data:
            print "%s\t%s" % (in_link.strip(), dest_page)

if __name__ == "__main__":
    main()
