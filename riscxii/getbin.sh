cat $1 | xxd -e | xxd -r | xxd -b -g4 -c4 | head -n 9