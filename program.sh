
file=$1
t=$(mktemp)
cat "$file">$t

#compile 
rm main
g++ to64.cpp -o main
./main "$(cat $t)"
