// Prints the maiden names of married women and
// gives marriage advice according to the family tree
// CS44001 Assignment 11 - Genealogy
// Connor DeGeorge
// 4/20/20

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::endl;
using std::string; using std::toupper;
using std::vector;

class Person { // component
public:
	Person(string firstName, Person* spouse, Person* father, Person* mother) :
		firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
	const string& getFirstName() { return firstName_; }
	Person* getSpouse() { return spouse_; }
	void setSpouse(Person* spouse) { spouse_ = spouse; }
	Person* getFather() { return father_; }

	virtual void accept(class PersonVisitor*) = 0;
	virtual ~Person() {}
private:
	const string firstName_;
	Person* spouse_;
	Person* father_;
	Person* mother_;
};


// leaf
// man has a last name 
class Man : public Person {
public:
	Man(string lastName, string firstName, Person* spouse,
		Person* father, Person* mother) :
		lastName_(lastName), Person(firstName, spouse, father, mother) {}
	const string& getLastName() { return lastName_; }
	void accept(class PersonVisitor* visitor) override;
private:
	const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
	Woman(vector<Person*> children,
		string firstName,
		Person* spouse,
		Person* father, Person* mother) :
		children_(children),
		Person(firstName, spouse, father, mother) {}
	const vector<Person*>& getChildren() { return children_; }
	void setChildren(const vector<Person*>& children) { children_ = children; }
	void accept(class PersonVisitor* visitor) override;
private:
	vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
	virtual void visit(Man*) = 0;
	virtual void visit(Woman*) = 0;
	virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) { visitor->visit(this); }

void Woman::accept(PersonVisitor* visitor) {
	// children traversal through mother only
	// father's children are not traversed so as not 
	// to traverse them twice: for mother and father

	visitor->visit(this);
	// traversing descendants
	for (auto child : children_) child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
	void visit(Man* m) override {
		cout << m->getFirstName() << " " << m->getLastName() << endl;
	}
	void visit(Woman* w) override {
		cout << w->getFirstName() << " ";
		if (w->getSpouse() != nullptr)
			cout << static_cast<Man*> (w->getSpouse())->getLastName();
		else if (w->getFather() != nullptr)
			cout << static_cast<Man*> (w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};

class MaidenNamePrinter : public PersonVisitor {
public:
	void visit(Man* m) override {
		cout << m->getFirstName() << ": " << "no maiden name for men" << endl;
	}
	void visit(Woman* w) override {
		cout << w->getFirstName() << ": ";
		if (w->getFather() != nullptr)
			cout << static_cast<Man*> (w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};

class ChildrenPrinter : public PersonVisitor {
public:
	void visit(Man* m) override {
		cout << m->getFirstName() << ": ";
		Woman* spouse = static_cast<Woman*>(m->getSpouse());
		if (spouse != nullptr)
			printNames(spouse->getChildren());
		cout << endl;
	}
	void visit(Woman* w) override {
		cout << w->getFirstName() << ": ";
		printNames(w->getChildren());
		cout << endl;
	}
private:
	void printNames(const vector<Person*>& children) {
		for (const auto c : children)
			cout << c->getFirstName() << ", ";
	}
};

class MarriageAdvisor : public PersonVisitor {
public:
	MarriageAdvisor(string oneFirst, string oneLast, string twoFirst, string twoLast) :
		oneFirst_(oneFirst), oneLast_(oneLast), twoFirst_(twoFirst), twoLast_(twoLast) {}
	void visit(Man* m) override {
		if (m->getFirstName() == oneFirst_ && m->getLastName() == oneLast_) {
			one_ = m;
			if (one_ != nullptr && two_ != nullptr)
				setCanMarry();
		}
		else if (m->getFirstName() == twoFirst_ && m->getLastName() == twoLast_)
			two_ = m;
	}
	void visit(Woman* w) override {
		string lastName;
		if (w->getSpouse() != nullptr)
			lastName = static_cast<Man*>(w->getSpouse())->getLastName();
		else if (w->getFather() != nullptr)
			lastName = static_cast<Man*>(w->getFather())->getLastName();
		else
			lastName = "Doe";

		if (w->getFirstName() == oneFirst_ && lastName == oneLast_)
			one_ = w;
		else if (w->getFirstName() == twoFirst_ && lastName == twoLast_)
			two_ = w;

		if (one_ != nullptr && two_ != nullptr)
			setCanMarry();
	}
	bool canMarry() { return canMarry_; }
private:
	void setCanMarry();
	const string oneFirst_;
	const string oneLast_;
	const string twoFirst_;
	const string twoLast_;
	Person* one_ = nullptr;
	Person* two_ = nullptr;
	bool canMarry_ = false;
};

void MarriageAdvisor::setCanMarry() {
	if (one_ == nullptr || two_ == nullptr) {
		canMarry_ = false;
		return;
	}

	// Trying to marry themselves
	if (one_ == two_) {
		canMarry_ = false;
		return;
	}

	// Already married
	if (one_->getSpouse() != nullptr || two_->getSpouse() != nullptr) {
		canMarry_ = false;
		return;
	}

	// Siblings, have same father
	if (one_->getFather() == two_->getFather()) {
		canMarry_ = false;
		return;
	}

	// Parents
	if (one_->getFather() == two_ || one_->getFather()->getSpouse() == two_) {
		canMarry_ = false;
		return;
	}

	// Children
	if (two_->getFather() == one_ || two_->getFather()->getSpouse() == one_) {
		canMarry_ = false;
		return;
	}

	// Aunts/Uncles, mom's side
	Woman* mom = static_cast<Woman*>(one_->getFather()->getSpouse());
	if (mom != nullptr) {
		if (mom->getFather() != nullptr) {
			Woman* grandma = static_cast<Woman*>(mom->getFather()->getSpouse());
			vector<Person*> au = grandma->getChildren();
			for (Person* p : au)
				if (p == two_) {
					canMarry_ = false;
					return;
				}
		}
	}

	// Aunts/Uncles, dad's side
	Man* dad = static_cast<Man*>(one_->getFather());
	if (dad != nullptr) {
		if (dad->getFather() != nullptr) {
			Woman* grandma = static_cast<Woman*>(dad->getFather()->getSpouse());
			vector<Person*> au = grandma->getChildren();
			for (Person* p : au)
				if (p == two_) {
					canMarry_ = false;
					return;
				}
		}
	}

	// None of the above
	canMarry_ = true;
}

// demonstrating the operation
int main() {

	// setting up the genealogical tree      
	// the tree is as follows
	//    
	//
	//       James Smith  <--spouse-->   Mary 
	//	                                  |
	//	                                 children -------------------------
	//	                                  |              |                |
	//	                                  |              |                |
	//	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
	//	                                  |
	//	                                 children------------
	//	                                  |                 |
	//                                     |                 |
	//	   Jennifer  <--spouse-->  Michael Johnson      Barbara
	//	       |
	//	     children
	//	       |
	//          |
	//	     Susan


	// first generation
	Man* js = new Man("Smith", "James",
		nullptr, nullptr, nullptr);
	Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
	ms->setSpouse(js); js->setSpouse(ms);

	// second generation
	Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
	Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
	ps->setSpouse(wj); wj->setSpouse(ps);

	vector<Person*> marysKids = { ps,
					   new Man("Smith", "Robert", nullptr, js, ms),
					   new Woman({}, "Linda", nullptr, js, ms) };
	ms->setChildren(marysKids);

	// third generation
	Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
	vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
	ps->setChildren(patsKids);

	Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
	vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

	jj->setSpouse(mj); mj->setSpouse(jj);
	jj->setChildren(jensKids);


	// defining two visitors
	ChildrenPrinter* cp = new ChildrenPrinter;
	NamePrinter* np = new NamePrinter;
	MaidenNamePrinter* mnp = new MaidenNamePrinter;

	// executing the traversal with the composite
	// and the specific visitor

	cout << "\nNAME LIST\n";
	ms->accept(np);

	cout << "\nMAIDEN NAME LIST\n";
	ms->accept(mnp);

	cout << endl << endl;

	cout << "CHILDREN LIST\n";
	ms->accept(cp);

	cout << "\nMARRIAGE ADVICE\n";
	while (true) {
		string oneFirst, oneLast, twoFirst, twoLast;
		cout << "Enter first candidate [First Last]: ";
		cin >> oneFirst; cin >> oneLast;
		cout << "Enter second candidate [First Last]: ";
		cin >> twoFirst; cin >> twoLast;
		cout << endl;

		MarriageAdvisor* ma = new MarriageAdvisor(oneFirst, oneLast, twoFirst, twoLast);
		ms->accept(ma);

		if (ma->canMarry())
			cout << "They can marry." << endl;
		else
			cout << "They can not marry." << endl;

		char answer;
		cout << "Check another relationship? [y/n]: ";
		cin >> answer;

		if (toupper(answer) == 'N') break;
	}

	return 0;
}