import os
from os import listdir
from os.path import isfile, join
path = '/root/.pece/automations/enabled/'
onlyfiles = [f for f in listdir(path) if isfile(join(path, f))]
for automation in onlyfiles:
  os.system('n8n execute --file=' + path + automation)

