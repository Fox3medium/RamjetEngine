#include "String.h"
#include <string>
#include <cstring>

namespace Utils {

	String::String()
	{
		length = 0;
		data = new char[0];
	}

	String::String(char c)
	{
		length = 1;
		data = new char[2];
		data[0] = c;
		data[1] = '\0';
	}

	String::String(const char* c)
	{
		if (c)
		{
			unsigned n = 0;
			while (c[n] != '\0')
				n++;
			length = n;
			data = new char[n + 1];
			data[n] = '\0';
			for (unsigned j = 0; j < n; j++)
				data[j] = c[j];
		}
		else
		{
			length = 0;
			data = new char[0];
		}
	}

	String::String(const unsigned i)
	{
		data = new char[i + 1];
		data[i] = '\0';
		length = i;
	}

	String::String(const String& s)
	{
		length = s.len();
		data = new char[length + 1];
		data[length] = '\0';
		for (unsigned j = 0; j < length; j++)
			data[j] = s[j];
	}

	String::~String()
	{
		delete[] data;
	}

	unsigned String::len() const
	{
		return length;
	}

	int String::index(char c) const
	{
		for (unsigned j = 0; j < length; j++)
			if (data[j] == c) return (int)j;
		return -1;
	}

	int String::index(String s)
	{
		this->contains(s);
		return indexOf;
	}

	void String::upcase()
	{
		unsigned last = this->len();
		this->upcase(0, last);
	}

	void String::upcase(unsigned first, unsigned last)
	{
		if ((first >= last) || (last > length)) throw 1;

		for (unsigned j = first; j < last; j++)
			if ('a' <= data[j] && data[j] <= 'z')
				data[j] -= ('a' - 'A');
	}

	String String::toUpcase() const
	{
		String ret = this->toChars();
		unsigned retLength = ret.len();
		ret.upcase(0, retLength);
		return ret;
	}

	void String::downcase()
	{
		unsigned last = this->len();
		this->upcase(0, last);
	}

	void String::downcase(unsigned first, unsigned last)
	{
		if ((first >= last) || (last > length)) throw 1;

		for (unsigned j = first; j < last; j++)
			if ('A' <= data[j] && data[j] <= 'Z')
				data[j] += ('a' - 'A');
	}

	String String::toDowncase() const
	{
		String ret = this->toChars();
		unsigned retLength = ret.len();
		ret.downcase(0, retLength);
		return ret;
	}

	void String::togglecase(unsigned first, unsigned last)
	{
		if ((first >= last) || (last > length)) throw 1;

		for (unsigned j = first; j < last; j++)
			if ('A' <= data[j] && data[j] <= 'Z')
				data[j] += ('a' - 'A');
			else if ('a' <= data[j] && data[j] <= 'z')
				data[j] -= ('a' - 'A');
	}

	String String::toggleCase() const
	{
		String ret = this->toChars();
		unsigned retlen = ret.len();

		return String(retlen);
	}

	String String::backWard() const
	{
		return String();
	}

	char* String::toChars() const
	{
		char* c = new char[length];
		c = data;
		return c;
	}

	char String::at(unsigned index) const
	{
		char c = '\0';
		if (index < length)
			c = this->index(index);
		return c;
	}

	bool String::contain(char c) const
	{
		for (unsigned int i = 0; i < length; i++)
			if (data[i] == c)
				return true;
		return false;
	}

	bool String::contains(String s)
	{
		unsigned sLength = s.length;
		unsigned l = 0;
		for (unsigned int i = 0; i < length; i++) {
			if (data[i] == s[l]) {
				l++;
				if (l >= sLength) {
					indexOf = i - sLength + 1;
					return true;
				}
			}
			else l = 0;
		}

		indexOf = -1;
		return false;
	}

	String String::subStr(unsigned first, unsigned len) const
	{
		String ret;
		unsigned int last = first + len;
		if (last > length) {
			last = length;
			ret = String(length - first);
		}
		else ret = String(len);

		unsigned int i = 0;

		for (unsigned int j = first; j < last; j++) {
			ret[i] = data[j];
			i++;
		}

		return ret;
	}

	String String::subStr(unsigned start) const
	{
		unsigned last = length - start;
		String ret = this->subStr(start, last);
		return ret;
	}

	void String::insert(unsigned index, String s)
	{
		String data1 = this->subStr(0, index);
		String data2 = this->subStr(index, length);

		unsigned len = length + s.len();

		String ret = String(length + s.len());
		updateDatas(ret);
	}

	void String::insert(unsigned index, char c)
	{
		String out = String(c);
		insert(index, out);
	}

	void String::replace(String s, String toReplace)
	{
		String ret = data;
		String d1;
		String d2;
		unsigned pastIndexOf = -2;
		while (ret.contains(toReplace) && ret.indexOf != pastIndexOf && ret.indexOf != pastIndexOf + s.len()) {
			d1 = ret.subStr(0, ret.indexOf);
			d2 = ret.subStr(ret.indexOf + toReplace.len(), ret.len());
			ret = d1 + s + d2;
			pastIndexOf = ret.indexOf;
		}
		updateDatas(ret);
	}

	void String::replace(char c, String toReplace)
	{
		String out = c;
		replace(out, toReplace);
	}

	void String::replace(char c, char toReplace)
	{
		String out1 = c;
		String out2 = toReplace;
		replace(out1, out2);
	}

	void String::sanitize()
	{
		replace("", "\n");
		replace("", "\t");
		replace("", " ");
	}

	void String::add(String S)
	{
		String a = data;
		a += S;
		updateDatas(a);
	}

	void String::add(char c)
	{
		String a = c;
		add(a);
	}

	void String::resize(unsigned size)
	{
		if (size < length) {
			String a = subStr(0, size);
			updateDatas(a);
		}
		else {
			String a = String(size);
			add(a);
		}

	}

	int String::size() const
	{
		return length;
	}

	std::ostream& operator<< (std::ostream& os, const String& s)
	{
		if (s.len() > 0)
		{
			for (unsigned j = 0; j < s.len(); j++)
				os << s[j];
		}
		else os << "";

		return os;
	}

	std::istream& operator>> (std::istream& is, String& s)
	{
		char* c = new char[1000];
		is >> c;
		s = String(c);
		delete[] c;

		return is;
	}

	String String::toString(int i)
	{
		std::string s = std::to_string(i);
		String ret = s.c_str();
		return ret;
	}

	String String::toString(double d)
	{
		std::string s = std::to_string(d);
		String ret = s.c_str();
		return ret;
	}

	String String::toString(float f)
	{
		std::string s = std::to_string(f);
		String ret = s.c_str();
		return ret;
	}

	String String::toString(bool b)
	{
		if (b) {
			return String("true");
		}
		return String("false");
	}

	bool String::toBool() {
		if (contains("true") | contains("1")) {
			return true;
		}
		return false;
	}

	void String::updateDatas(String a)
	{
		unsigned len = a.len();
		delete data;
		data = new char[len + 1];
		for (unsigned int i = 0; i < len; i++) {
			data[i] = a[i];
		}
		data[a.len()] = '\0';
		length = a.len();
	}

	String::operator char* ()
	{
		return data;
	}

	String::operator std::string()
	{
		std::string ret = data;
		return ret;
	}

	char String::operator[] (unsigned j) const
	{
		if (j >= length) throw 1;
		return data[j];
	}

	char& String::operator[] (unsigned j)
	{
		if (j >= length) throw 1;
		return data[j];
	}



	String& String::operator= (const String& s)
	{
		if (this == &s) return *this;

		delete data;
		length = s.len();
		data = new char[length + 1];
		data[length] = '\0';
		for (unsigned j = 0; j < length; j++)
			data[j] = s[j];
		return *this;
	}



	String& String::operator+= (const String& s)
	{
		/*unsigned len = length + s.len();
		unsigned last=0;
		char* str = new char[len + 1];
		str[len] = '\0';

		for (unsigned j = 0; j < length; j++) {
			str[j] = data[j];
			last = j;
		}

		for (unsigned i = 0; i < s.len(); i++)
			str[last + i] = s[i];*/

		std::string s1 = data;
		std::string s2 = s.data;
		std::string s3 = s1 + s2;
		String s4 = s3.c_str();
		char* str = s4.data;

		delete data;
		length = s4.len();
		data = str;
		return *this;
	}

	String& String::operator-=(const String& s)
	{
		replace("", s);
		return *this;
	}



	String operator+ (const String& lhs, const String& rhs)
	{
		return String(lhs) += rhs;
	}

	String operator+ (const String& lhs, char rhs)
	{
		return String(lhs) += String(rhs);
	}

	String operator+ (const String& lhs, const char* rhs)
	{
		return String(lhs) += String(rhs);
	}

	String operator+ (char lhs, const String& rhs)
	{
		return String(lhs) += rhs;
	}
	String operator+ (const char* lhs, const String& rhs)
	{
		return String(lhs) += rhs;
	}

	String operator-(const String& lhs, const String& rhs)
	{
		return String(lhs) -= rhs;
	}

	String operator-(const String& lhs, char rhs)
	{
		return String(lhs) -= String(rhs);

	}

	String operator-(const String& lhs, const char* rhs)
	{
		return String(lhs) -= String(rhs);

	}

	String operator-(char lhs, const String& rhs)
	{
		return String(lhs) -= rhs;

	}

	String operator-(const char* lhs, const String& rhs)
	{
		return String(lhs) -= rhs;

	}



	bool operator== (const String& lhs, const String& rhs)
	{
		if (lhs.len() != rhs.len()) return false;

		unsigned cap = lhs.len();
		unsigned   n = 0;
		while ((n < cap) && (lhs[n] == rhs[n])) n++;
		return (n == cap);
	}

	bool operator== (const String& lhs, char rhs)
	{
		return (lhs == String(rhs));
	}

	bool operator== (const String& lhs, const char* rhs)
	{
		return (lhs == String(rhs));
	}

	bool operator== (char lhs, const String& rhs)
	{
		return (String(lhs) == rhs);
	}

	bool operator== (const char* lhs, const String& rhs)
	{
		return (String(lhs) == rhs);
	}



	bool operator> (const String& lhs, const String& rhs)
	{
		unsigned cap = (lhs.len() < rhs.len()) ? lhs.len() : rhs.len();
		unsigned n = 0;
		while ((n < cap) && (lhs[n] == rhs[n])) n++;
		if (n == cap) return (lhs.len() > rhs.len());

		if ((('A' <= lhs[n] && lhs[n] <= 'Z') || ('a' <= lhs[n] && lhs[n] <= 'z')) &&
			(('A' <= rhs[n] && rhs[n] <= 'Z') || ('a' <= rhs[n] && rhs[n] <= 'z')))
		{
			char A = (lhs[n] & ~32);
			char B = (rhs[n] & ~32);
			if (A != B) return (A > B);
		}
		return lhs[n] > rhs[n];
	}

	bool operator> (const String& lhs, char rhs)
	{
		return (lhs > String(rhs));
	}

	bool operator> (const String& lhs, const char* rhs)
	{
		return (lhs > String(rhs));
	}

	bool operator> (char lhs, const String& rhs)
	{
		return (String(lhs) > rhs);
	}

	bool operator> (const char* lhs, const String& rhs)
	{
		return (String(lhs) > rhs);
	}



	bool operator!= (const String& lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator!= (const String& lhs, char rhs)
	{
		return !(lhs == rhs);
	}

	bool operator!= (const String& lhs, const char* rhs)
	{
		return !(lhs == rhs);
	}

	bool operator!= (char lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator!= (const char* lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}



	bool operator< (const String& lhs, const String& rhs)
	{
		return !(lhs == rhs) && !(lhs > rhs);
	}

	bool operator< (const String& lhs, char rhs)
	{
		return !(lhs == rhs) && !(lhs > rhs);
	}

	bool operator< (const String& lhs, const char* rhs)
	{
		return !(lhs == rhs) && !(lhs > rhs);
	}

	bool operator< (char lhs, const String& rhs)
	{
		return !(lhs == rhs) && !(lhs > rhs);
	}

	bool operator< (const char* lhs, const String& rhs)
	{
		return !(lhs == rhs) && !(lhs > rhs);
	}



	bool operator<= (const String& lhs, const String& rhs)
	{
		return !(lhs > rhs);
	}

	bool operator<= (const String& lhs, char rhs)
	{
		return !(lhs > rhs);
	}

	bool operator<= (const String& lhs, const char* rhs)
	{
		return !(lhs > rhs);
	}

	bool operator<= (char lhs, const String& rhs)
	{
		return !(lhs > rhs);
	}

	bool operator<= (const char* lhs, const String& rhs)
	{
		return !(lhs > rhs);
	}



	bool operator>= (const String& lhs, const String& rhs)
	{
		return (lhs == rhs) || (lhs > rhs);
	}

	bool operator>= (const String& lhs, char rhs)
	{
		return (lhs == rhs) || (lhs > rhs);
	}

	bool operator>= (const String& lhs, const char* rhs)
	{
		return (lhs == rhs) || (lhs > rhs);
	}

	bool operator>= (char lhs, const String& rhs)
	{
		return (lhs == rhs) || (lhs > rhs);
	}

	bool operator>= (const char* lhs, const String& rhs)
	{
		return (lhs == rhs) || (lhs > rhs);
	}
}