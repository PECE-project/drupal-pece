#!/bin/env python
from bs4 import BeautifulSoup
import sys
# based on https://www.geeksforgeeks.org/python-beautifulsoup-find-all-class/
class_list = set()

with open(sys.argv[1]) as fp:
    soup = BeautifulSoup(fp, "lxml")
    tags = {tag.name for tag in soup.find_all()}
    for tag in tags:
        for i in soup.find_all( tag ):
            if i.has_attr( "class" ):
                if len( i['class'] ) != 0:
                    for c in i['class']:
                        class_list.add(c)

for x in class_list:
  print(x)
