/*#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
//cbx9999999
void thisIsATest() {
	ASSERTM("start writing tests", false);
}

void runSuite(){
	cute::suite s;
	//TODO add your test here
	s.push_back(CUTE(thisIsATest));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "The Suite");
}

int main(){
    runSuite();
    return 0;
}

*/

#include "Data.h"

using namespace std;

int foo()
{
	Data d1;

	return 0;
}
