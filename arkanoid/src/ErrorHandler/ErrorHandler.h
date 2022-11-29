#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <iostream>

struct Error
{
public:
	std::string msg;
	std::string where_;
	bool err = true;
};

/// <summary>
/// Throw new error
/// Method overwirite old error
/// </summary>
/// <param name="_where">place in code where [__PRETTY_FUNCTION__]</param>
/// <param name="_msg">message what's gone wrong</param>
void throwError(std::string _where, std::string _msg);

/// <summary>
/// Throw new warning
/// Method overwrite old warning
/// </summary>
/// <param name="_where">place in code where [__PRETTY_FUNCTION__]</param>
/// <param name="_msg">message what's warning</param>
void throwWarning(std::string _where, std::string _msg);

/// <summary>
/// Returns true if any error is unhandled
/// </summary>
bool anyUnhandledErrWar();

/// <summary>
/// Returns error or warning if any unhandled or nullptr
/// </summary>
Error* handleErrWar();

/// <summary>
/// Default error handler. Only put it into update loop
/// </summary>
void handleDef();

__declspec(selectany) Error* __err__;
__declspec(selectany) Error* __war__;

#endif
