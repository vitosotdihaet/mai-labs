#! /usr/bin/bash

set -e

print_usage() {
    echo -e "Usage:"
    echo -e "REQUIRED ARGUMENTS:\n"
    echo -e "\t-f, --file [FILE_PATH]\t\t path to a file that needs to be copied\n"
    echo -e "OPTIONAL ARGUMENTS:\n"
    echo -e "\t-l, --first_char '[CHAR]'\t\t from which character, file prefixes start"
    echo -e "\t-c, --copy_count [COPY_COUNT]\t how many times file should be copied"
    echo -e "\t-v, --verbose\t\t\t verbosely make copies of a file\n"
}

bail() {
    echo -e "$1\n"
    print_usage
    exit 1
}

# default parameters
file=""
char='a'
copy_count=1
verbose=false

while [[ $# -gt 0 ]]; do # handle flags
    case $1 in
        -f|--file)
            file=$2

            if [ ${#file} -eq 0 ]; then
                bail "Empty filename!"
            elif [ ${file:0:1} = - ]; then
                bail "Invalid filename!"
            fi

            shift
            shift ;;
        -c|--copy_count) 
            copy_count=$2

            if [ ${#copy_count} -eq 0 ]; then
                bail "Copy count is not present"
            elif [ $copy_count -eq 0 ]; then
                bail "Why would you want to copy your file zero times?"
            fi

            shift
            shift ;;
        -l|--first_char)
            char=$2

            if [ ${#char} -eq 0 ]; then
                bail "Empty initial character"
            fi

            shift
            shift ;;
        -v|--verbose)
            shift
            verbose=true ;;
        *)
            bail "Info:" ;;
    esac
done

if [ ${#file} -eq 0 ]; then
    bail "You need to input file that needs to be copied!"
fi


echo "Start copying..."

char=${char::1}
asciicode=$(printf "%d" "'$char'")
let asciicode--

char=$(printf "\x$(printf %x $asciicode)")


for (( i=0; $i<$copy_count; ++i ))
do
    asciicode=$(printf "%d" "'$char'")
    let asciicode++

    newchar=$(printf "\x$(printf %x $asciicode)")
    char=$newchar

    last_dot_index=${#file}
    for (( j=0; $j<${#file}; ++j )); do
        if [ "${file:$j:1}" = "." ]; then
            last_dot_index=$j
        fi
    done
    extension_length=$(( ${#file} - $last_dot_index ))

    filename=${file:0:$last_dot_index}$char
    extension=${file:$last_dot_index:$extension_length}

    new_file=$filename$extension

    if [ $verbose = true ]; then
        echo "$i: copying $file to $new_file..."
    fi

    eval "cp \$file \$new_file"
done

echo "Done!"