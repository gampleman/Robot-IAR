UNAME := $(shell uname -s)
DEBUG_ARG := -D SHOULD_DEBUG_$(DEBUG)
default:
	mkdir -p bin
ifeq ($(UNAME),Linux)
	g++ src/Main.c -o bin/main -lphidget21 -lpowerbutton $(DEBUG_ARG)
endif
ifeq ($(UNAME),Darwin)
	g++ src/Main.c -o bin/main -framework Phidget21 -I /Library/Frameworks/Phidget21.framework/Headers -D NO_POWERLIB $(DEBUG_ARG)
endif

report:
	cat reports/1.md > reports/tmp1.md
	ruby -e "File.open('reports/tmp1.md', 'a') { |file| \
		file.puts '## Code listing'; \
		Dir['src/*.c'].each{|f| \
			file.puts ''; \
			file.puts '### ' + f; \
			File.readlines(f).each {|l| file.puts '    ' + l } \
		} \
	}"
ifeq ($(UNAME),Darwin)
	redcarpet reports/tmp1.md > reports/report1.html
	rm reports/tmp1.md
endif

