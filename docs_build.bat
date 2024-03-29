pip install mkdocs-material
pip install mkdocs-glightbox
IF "%1"=="serve" ( 
    cd Docs
    mkdocs serve
 )