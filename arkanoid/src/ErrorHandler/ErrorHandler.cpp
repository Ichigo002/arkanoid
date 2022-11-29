#include "ErrorHandler.h"

void throwError(std::string _where, std::string _msg)
{
	Error* e = new Error();
	e->msg = _msg;
	e->where_ = _where;
	e->err = true;
	__err__ = e;
}

void throwWarning(std::string _where, std::string _msg)
{
	Error* e = new Error();
	e->msg = _msg;
	e->where_ = _where;
	e->err = false;
	__war__ = e;
}

bool anyUnhandledErrWar()
{
	return __err__ || __war__;
}

Error* handleErrWar()
{
	if (__err__)
	{
		Error* e = __err__;
		__err__ = nullptr;
		return e;
	}
	if (__war__)
	{
		Error* e = __war__;
		__war__ = nullptr;
		return e;
	}
	return nullptr;
}

void handleDef()
{
	if (anyUnhandledErrWar())
	{
		Error* e = handleErrWar();

		std::cout
			<< std::endl
			<< (e->err ? "*> ERROR" : "*> WARNING")
			<< " occured in \""
			<< e->where_
			<< "\" with below message:\n"
			<< "  " << e->msg
			<< std::endl;
	}
}
