#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def main():
    out_links = []
    page_rank = 0.0

    prev_key = False
    for line in sys.stdin:
        line = line.strip()
        data = line.split("\t")
        
        cur_key = data[0].strip()
        
        # found a new key
        if prev_key and cur_key != prev_key:
            print "%s\t%f" % (prev_key, page_rank),
            for out_link in out_links:
                print "\t%s" % out_link,
            print

            out_links = []
            page_rank = 0.0
        
        # update
        # get page rank
        if len(data) == 3:
            page_rank = float(data[1].strip())
        # get out link
        else:
            out_links.append(data[1].strip())

        prev_key = cur_key
        
    if prev_key:
        print "%s\t%f" % (prev_key, page_rank),
        for out_link in out_links:
            print "\t%s" % out_link,
        print

if __name__ == "__main__":
    main()
