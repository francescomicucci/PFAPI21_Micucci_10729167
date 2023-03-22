.PHONY: all
all: main

main: main.c
	gcc -Wall -Werror -O2 -g3 main.c -o main

test_gen: ../script/suitegen.py ../script/suitegen.py
	python ../script/suitegen.py ..

test: main.c ../script/suitegen.py ../script/suitegen.py
	make test_gen
	rm ../script/__pycache__/ -R -f
	mkdir ../output/
	mkdir ../output/open
	mkdir ../output/private
	make main
	./main < ../input/open/input.1 > ../output/open/output.1
	./main < ../input/open/input.2 > ../output/open/output.2
	./main < ../input/open/input.3 > ../output/open/output.3
	./main < ../input/open/input.4 > ../output/open/output.4
	./main < ../input/open/input.5 > ../output/open/output.5
	./main < ../input/open/input.6 > ../output/open/output.6
	./main < ../input/private/input.1 > ../output/private/output.1
	./main < ../input/private/input.2 > ../output/private/output.2
	./main < ../input/private/input.3 > ../output/private/output.3
	./main < ../input/private/input.4 > ../output/private/output.4
	./main < ../input/private/input.5 > ../output/private/output.5
	./main < ../input/private/input.6 > ../output/private/output.6
	rm -f main
	
.PHONY: clear
clear:
	rm -f main

clear_test:
	rm ../input -R -f
	rm ../output -R -f