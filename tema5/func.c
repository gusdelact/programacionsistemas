

void f1(void) {
	printf("f1 ");
}

void f2(void) {
	printf("f2 ");
}

void general( void (*p) () ) {
	p();
}
main() {
general(f1);
general(f2);
}
