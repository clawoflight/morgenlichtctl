man_MANS = morgenlichtctl.1

EXTRA_DIST = morgenlichtctl.1.md

clean:
	rm -f *.1 *.7

%.1: %.1.md
	pandoc -s -t man $< > $@

%.7: %.7.md
	pandoc -s -t man $< > $@
