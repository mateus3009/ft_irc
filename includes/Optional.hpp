#ifndef OPTIONAL_HPP
# define OPTIONAL_HPP

# include "Exceptions.hpp"

template <typename T>
class Optional
{
    public:
        virtual ~Optional() {}

        virtual bool isPresent(void) const = 0;

        virtual T get(void) const = 0;
};

template <typename T>
class Empty : public Optional<T>
{
    public:
        bool isPresent(void) const { return false; }

        T get(void) const { throw IllegalAccessException("The optional is empty!"); }
};

template <typename T>
class OptionalData : public Optional<T>
{
    private:
        T _value;

    public:
        OptionalData(const T& value) : _value(value) {}

        bool isPresent(void) const { return true; }

        T get(void) const { return _value; }
};

#endif
