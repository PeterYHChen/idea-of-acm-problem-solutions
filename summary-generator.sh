> SUMMARY.md
touch SUMMARY.md

#fileIgnore=("README.md" "solution.cpp" "test.in")
fileIgnore=("README.md" "test.in")

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
            if [[ "${fileIgnore[@]}" =~ $filename ]]; then
                continue
            fi
            #echo "$indent* [$filename]($file)" >> SUMMARY.md
            # cat all files under same directory
            local filedir=$(dirname "$file")
            local value=`cat $file`
            echo "{% raw %}" >> "$filedir/README.md"
            echo "$value" >> "$filedir/README.md"
            echo "{% endraw %}" >> "$filedir/README.md"
            sed -i 's/^/    /' "$filedir/README.md"
        fi
    done
}

generateMenu $1 "0"
