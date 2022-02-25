#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;
/*
Description:
To call this function, simply pass the function name in Python that you wish to call.
Example:
callProcedure("printsomething");
Output:
Python will print on the screen: Hello from python!
Return:
None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();
	delete[] procname;
}

/*
Description:
To call this function, pass the name of the Python functino you wish to call and the string
parameter you want to send
Example:
int x = callIntFunc("PrintMe","Test");
Output:
Python will print on the screen:
You sent me: Test
Return:
100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];

	std::strcpy(procname, proc.c_str());
	char* paramval = new char[param.length() + 1];

	std::strcpy(paramval, param.c_str());
	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up

	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();
	// clean 
	delete[] procname;
	delete[] paramval;
	return _PyLong_AsInt(presult);
}

/*
Description:
To call this function, pass the name of the Python functino you wish to call and the string
parameter you want to send
Example:
int x = callIntFunc("doublevalue",5);
Return:
25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;

	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();

		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}

	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	return _PyLong_AsInt(presult);
}
#include <iostream>
using namespace std;
int main()
{
	int option;
	// Declares integer option
	int userNum;
	// Declares integer userNum
	cout << "1: Display a multiplication table" << endl; // Prints optionsand prompts user to pick one
	cout << "2: Double a value" << endl;
	cout << "3: Exit" << endl;
	cout << "Please enter your selection as a number 1, 2, or 3: " << endl;
	cin >> option;
	// Takes user input and sets it as option

	if (option == 1) {
		// If user chooses option number 1:
		cout << "Enter a value: ";
		// Prompts user to enter value
		cin >> userNum;
		// Takes user input and sets it as userNum
		cout << endl;
		// Prints newline
		cout << callIntFunc("MultiplicationTable", userNum) << endl;
		// Calls on python function to display multiplcation table
	}

	else if (option == 2) {
		// If user chooses option number 2:
		cout << "Enter a value to double: ";
		// Prompts user to enter value
		cin >> userNum;
		// Takes user input and sets it as userNum
		cout << endl;
		// Prints newline
		cout << callIntFunc("DoubleValue", userNum) << endl;
	}
	// End of second IF
	else if (option == 3) {
		// If user chooses option number 3:
		cout << endl;
		// Prints newline
		cout << "Goodbye" << endl;
		// Prints "Goodbye" if user chooses to exitand breaks
	}
	// End of third IF
	else {
		cout << "Error: Please only enter 1, 2, or 3" << endl;
		// Prints Error message
	}
	system("pause");
	// Keeps information on screen
	return 0;
}
// CallProcedure("printsomething");
// cout << callIntFunc("PrintMe", "House") << endl;
// cout << callIntFunc("SquareValue", 2);

 