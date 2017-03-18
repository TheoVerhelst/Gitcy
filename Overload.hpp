#ifndef OVERLOAD_HPP
#define OVERLOAD_HPP

#include <functional>
#include <ostream>
#include <vector>
#include "Data.hpp"
#include "SignatureType.hpp"

typedef std::function<Data(const std::vector<Data>&)> Functor;

class Overload
{
	public:
		Overload(const std::vector<SignatureType>& typeList, bool isVariadic, const Functor& functor);
		bool matches(const std::vector<Data>& arguments) const;
		/// \precondition matches(arguments)
		Data operator()(const std::vector<Data>& arguments) const;

		friend std::ostream& operator<<(std::ostream& os, const Overload& signature);

	private:
		std::vector<SignatureType> _typeList;
		bool _isVariadic;
		Functor _functor;
};


#endif // OVERLOAD_HPP
