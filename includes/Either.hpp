#ifndef EITHER_HPP
# define EITHER_HPP

# include "Exceptions.hpp"

template <typename L, typename R>
class Either
{
    public:
        virtual ~Either() {};

        virtual L left(void) const = 0;

        virtual bool isLeft(void) const = 0;

        virtual R right(void) const = 0;

        virtual bool isRight(void) const = 0;

};

template <typename L, typename R>
class Left : public Either<L, R>
{
    private:
        L _left;

    public:
        Left(void) : _left() {}

        Left(const L& left) : _left(left) {}

        Left(const Left& other) : _left(other._left) {}

        ~Left() {}

        Left& operator=(const Left& other)
        {
            _left = other._left;
            return *this;
        }

        L left(void) const { return _left; }

        bool isLeft(void) const { return true; }

        R right(void) const { throw IllegalAccessException("The right side is not available!"); }

        bool isRight(void) const { return false; }
};

template <typename L, typename R>
class Right : public Either<L, R>
{
    private:
        R _right;

    public:
        Right(void) : _right() {}

        Right(const R& left) : _right(left) {}

        Right(const Right& other) : _right(other._right) {}

        ~Right() {}

        Right& operator=(const Right& other)
        {
            _right = other._right;
            return *this;
        }

        L left(void) const { throw IllegalAccessException("The left side is not available!"); }

        bool isLeft(void) const { return false; }

        R right(void) const { return _right; }

        bool isRight(void) const { return true; }
};

#endif
