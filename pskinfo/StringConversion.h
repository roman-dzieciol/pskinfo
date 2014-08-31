
#pragma once


wstring toWideString( const char* pStr );
string toNarrowString( const wchar_t* pStr );


// ============================================================================
//  DeleteObject
// ============================================================================
struct DeleteObject
{
	template<typename T> void operator()(const T* ptr) const
	{
		delete ptr;
	}
};


// ============================================================================
//  string_make
// ============================================================================
class string_make : public ostringstream 
{
public:
	operator string() const { return str(); };
	template<typename AA>
	string_make &operator << (const AA &str) 
	{
		*static_cast<ostringstream *>(this) << str;
		return *this;
	}
};

// ============================================================================
//  cstring_make
// ============================================================================
class cstring_make : public string_make 
{
public:
	operator const char *() const { return str().c_str(); }
private:
	operator string() const { return str(); };
};


// ============================================================================
//  std::string trim
// ============================================================================
inline string trim(const string& s, const string& chars) 
{
	if( s.length() != 0 )
	{
		size_t beg = s.find_first_not_of(chars);
		size_t end = s.find_last_not_of(chars);
		if(beg != string::npos)
			return string(s, beg, end - beg + 1);
	}
	return "";
}