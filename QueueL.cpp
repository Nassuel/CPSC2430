/**
 * @file QueueL.h - implementation of QUeue ADT with std::list
 * @author Nassuel Valera
 * @see "Seattle UNiversity, CPSC 2430, Spring 2018"
 */

#pragma once
#include <list>
#include "adt/Queue.h"

/**
 * @class QueueL -implementation of Queue ADT with std::list
 * @param data element type must have 0-arg ctor, copy-ctor
 * 	  and << opeerator to stf::ostream
 */

template <typename T>
class QueueL : public Queue<T> {
public:
	QueueL();
	~QueueL();
	QueueL(const QueueL<T>& other);
	QueueL& operator = (const QueueL<T>& other);
	QueueL(QueueL<T>&& temp);

	const T& peek() const;
	void enqueue(const T& datum);
	void dequeue();
	bool empty();
	void clear();	
	std::ostream& print(std::ostream out ) const;
private:
	std::list<T> qlist;
}

template <typename T>
QueueL<T>::QueueL() : qlist() {
}

template <typename T>
Queue<T>::~QueueL() {
}

template <typename T>
QueueL& QueueL<T>::operator=(const QueueL<t>& other) {
	qlist = other.qlist;
}

template <typename T>
QueueL<T>::QueueL(QueueL<T>&& temp) : qlist() {
	std::swap(qlist, temp.qlist);
}

template <typename T>
QueueL& QueueL<T>::operator=(QueueL<T>&& temp) {
	std::swap(qlist, temp.qlist);
	return *this;
}
