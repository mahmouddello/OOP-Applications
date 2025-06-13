#pragma once
#include "clsPerson.h"
#include <vector>
#include <fstream>
#include <string>
#include "../cpplibs/clsString.h"
#include "../cpplibs/clsDate.h"
#include "../cpplibs/clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
public:

	struct stLoginRegisterRecord
	{
		string datetime;
		string username;
		string password;
		int permissions;
	};

private:
	enum _enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };

	_enMode _mode;
	string _username;
	string _password;
	int _permessions;
	bool _markedForDelete = false;

	static string _converUserObjectToLine(clsUser user, string seperator = "#//#")
	{

		string userRecord = "";
		userRecord += user.firstName + seperator;
		userRecord += user.lastName + seperator;
		userRecord += user.email + seperator;
		userRecord += user.phoneNumber + seperator;
		userRecord += user._username + seperator;
		userRecord += clsUtil::encryptMessage(user.password) + seperator;
		userRecord += to_string(user.permessions);

		return userRecord;

	}

	static clsUser _convertLineToUserObject(string line, string seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::split(line, seperator);

		return clsUser(_enMode::updateMode, vUserData[0], vUserData[1],
			vUserData[2], vUserData[3], vUserData[4],
			clsUtil::decryptMessage(vUserData[5]), stoi(vUserData[6]));
	}

	static vector<clsUser> _loadUsersDataFromFile()
	{
		string line;
		fstream file;
		vector<clsUser> v;
		file.open("users.txt", ios::in);

		if (file.is_open())
		{
			while (getline(file, line))
			{
				v.push_back(_convertLineToUserObject(line));
			}

			file.close();
		}

		return v;
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream MyFile;
		MyFile.open("users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << dataLine << endl;

			MyFile.close();
		}
	}

	static void _saveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream file;
		file.open("users.txt", ios::out);

		if (file.is_open())
		{
			for (clsUser user : vUsers)
			{
				if (!user.isMarkedForDelete())
				{
					file << _converUserObjectToLine(user) << endl;
				}
			}

			file.close();
		}
	}

	static clsUser _getEmptyUserObject()
	{
		return clsUser(_enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	void _update()
	{
		vector<clsUser> _vUsers = _loadUsersDataFromFile();
		for (clsUser& user : _vUsers)
		{
			if (user.getUsername() == _username)
			{
				user = *this;
				break;
			}
		}

		_saveUsersDataToFile(_vUsers);
	}

	void _addNew()
	{
		_addDataLineToFile(_converUserObjectToLine(*this));
	}

	string _prepareLoginRecord(string sep = "#//#")
	{
		vector<string> vData(4);

		vData[0] = clsDate::getSystemDateTime();
		vData[1] = this->getUsername();
		vData[2] = clsUtil::encryptMessage(this->password);
		vData[3] = to_string(this->permessions);

		return clsString::join(vData, sep);
	}

	static stLoginRegisterRecord _convertLineToLoginRecord(string line, string sep = "#//#")
	{
		stLoginRegisterRecord record;

		vector<string> loginRegisterDataLine = clsString::split(line, sep);
		record.datetime = loginRegisterDataLine[0];
		record.username = loginRegisterDataLine[1];
		record.password = clsUtil::decryptMessage(loginRegisterDataLine[2]);
		record.permissions = stoi(loginRegisterDataLine[3]);

		return record;
	}

public:
	clsUser
	(
		_enMode mode,
		string firstName,
		string lastName,
		string email,
		string phoneNumber,
		string username,
		string password,
		int permessions
	) : clsPerson(firstName, lastName, email, phoneNumber)
	{
		_mode = mode;
		_username = username;
		_password = password;
		_permessions = permessions;
	}

	enum enPermessions
	{
		eAll = -1,
		pShowClientsList = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pLoginRegitser = 128,
	};

	// read-only property
	string getUsername()
	{
		return _username;
	}

	// property get
	string getPassword()
	{
		return _password;
	}

	// property set
	void setPassword(string password)
	{
		_password = password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string password;

	// property get
	int getPermissions()
	{
		return _permessions;
	}

	// property set
	void setPermessions(int permessions)
	{
		_permessions = permessions;
	}

	__declspec(property(get = getPermissions, put = setPermessions)) int permessions;

	bool isMarkedForDelete()
	{
		return _markedForDelete;
	}

	bool isEmpty()
	{
		return _mode == _enMode::emptyMode;
	}

	static bool isUserExist(string username)
	{
		clsUser user = find(username);

		return !(user.isEmpty());
	}

	static clsUser getAddNewUserObject(string username)
	{
		return clsUser(_enMode::addNewMode, "", "", "", "", username, "", 0);
	}

	static clsUser find(string username)
	{

		fstream MyFile;
		MyFile.open("users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser user = _convertLineToUserObject(Line);
				if (user.getUsername() == username)
				{
					MyFile.close();
					return user;
				}

			}

			MyFile.close();

		}

		return _getEmptyUserObject();
	}

	static clsUser find(string username, string password)
	{

		fstream MyFile;
		MyFile.open("users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser user = _convertLineToUserObject(Line);
				if (user.getUsername() == username && user.getPassword() == password)
				{
					MyFile.close();
					return user;
				}

			}

			MyFile.close();

		}

		return _getEmptyUserObject();
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedBecauseUserExist = 2 };

	static vector<clsUser> getUsersList()
	{
		return _loadUsersDataFromFile();
	}

	enSaveResults save()
	{
		switch (_mode)
		{
			case _enMode::emptyMode:
			{
				if (isEmpty())
					return enSaveResults::svFailedEmptyObject;
			}
			case _enMode::updateMode:
			{
				_update();
				return enSaveResults::svSucceeded;
			}
			case _enMode::addNewMode:
			{
				if (isUserExist(_username))
					return enSaveResults::svFailedBecauseUserExist;

				_addNew();

				// update the mode, becuase object is added to file, and it's still in memory
				_mode = _enMode::updateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	bool deleteUser()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& user: vUsers)
		{
			if (user.getUsername() == _username)
			{
				user._markedForDelete = true;
				*this = _getEmptyUserObject();
				_saveUsersDataToFile(vUsers);
				return true;
			}
		}

		return false;
	}

	static bool authenticateLogin(string username, string password)
	{
		clsUser user = clsUser::find(username, password);
		return !(user.isEmpty());
	}

	bool checkAccessPermission(enPermessions ePermissions)
	{
		short per = pow(2, short(ePermissions - 1));
		
		if (this->permessions == enPermessions::eAll)
			return true;

		if ((this->permessions & per) == per)
			return true;

		return false;
	}

	void registerLogin()
	{
		fstream file;
		file.open("logs.txt", ios::app | ios::out);

		if (file.is_open())
		{
			string dataLine = _prepareLoginRecord();
			file << dataLine << endl;

			file.close();
		}
	}

	static vector<stLoginRegisterRecord> getRegisterLoginLogs()
	{
		fstream file;
		file.open("logs.txt", ios::in);
		vector<stLoginRegisterRecord> vData;
		string line;

		if (file.is_open())
		{
			while (getline(file, line))
			{
				vData.push_back(_convertLineToLoginRecord(line));
			}
			file.close();
		}

		return vData;
	}

};

