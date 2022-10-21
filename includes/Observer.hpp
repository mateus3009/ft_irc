#ifndef OBSERVER_HPP
# define OBSERVER_HPP

# include <set>
# include <iostream>

template <typename T>
struct Observer
{
    virtual void handle(T& value) = 0;
};

template <typename T>
class Publisher
{
    private:
        std::set<Observer<T>*> _subscribers;

    public:
        Publisher(void);

        Publisher(const Publisher<T>& other);

        ~Publisher();

        Publisher<T>& operator=(const Publisher<T>& other);

        void subscribe(Observer<T>* observer);

        void unsubscribe(Observer<T>* observer);

        void notify(T value);

};

template <typename T>
Publisher<T>::Publisher(void) : _subscribers() {}

template <typename T>
Publisher<T>::Publisher(const Publisher& other) : _subscribers(other._subscribers) {}

template <typename T>
Publisher<T>::~Publisher() {}

template <typename T>
Publisher<T>& Publisher<T>::operator=(const Publisher<T>& other)
{
    _subscribers = other._subscribers;
    return _subscribers;
}

template <typename T>
void Publisher<T>::subscribe(Observer<T>* observer)
{
    _subscribers.insert(observer);
}

template <typename T>
void Publisher<T>::unsubscribe(Observer<T>* observer)
{
    _subscribers.erase(observer);
}

template <typename T>
void Publisher<T>::notify(T value)
{
    for (typename std::set<Observer<T>*>::iterator it = _subscribers.begin(); it != _subscribers.end(); ++it)
        (*it)->handle(value);
}

#endif
