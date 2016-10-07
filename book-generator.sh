rm SUMMARY.md
touch SUMMARY.md

generateMenu(){
    local dir=$1
    local depth=$2
    local indent=""

    for ((i=1; i<=4*depth; i++)); do
        indent=" $indent"
    done

    for file in "$dir"/*; do
        filename=`basename $file`

        if [ -d "$file" ]; then
            touch "$file"/README.md
            echo "$indent* [$filename]($file/README.md)" >> SUMMARY.md
            generateMenu $file "1+$depth"
        elif [ -f "$file" ] && [ $filename != "README.md" ] && [ $filename != "solution.cpp" ]; then
            echo "$indent* [$filename]($file)" >> SUMMARY.md
        fi
    done
}

generateMenu $1 "0"
