#! /usr/bin/bash

file=''

char='a'
copy_count=1
verbose=false

print_usage() {
    printf "Invalid input!\n"
    printf "Usage:\n"
    printf "REQUIRED ARGUMENTS:\n"
    printf "\t-f, --file [FILE_PATH]\t\t path to a file that needs to be copied\n"
    printf "OPTIONAL ARGUMENTS:\n"
    printf "\t-l, --first_char '[CHAR]'\t\t from which character, file prefixes start\n"
    printf "\t-c, --copy_count [COPY_COUNT]\t how many times file should be copied\n"
    printf "\t-v, --verbose\t\t\t verbosely make copies of a file\n"
}

while [[ $# -gt 0 ]]; do
    case $1 in
        -f|--file)
            file=$2
            shift
            shift ;;
        -c|--copy_count) 
            copy_count=$2 
            shift
            shift ;;
        -v|--verbose)
            shift
            verbose=true ;;
        -l|--first_char)
            char=$2
            shift
            shift ;;
        *)
            print_usage
            exit 1 ;;
    esac
done

char=${char::1}

for (( i=0; $i<$copy_count; ++i ))
do
    asciicode=$(printf "%d" "'$char'")
    let asciicode++

    newchar=$(printf "\x$(printf %x $asciicode)")
    char=$newchar

    new_file=$file

    if [ $verbose = true ]; then
        echo "$i: copying $file to $new_file..."
    fi
done