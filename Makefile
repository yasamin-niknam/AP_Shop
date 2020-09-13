a.out: main.o seller.o person.o goods.o factor.o request.o shoppingcenter.o
	g++ main.o seller.o person.o goods.o factor.o request.o shoppingcenter.o

main.o: seller.o person.o goods.o factor.o request.o shoppingcenter.o main.cpp
	g++ -c main.cpp -o main.o

shoppingcenter.o: shoppingcenter.cpp shoppingcenter.hpp seller.o person.o goods.o factor.o request.o
	g++ -c shoppingcenter.cpp -o shoppingcenter.o

seller.o: seller.cpp seller.hpp goods.o
	g++ -c seller.cpp -o seller.o

person.o: person.cpp person.hpp seller.o
	g++ -c person.cpp -o person.o

goods.o: goods.cpp goods.hpp
	g++ -c goods.cpp -o goods.o

factor.o: factor.cpp factor.hpp person.o seller.o goods.o
	g++ -c factor.cpp -o factor.o

request.o: request.cpp request.hpp
	g++ -c request.cpp -o request.o

clean:
	rm -r *.o
	rm -r *.out