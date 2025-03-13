#include <iostream>

using namespace std;

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(size_t amount);
	Vector(size_t amount, const T& value);
	Vector(const Vector& other);
	Vector<T>& operator=(const Vector& other);
	void push_back(const T& value);
	void pop_back();
	void push_front(const T& value);
	void pop_front();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	size_t size() const;
	bool empty() const;
	void reserve(size_t amount);
	void resize(size_t amount);
	void clear();
	void swap(Vector& dub);
	~Vector();
private:
	T* arr = nullptr;
	size_t capacity_ = 0;
	size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector(size_t amount) : capacity_(amount * 2), size_(amount) {
	arr = static_cast<T*>(::operator new(2 * amount * sizeof(T)));
	for (size_t i = 0; i < size_; i++) {
		new(arr + i) T();
	}
}

template <typename T>
Vector<T>::Vector(size_t amount, const T& value) : capacity_(2 * amount), size_(amount) {
	arr = static_cast<T*>(::operator new(2 * amount * sizeof(T)));
	for (size_t i = 0; i < size_; i++) {
		new(arr + i) T(value);
	}
};

template <typename T>
Vector<T>::Vector(const Vector& other) : capacity_(other.capacity_), size_(other.size_) {
	arr = static_cast<T*>(::operator new(other.capacity_ * sizeof(T)));
	for (size_t i = 0; i < other.size_; i++) {
		new(arr + i) T(other.arr[i]);
	}
};

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (capacity_ == other.capacity_) {
		for (size_t i = 0; i < size_; i++) {
			arr[i] = other.arr[i];
		}
		for (size_t i = 0; size_ < other.size_; i++) {
			new(arr + size_ + i) T(other.arr[i + size_]);
			size_++;
		}
	}
	else {
		Vector<T> tmp(other);
		swap(tmp);
		return *this;
	}
};

template <typename T>
void Vector<T>::push_back(const T& value) {
	if (capacity_ > size_) {
		new(arr + size_) T(value);
		size_++;
	}
	else if (!size_) {
		arr = static_cast<T*>(::operator new(2 * sizeof(T)));
		new(arr) T(value);
		size_ = 1;
		capacity_ = 2;
	}
	else {
		T* new_arr = static_cast<T*>(::operator new(size_ * 2 * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new(new_arr + i) T(arr[i]);
		}
		new(new_arr + size_) T(value);
		for (size_t i = 0; i < size_; i++) {
			arr[i].~T();
		}
		::operator delete(arr);
		arr = new_arr;
		capacity_ = size_ * 2;
		size_++;
	}
};

template <typename T>
void Vector<T>::pop_back() {
	if (!empty()) {
		arr[size_ - 1].~T();
		size_--;
	}
};

template <typename T>
void Vector<T>::push_front(const T& value) {
	if (capacity_ > size_) {
		new(arr + size_) T(arr[size_ - 1]);
		for (size_t i = 1; i < size_; i++) {
			arr[size_ - i] = arr[size_ - i - 1];
		}
		arr[0] = value;
		size_++;
	}
	else if(!size_) {
		arr = static_cast<T*>(::operator new(2 * sizeof(T)));
		new(arr) T(value);
		size_ = 1;
		capacity_ = 2;
	}
	else {
		T* new_arr = static_cast<T*>(::operator new(size_ * 2 * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new(new_arr + i + 1) T(arr[i]);
		}
		new(new_arr) T(value);
		for (size_t i = 0; i < size_; i++) {
			arr[i].~T();
		}
		::operator delete(arr);
		arr = new_arr;
		capacity_ = size_ * 2;
		size_++;
	}
};

template <typename T>
void Vector<T>::pop_front() {
	if (!empty()) {
		for (size_t i = 0; i + 1 < size_; i++) {
			arr[i] = arr[i + 1];
		}
		arr[size_ - 1].~T();
		size_--;
	}
};

template <typename T>
T& Vector<T>::operator[](size_t index) {
	return arr[index];
};

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
	return arr[index];
};

template <typename T>
size_t Vector<T>::size() const {
	return size_;
};

template <typename T>
bool Vector<T>::empty() const {
	return size_ == 0;
};

template <typename T>
void Vector<T>::reserve(size_t amount) {
	if (capacity_ < amount) {
		T* new_arr = static_cast<T*>(::operator new(amount * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new(new_arr + i) T(arr[i]);
		}
		for (size_t i = 0; i < size_; i++) {
			arr[i].~T();
		}
		::operator delete(arr);
		arr = new_arr;
		capacity_ = amount;
	}
};

template <typename T>
void Vector<T>::resize(size_t amount) {
	if (size_ >= amount) {
		while (size_ > amount) {
			pop_back();
		}
	}
	else if(size_ < amount && capacity_ >= amount) {
		for (size_t i = 0; size_ < amount; i++) {
			new(arr + size_ + i) T();
			size_++;
		}
	}
	else {
		T* new_arr = static_cast<T*>(::operator new(amount * 2 * sizeof(T)));
		for (size_t i = 0; i < size_; i++) {
			new(new_arr + i) T(arr[i]);
		}
		for (size_t i = 0; size_ < amount; i++) {
			new(new_arr + size_ + i) T();
			size_++;
		}
		for (size_t i = 0; i < size_; i++) {
			arr[i].~T();
		}
		::operator delete(arr);
		arr = new_arr;
		capacity_ = amount * 2;
	}
};

template <typename T>
void Vector<T>::clear() {
	for (size_t i = 0; i < size_; i++) {
		arr[i].~T();
	}
	::operator delete(arr);
	arr = nullptr;
	capacity_ = 0;
	size_ = 0;
};

template <typename T>
void Vector<T>::swap(Vector& dub) {
	std::swap(arr, dub.arr);
	std::swap(size_, dub.size_);
	std::swap(capacity_, dub.capacity_);
}

template <typename T>
Vector<T>::~Vector() {
	for (size_t i = 0; i < size_; i++) {
		arr[i].~T();
	}
	::operator delete(arr);
}