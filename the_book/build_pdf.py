#!/usr/bin/env python3
import os
import subprocess
import markdown

BOOK_DIR = "/home/zx/projects/6ls/the_book"
TREATISE_MD = os.path.join(BOOK_DIR, "THE_LORS_COMPILER_COMPLETE_TREATISE.md")
HTML_OUTPUT = os.path.join(BOOK_DIR, "the_book.html")
PDF_OUTPUT = os.path.join(BOOK_DIR, "The_Lors_Compiler_Architecture_Book.pdf")

# Custom CSS for book rendering
CSS = """
@page {
    size: A4;
    margin: 20mm 20mm 20mm 20mm;
}

body {
    font-family: 'Helvetica Neue', Arial, sans-serif;
    line-height: 1.6;
    color: #1a1a1a;
    font-size: 11pt;
    margin: 0;
    padding: 0;
}

.cover-page {
    page-break-after: always;
    text-align: center;
    padding-top: 150px;
    height: 80vh;
}

.cover-title {
    font-size: 32pt;
    font-weight: 800;
    color: #0f172a;
    margin-bottom: 20px;
    line-height: 1.2;
}

.cover-subtitle {
    font-size: 16pt;
    color: #475569;
    margin-bottom: 40px;
    font-weight: 300;
}

.cover-meta {
    font-size: 12pt;
    color: #64748b;
    margin-top: 100px;
}

.divider {
    width: 100px;
    height: 4px;
    background-color: #2563eb;
    margin: 30px auto;
}

h1 {
    font-size: 20pt;
    color: #0f172a;
    border-bottom: 2px solid #2563eb;
    padding-bottom: 8px;
    margin-top: 40px;
    page-break-before: always;
}

h1:first-of-type {
    page-break-before: avoid;
}

h2 {
    font-size: 15pt;
    color: #1e293b;
    border-bottom: 1px solid #cbd5e1;
    padding-bottom: 4px;
    margin-top: 30px;
}

h3 {
    font-size: 12pt;
    color: #334155;
    margin-top: 20px;
}

p, ul, ol {
    margin-bottom: 12px;
}

code {
    font-family: 'Consolas', 'Courier New', monospace;
    font-size: 9.5pt;
    background-color: #f1f5f9;
    padding: 2px 5px;
    border-radius: 3px;
    border: 1px solid #e2e8f0;
}

pre {
    background-color: #0f172a;
    color: #f8fafc;
    padding: 14px;
    border-radius: 6px;
    overflow-x: auto;
    font-size: 9pt;
    line-height: 1.45;
    margin: 15px 0;
    page-break-inside: avoid;
}

pre code {
    background: transparent;
    color: inherit;
    padding: 0;
    border: none;
    font-family: 'Consolas', 'Courier New', monospace;
}

table {
    width: 100%;
    border-collapse: collapse;
    margin: 20px 0;
    font-size: 9.5pt;
    page-break-inside: avoid;
}

th, td {
    padding: 8px 12px;
    text-align: left;
    border: 1px solid #cbd5e1;
}

th {
    background-color: #f1f5f9;
    color: #0f172a;
    font-weight: 700;
}

tr:nth-child(even) {
    background-color: #f8fafc;
}

blockquote {
    border-left: 4px solid #2563eb;
    margin: 15px 0;
    padding: 10px 15px;
    background-color: #f8fafc;
    color: #334155;
    font-style: italic;
}

hr {
    border: 0;
    height: 1px;
    background: #e2e8f0;
    margin: 30px 0;
}
"""

def generate_html():
    with open(TREATISE_MD, 'r', encoding='utf-8') as f:
        md_text = f.read()

    html_body = markdown.markdown(
        md_text,
        extensions=['tables', 'fenced_code', 'toc', 'sane_lists']
    )

    full_html = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>The Lors Compiler Architecture Book (Stage 6)</title>
    <style>
{CSS}
    </style>
</head>
<body>
    <div class="cover-page">
        <div class="cover-title">THE LORS COMPILER<br>ARCHITECTURE & SELF-HOSTING</div>
        <div class="divider"></div>
        <div class="cover-subtitle">Stage 6 LLVM Modular Compiler Specification and Engineering Handbook</div>
        <div class="cover-meta">
            <p><strong>Stage:</strong> Stage 6 (v6-dv)</p>
            <p><strong>Architecture:</strong> Modular Multi-Object LLVM Native Backend</p>
            <p><strong>Status:</strong> Autonomous Self-Hosting (Fixed-Point Point of Inflection Achieved)</p>
            <p><strong>Test Coverage:</strong> 100% (124+ Automated Test Programs)</p>
        </div>
    </div>

    {html_body}
</body>
</html>
"""
    with open(HTML_OUTPUT, 'w', encoding='utf-8') as f:
        f.write(full_html)
    print(f"Generated HTML at {HTML_OUTPUT}")

def generate_pdf():
    cmd = [
        "google-chrome",
        "--headless",
        "--disable-gpu",
        "--no-sandbox",
        "--no-pdf-header-footer",
        f"--print-to-pdf={PDF_OUTPUT}",
        HTML_OUTPUT
    ]
    print(f"Running command: {' '.join(cmd)}")
    subprocess.run(cmd, check=True)
    print(f"SUCCESS: Generated PDF at {PDF_OUTPUT}")

if __name__ == "__main__":
    generate_html()
    generate_pdf()
