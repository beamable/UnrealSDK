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

    if [ ! -d ".venv" ]; then
        python -m venv .venv
	activate_path=$(find .venv -type f -name "activate")
        source $activate_path
        python -m pip install mkdocs-material
        python -m pip install mkdocs-glightbox
        python -m pip install mkdocs-autorefs
    fi
    activate_path=$(find .venv -type f -name "activate")

    if [ -n "$activate_path" ]; then
        echo "Path to activate python venv: $activate_path"
        source $activate_path
    else
        echo "Activate file not found"
        exit 2
    fi


    argument=${1:-"nothing"}
    if [[ $argument == "serve" ]]; then
        cd Docs
        python -m mkdocs serve
    fi
}

# Call the main function with arguments
main "$@"
