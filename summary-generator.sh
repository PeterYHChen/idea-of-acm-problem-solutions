> SUMMARY.md
touch SUMMARY.md

fileNotParse=("solution.cpp" "test.in")
fileIgnore=("README.md")

generateMenu(){
    local dir=$1
    local depth=$2
    local indent=""

    for ((i=1; i<=4*depth; i++)); do
        indent=" $indent"
    done

    for file in "$dir"/*; do
        filename=`basename $file`

        if [[ -d "$file" ]]; then
            > "$file/README.md"
            touch "$file"/README.md
            echo "$indent* [$filename]($file/README.md)" >> SUMMARY.md
            generateMenu $file "1+$depth"

        elif [[ -f "$file" ]]; then
            if [[ "${fileIgnore[@]}" =~ $filename ]]; then # files to be ignored.
                continue

            elif [[ "${fileNotParse[@]}" =~ $filename ]]; then # handle not parsed files, usually source code
                filedir=$(dirname "$file")
                # cat all files under same directory
                # indent the content as code block in markdown syntax
                value=`cat $file`
                # value=`cat $file | sed 's/^/    /'`
                echo "## $filename" >> "$filedir/README.md"
                echo "\`\`\`cpp" >> "$filedir/README.md"
                echo "$value" >> "$filedir/README.md"
                echo "\`\`\`" >> "$filedir/README.md"
                continue

            else # other markdown files
                echo "$indent* [$filename]($file)" >> SUMMARY.md
            fi
        fi
    done
}

generateMenu $1 "0"
