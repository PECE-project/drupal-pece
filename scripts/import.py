#!/bin/env python
import mariadb
import os
import sys

directory = os.fsencode(sys.argv[1])

# Connect to MariaDB Platform
try:
    conn = mariadb.connect(
        user="db",
        password="db",
        host="127.0.0.1",
        port=int(os.environ['DB_PORT']),
        database=os.environ['DB_NAME']

    )
except mariadb.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
    sys.exit(1)

# Get Cursor
# conn.autocommit = True
cursor = conn.cursor()
try:
    cursor.execute("CREATE OR REPLACE TABLE `essay_content` (\
        `nodeid` int(11) NOT NULL,\
        `content` longtext NOT NULL)")
except mariadb.Error as e:
    print(f"Error creating table essay_content: {e}")
    sys.exit(1)
db_error = False
for file in os.listdir(directory):
    filename = os.fsdecode(file)
    if filename[0:6] != "essay-":
        print(f"Skipping non-essay file {file}")
        continue
    print(f"Attempting to import {file}")
    nodeid = os.path.splitext(filename)[0][6:]
    try:
        with open(os.path.join(directory, os.fsencode(filename)), "rt") as html:
            content = html.read()
        content_len = len(content)
        cursor.execute("INSERT INTO `essay_content` (nodeid, content) VALUES (?, ?)", (nodeid, content))
        print(f"NodeID {nodeid} is {content_len} bytes")
    except mariadb.Error as e:
        db_error: True
        conn.rollback()
        print(f"Error inserting into MariaDB for node {nodeid}: {e}")
        break
    except IOError:
        print(f"Could not read file {filename}")
    except e:
        print(f"Something else weird happened: {e}")

if not db_error: conn.commit()
conn.close()