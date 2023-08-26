#include <exception>
#include <sstream>

namespace Simple
{
	using namespace std;

	class Exception: public exception
	{
		string Error;
	public:
		Exception(string Err,string FileName,int Line)
		{
			stringstream ss;
			ss<<"Exception: "<<Err<<'\n'<<"File: "<<FileName<<'\n'<<"Line: "<<Line<<'\n';
			Error = ss.str();
		}

		virtual const char* what() const throw()
		{
			return Error.c_str();
		}
	};
}
