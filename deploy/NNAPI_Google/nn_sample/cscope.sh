#!/bin/sh 
find . -name "*.*" > cscope.files 
cscope -bkq -i cscope.files 
ctags -R
