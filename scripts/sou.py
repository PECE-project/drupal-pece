#!/bin/env python
import sys
from bs4 import BeautifulSoup
with open(sys.argv[1]) as fp:
    soup = BeautifulSoup(fp, "lxml")
    print(soup.find(id="block-system-main").prettify())
