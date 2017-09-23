par-lab.pdf: book.tex
	pdflatex book.tex
	pdflatex book.tex
	mv book.pdf par-lab.pdf
	rm -f book*

book.tex: paralel.md
	pandoc -s paralel.md -o book.tex
	sed -i 's/{book}/{tufte-book}/' book.tex
	sed -i 's/Praktikum Pemrosesan Paralel/Praktikum\\\\Pemrosesan\\\\Paralel/' book.tex
	sed -i 's/\\newpage//' book.tex
	sed -i '/\\begin{document}/a \
	\\frontmatter\\pagenumbering{roman}' book.tex
	sed -i '/\\listoffigures/a \
	\\mainmatter\\setcounter{page}{1}\\pagenumbering{arabic}' book.tex

clean:
	rm -f par-lab.pdf
