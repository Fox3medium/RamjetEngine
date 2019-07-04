#pragma once

#include <iostream>

#include <vector>

namespace Utils {

	class String {

	public:

		/*!
		*/
		String();
		/*!
		*/
		String(char c);
		/*!
		*/
		String(const char* c);
		/*!
		*/
		String(const unsigned i);


		/*!
		*/
		String(const String& s);

		/*!
		*/
		~String();

		/*!
		*/
		unsigned len() const;

		/*!
		*/
		int index(char c) const;

		/*!
		*/
		int index(String s);
		// Not const because it need to change a parameter in this object

		/*!
		*/
		void upcase();
		/*!
		*/
		void upcase(unsigned first, unsigned last);
		/*!
		*/
		String toUpcase() const;

		/*!
		*/
		void downcase();
		/*!
		*/
		void downcase(unsigned first, unsigned last);
		/*!
		*/
		String toDowncase() const;

		/*!
		*/
		void togglecase(unsigned first, unsigned last);
		/*!
		*/
		String toggleCase() const;

		/*!
		*/
		String backWard() const;

		/*!
		*/
		char* toChars() const;

		/*!
		*/
		char at(unsigned index) const;

	private:
		/*!
		*/
		bool contain(char c) const;

	public:
		/*!
		*/
		bool contains(String s);

		/*!
		*/
		String subStr(unsigned first, unsigned len) const;
		/*!
		*/
		String subStr(unsigned start) const;

		/*!
		*/
		std::vector<std::string> splitStr(const std::string &str, char delimeter) const;

		/*!
		*/
		void insert(unsigned index, String s);
		/*!
		*/
		void insert(unsigned index, char c);

		/*!
		*/
		void replace(String s, String toReplace);
		/*!
		*/
		void replace(char c, String toReplace);
		/*!
		*/
		void replace(char c, char toReplace);

		/*!
		*/
		void sanitize();

		/*!
		*/
		void add(String S);
		/*!
		*/
		void add(char c);

		/*!
		*/
		void resize(unsigned size);

		/*!
		*/
		int size() const;

		/*!
		*/
		//void push_back();
		/*!
		*/
		//void pop_back();

		/*!
		*/
		//void erease();

		//@{
		/*!
		*/
		static String toString(int i);
		static String toString(double d);
		static String toString(float f);
		static String toString(bool b);
		//@}

		bool toBool();

	private:
		char* data;
		unsigned length;
		unsigned indexOf = 0;

		void updateDatas(String a);


	public:

		//@{
		/*!
		*/
		operator char* ();
		//@}

		//@{
		/*!
		*/
		operator std::string();
		//@}

		//@{
		/*!
		*/
		friend std::ostream& operator<< (std::ostream& so, const String& s);
		friend std::istream& operator>> (std::istream& so, String& s);
		//@}

		//@{
		/*!
		*/
		char  operator[] (unsigned j) const;
		char& operator[] (unsigned j);
		//@}

		//@{
		/*!
		*/
		String& operator= (const String& s);
		//@}

		//@{
		/*!
		*/
		String& operator+= (const String& s);
		//@}

		//@{
		/*!
		*/
		String& operator-= (const String& s);
		//@}

		//@{
		/*!
		*/
		friend String operator+ (const String& lhs, const String& rhs);
		friend String operator+ (const String& lhs, char          rhs);
		friend String operator+ (const String& lhs, const char* rhs);
		friend String operator+ (char          lhs, const String& rhs);
		friend String operator+ (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend String operator- (const String& lhs, const String& rhs);
		friend String operator- (const String& lhs, char          rhs);
		friend String operator- (const String& lhs, const char* rhs);
		friend String operator- (char          lhs, const String& rhs);
		friend String operator- (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator== (const String& lhs, const String& rhs);
		friend bool operator== (const String& lhs, char          rhs);
		friend bool operator== (const String& lhs, const char* rhs);
		friend bool operator== (char          lhs, const String& rhs);
		friend bool operator== (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator!= (const String& lhs, const String& rhs);
		friend bool operator!= (const String& lhs, char          rhs);
		friend bool operator!= (const String& lhs, const char* rhs);
		friend bool operator!= (char          lhs, const String& rhs);
		friend bool operator!= (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator> (const String& lhs, const String& rhs);
		friend bool operator> (const String& lhs, char          rhs);
		friend bool operator> (const String& lhs, const char* rhs);
		friend bool operator> (char          lhs, const String& rhs);
		friend bool operator> (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator< (const String& lhs, const String& rhs);
		friend bool operator< (const String& lhs, char          rhs);
		friend bool operator< (const String& lhs, const char* rhs);
		friend bool operator< (char          lhs, const String& rhs);
		friend bool operator< (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator<= (const String& lhs, const String& rhs);
		friend bool operator<= (const String& lhs, char          rhs);
		friend bool operator<= (const String& lhs, const char* rhs);
		friend bool operator<= (char          lhs, const String& rhs);
		friend bool operator<= (const char* lhs, const String& rhs);
		//@}

		//@{
		/*!
		*/
		friend bool operator>= (const String& lhs, const String& rhs);
		friend bool operator>= (const String& lhs, char          rhs);
		friend bool operator>= (const String& lhs, const char* rhs);
		friend bool operator>= (char          lhs, const String& rhs);
		friend bool operator>= (const char* lhs, const String& rhs);
		//@}

	};
}