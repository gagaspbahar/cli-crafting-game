#include "../Item.cpp"
#include "../Nontool.cpp"
#include "../Tool.cpp"

using namespace std;

int main(){
    Item* a = new NonTool(1, "OAK_LOG", "LOG", 10);
    Item* b = a;
    cout << b->getQty() << endl;
    if (a == b){
    	cout << "A " << a->getName() << " dan B " << b->getName() << " sama" << endl;
	}
	a->setQty(5);
	cout << "Quantity A sekarang = " << a->getQty() << endl;
	Item *c = a;
	cout << c->getType() << endl;
	cout << c->getQty() << endl;
	Item* d = new Tool();
	d->setDura(7);
	d->setId(1);
	cout << d->getDura() << endl;
	cout << d->getId() << endl;

    return 0;
}
