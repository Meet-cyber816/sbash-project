#!/bin/bash

awk '{ print length, $0 }' black_commands.txt | sort -nr | uniq | cut -d' ' -f2- > /usr/local/bin/_sbash_restricted_commands.txt
