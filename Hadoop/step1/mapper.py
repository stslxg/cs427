#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import sys

MinGanCi = ["cf."]
MinGanCi2 = [":image", "image", "wiktionary", "simple", "wikipedia", "wikibooks", "wp", "wikispecies", "user", "wikt", "special", "user talk"]
MinGanCi3 = ["category", ":category"]

text = ""
href_first = 0
href_last = 0

def get_next_href():
    global href_first, href_last

    href_first = text.find("[[", href_last)
    while href_first != -1:
        href_last = text.find("]]", href_first)
        semico = text.find(":", href_first + len("[[") + 1, href_last)
        if semico != -1:
            tmp = text[href_first + len("[[") : semico]
            if tmp.lower() in MinGanCi3: # for category
                href_first = semico - len("[[") + 1
            elif tmp.lower() in MinGanCi2 \
            or (len(tmp) <= 3 or tmp.find("-") != -1) and tmp.islower():
            # For WikiMedia or other language versions
                href_first = text.find("[[", href_first + len("[["))
            else:
                return
        else:
            return

def main():
    global text, href_first, href_last

    for line in sys.stdin:
        line = line.strip()
        
        # get title
        title_first = line.find("&lttitle&gt")
        title_last = line.find("&lt/title&gt")
        title = line[(title_first + len("&lttitle&gt")) : title_last]
        print title, "\t1.0",

        # get text
        text_first_0 = line.find("&lttext")
        text_first_1 = line.find("&gt", text_first_0) + len("&gt")
        text_last = line.find("&lt/text&gt")
        text = line[text_first_1 : text_last]
        
        # get href
        href_last = 0
        get_next_href()
        while href_first != -1:
            href = text[(href_first + len("[[")) : href_last]
            if href != title and not (href in MinGanCi):
                for link in href.split("|"):
                    print "\t%s" % link,

            get_next_href()
        
        print

if __name__ == "__main__":
    main()
