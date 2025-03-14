# My_Vector
## Методы
### Конструкторы
- Vector() = default;
- Vector(size_t amount);
- Vector(size_t amount, const T& value);
- Vector(const Vector& other);
### Деструктор
- ~Vector();
## operator=
- Vector<T>& operator=(const Vector& other);
### element access methods
- void push_back(const T& value);
- void pop_back();
- void push_front(const T& value);
- void pop_front();
- T& operator[](size_t index);
- const T& operator[](size_t index) const;
### Capacity
- size_t size() const;
- bool empty() const;
### Modifiers
- void reserve(size_t amount);
- void resize(size_t amount);
- void clear();
- void swap(Vector& dub);
