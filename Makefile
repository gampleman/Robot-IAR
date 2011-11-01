UNAME := $(shell uname -s)
DEBUG_ARG := -D SHOULD_DEBUG_$(DEBUG)
default:
	mkdir -p bin
ifeq ($(UNAME),Linux)
	g++ src/Main.c -o bin/main -lphidget21 -lpowerbutton $(DEBUG_ARG) -D FREQUENCY=$(FREQUENCY) -D BATTERY=0.6 $(OPTS)
endif
ifeq ($(UNAME),Darwin)
	g++ src/Main.c -o bin/main -framework Phidget21 -I /Library/Frameworks/Phidget21.framework/Headers -D NO_POWERLIB $(DEBUG_ARG) -D FREQUENCY=$(FREQUENCY) $(OPTS)
endif

report:
	cat reports/2.md > reports/tmp2.md
	ruby -e "File.open('reports/tmp2.md', 'a') { |file| \
		file.puts '## Code listing'; \
		Dir['src/*.c'].each{|f| \
			file.puts ''; \
			file.puts '### ' + f; \
			File.readlines(f).each {|l| file.puts '    ' + l } \
		} \
	}"
ifeq ($(UNAME),Darwin)
	redcarpet reports/tmp2.md > reports/report1.html
	rm reports/tmp2.md
endif

copy_to_dodo:
	scp -r . student@Dodo:/home/student/MyPrograms

debug:
	uniq | bin/main
