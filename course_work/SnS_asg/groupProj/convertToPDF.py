import nbformat
from nbconvert import PDFExporter

# Read the notebook file
with open('./ch6.ipynb', 'r', encoding='utf-8') as f:
    nb = nbformat.read(f, 4)

# Modify the notebook metadata
nb.metadata['title'] = "Chapter 6 Group Assignment"

exporter = PDFExporter()
exporter.exclude_input_prompt = True
exporter.exclude_output_prompt = True

(body, resources) = exporter.from_notebook_node(nb)

with open('ch6_2.pdf', 'wb') as f:
    f.write(body)