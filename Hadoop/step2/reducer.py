#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

def get_line():
    for line in sys.stdin:
        yield line

def main(c = 0.3):
    new_sum = 0
    in_links = []
    old_page_rank = 0.0

    prev_key = False
    for line in get_line():
        line = line.strip()
        data = line.split("\t")
        
        cur_key = data[0].strip()
        
        # found a new key
        if prev_key and cur_key != prev_key:
            new_page_rank = (1 - c) * old_page_rank + c * new_sum
            print "%s\t%f" % (prev_key, new_page_rank),
            for in_link in in_links:
                print "\t%s" % in_link,
            print

            new_sum = 0
            in_links = []
            old_page_rank = 0.0
        
        # update
        # contains old_page_rank
        if len(data) == 2:
            old_page_rank = float(data[1].strip())
        # contains new information
        else:
            in_links.append(data[1].strip())
            new_sum += float(data[2].strip()) / int(data[3].strip())

        prev_key = cur_key
        
    if prev_key:
        new_page_rank = (1 - c) * old_page_rank + c * new_sum
        print "%s\t%f" % (prev_key, new_page_rank),
        for in_link in in_links:
            print "\t%s" % in_link,
        print

if __name__ == "__main__":
    main()
