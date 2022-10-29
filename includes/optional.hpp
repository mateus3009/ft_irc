#ifndef OPTIONAL_HPP
# define OPTIONAL_HPP

# include "exceptions.hpp"

template <typename T>
class optional
{
    public:
        virtual ~optional() {}

        virtual bool is_present(void) const = 0;

        virtual T get(void) const = 0;
};

template <typename T>
class empty : public optional<T>
{
    public:
        bool is_present(void) const { return false; }

        T get(void) const { throw illegal_access_exception("The optional is empty!"); }
};

template <typename T>
class optional_data : public optional<T>
{
    private:
        T _value;

    public:
        optional_data(const T& value) : _value(value) {}

        bool is_present(void) const { return true; }

        T get(void) const { return _value; }
};

#endif
