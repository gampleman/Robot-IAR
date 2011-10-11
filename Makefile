UNAME := $(shell uname -s)
default:
	mkdir -p bin
ifeq ($(UNAME),Linux)
	g++ src/Main.c -o bin/main -lphidget21 -lpowerbutton
endif
ifeq ($(UNAME),Darwin)
	echo "#define NO_POWERLIB 1"|cat - src/Main.c > src/CompileMain.c
	g++ src/CompileMain.c -o bin/main -framework Phidget21 -I /Library/Frameworks/Phidget21.framework/Headers
	rm src/CompileMain.c
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