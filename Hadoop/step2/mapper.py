#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def main():
    for line in sys.stdin:
        line = line.strip()
        data = line.split("\t")
        
        src_page = data[0].strip()
        page_rank = float(data[1].strip())
        del data[0]
        del data[0]
        page_count = len(data)

        print "%s\t%f" % (src_page, page_rank)
        for out_link in data:
            if out_link.strip() != "":
                print "%s\t%s\t%f\t%i" % (out_link.strip(), src_page, page_rank, page_count)

if __name__ == "__main__":
    main()
