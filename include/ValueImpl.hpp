#ifndef VALUEIMPLE_HPP
#define VALUEIMPLE_HPP

#include <ostream>
#include <typeinfo>

class ValueImplBase
{
    public:
        virtual ~ValueImplBase() = default;
        virtual void print(std::ostream& os) const = 0;
        // TODO try to make it constexpr
        virtual const std::type_info& type() const = 0;
        virtual ValueImplBase* clone() const = 0;
};

template <typename T>
class ValueImpl : public ValueImplBase
{
    public:
        ValueImpl(T value);
        virtual ~ValueImpl() override = default;
        virtual void print(std::ostream& os) const override;
        virtual const std::type_info& type() const override;
        virtual ValueImplBase* clone() const override;
        const T& getValue() const;

    private:
        T _value;
};

template <typename T>
ValueImpl<T>::ValueImpl(T value):
    _value{std::move(value)}
{
}

template <typename T>
void ValueImpl<T>::print(std::ostream& os) const
{
    os << _value;
}

template <typename T>
const std::type_info& ValueImpl<T>::type() const
{
    return typeid(T);
}

template <typename T>
ValueImplBase* ValueImpl<T>::clone() const
{
    return new ValueImpl{_value};
}

template <typename T>
const T& ValueImpl<T>::getValue() const
{
    return _value;
}


#endif // VALUEIMPLE_HPP
