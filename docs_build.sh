#!/bin/sh

main() {
    name_pattern='^[a-zA-Z0-9./-]+$'

    # Use 'find' to recursively list all files and directories
    find "Docs/docs/" -print0 | while IFS= read -r -d '' path; do
        name=$(basename "$path")

        # Check if the name contains only lowercase letters and hyphens
        if [[ ! "$name" =~ $name_pattern ]]; then
            echo "Invalid name: $path"
            exit 2
        fi
    done
    pip install mkdocs-material
    pip install mkdocs-glightbox
    pip install mkdocs-autorefs

    argument=${1:-"nothing"}
    if [ $argument = "serve" ]; then
        cd Docs
        mkdocs serve
    fi
}
main