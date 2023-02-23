#include <iostream>
#include "barchartanimate.h"

using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarOperatorLessThan() {
	Bar b("Chicago", 9234324, "US");
	Bar b2("Chicago", 9234329, "US");
	if(b2 <= b) {
		cout << "testBarOperatorLessThan: operator < failed" << endl;
		return false;
	}
	cout << "testBarOperatorLessThan: all passed!" << endl;
	return true;
}

bool testBarOperatorGreaterThan() {
	Bar b("Chicago", 9234324, "US");
	Bar b2("Chicago", 9234322, "US");
	if(b2 >= b) {
		cout << "testBarOperatorGreaterThan: operator > failed" << endl;
		return false;
	}
	cout << "testBarOperatorGreaterThan: all passed!" << endl;
	return true;
}

bool testBarOperatorGreaterThanOrEqualTo() {
	Bar b("Chicago", 9234324, "US");
	Bar b2("Chicago", 9234326, "US");
	if(b2 > b) {
		cout << "testBarOperatorGreaterThanOrEqualTo: operator >= failed" << endl;
		return false;
	}
	cout << "testBarOperatorGreaterThanOrEqualTo: all passed!" << endl;
	return true;
}

bool testBarOperatorLessThanOrEqualTo() {
	Bar b("Chicago", 9234324, "US");
	Bar b2("Chicago", 9234320, "US");
	if(b2 < b) {
		cout << "testBarOperatorLessThanOrEqualTo: opeator <= failed" << endl;
		return false;
	}
	cout << "testBarOperatorLessThanOrEqualTo: all passed!" << endl;
	return true;
}
bool testBarChartCopyConstructor() {
	BarChart bc1(10);
	BarChart bc2(bc1);
	if(bc1.getSize() != bc2.getSize()) {
		cout << "testBarChartCopyConstructor: copy constructor failed" << endl;
		return false;
	}
	cout << "testBarChartCopyConstructor: all passed!" << endl;
	return true;
}
bool testBarChartCopyOperator() {
	BarChart bc1;
	BarChart bc2(10);
	bc1 = bc2;
	if(bc1.getSize() != bc2.getSize()) {
		cout << "testBarChartCopyOperator: copy operator failed" << endl;
		return false;
	}
	cout << "testBarChartCopyOperator: all passed!" << endl;
	return true;
}
void testBarChartGraph() {

  BarChart chart(4);
  chart.addBar("test1", 10, "category1");
  chart.addBar("test2", 7, "category2");
  chart.addBar("test3", 12, "category3");
  chart.addBar("test4", 4, "category4");

  map<string, string> colors;
  colors.emplace("category1", "\033[1;36m");
  colors.emplace("category2", "\033[1;32m");
  colors.emplace("category3", "\033[1;35m");
  colors.emplace("category4", "\033[1;34m");
  chart.dump(cout);
  chart.graph(cout, colors, 10);
}
int main() {
	testBarDefaultConstructor();
	testBarParamConstructor();
	testBarOperatorLessThan();
	testBarOperatorGreaterThan();
	testBarOperatorGreaterThanOrEqualTo();
	testBarOperatorLessThanOrEqualTo();
	testBarChartCopyConstructor();
	testBarChartCopyOperator();
  testBarChartGraph();
  return 0;
}