html: docs/_build/html

docs/_build:
	mkdir docs/_build

docs/_build/breathe:
	git clone git://github.com/michaeljones/breathe.git docs/_build/breathe
	$(RM) -r docs/_build/breathe/examples  \
		 docs/_build/breathe/testsuite \
		 docs/_build/breathe/README.rst

docs/_build/doxy: docs/_build MMA8452Q.h
	doxygen docs/doxygen.conf

docs/_build/html: docs/_build/doxy docs/_build/breathe docs/*.rst
	sphinx-build -b html docs/ docs/_build/html

pages: html
	git checkout gh-pages
	rsync -r docs/_build/html/* .
	rm -rf docs/*
	git add .
	git commit -m "build docs"
	git checkout master

clean:
	$(RM) -r docs/_build
