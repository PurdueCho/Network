all: prog2 prog2_arq prog2_gbn

prog2: prog2.c prog2.h
	gcc -Wall -Wextra -g prog2.c -o prog2

prog2_arq: prog2_arq.c prog2.h
	gcc -Wall -Wextra -g prog2_arq.c -o prog2_arq

prog2_gbn: prog2_gbn.c prog2.h
	gcc -Wall -Wextra -g prog2_gbn.c -o prog2_gbn

clean:
	rm -f prog2 *~ *.swp
	rm -f prog2_arq *~ *.swp
	rm -f prog2_gbn *~ *.swp
