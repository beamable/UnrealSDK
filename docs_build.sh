#!/bin/sh

pip install mkdocs-material
pip install mkdocs-glightbox

argument=${1:-"nothing"}
if [ $argument = "serve" ]; then
    cd Docs
    mkdocs serve
fi