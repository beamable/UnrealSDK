#!/bin/sh

pip install mkdocs-material
pip install mkdocs-glightbox
pip install mkdocs-autorefs

argument=${1:-"nothing"}
if [ $argument = "serve" ]; then
    cd Docs
    mkdocs serve
fi