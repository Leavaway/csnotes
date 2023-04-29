/*
    The data object collection of a linear list is {a1, a2, ... an}, where the type of each element is DataType. 
    Except for the first element a1, each element has exactly one immediate predecessor. 
    Similarly, except for the last element an, each element has exactly one immediate successor. 
    The relationship between data elements is one-to-one.
*/
template<typename T>
class LinearList {
public:
    // insert the element at the specified position.
    virtual void insert(int index, const T& value) = 0;

    // remove element at the specified position
    virtual void remove(int index) = 0;

    // search for value and return the index
    virtual int find(const T& value) const = 0;

    // get the length of linear list
    virtual int length() const = 0;

    // get the element at the specified position.
    virtual const T& get(int index) const = 0;

    // modify the element at the specified position.
    virtual void set(int index, const T& value) = 0;

    // check empty
    virtual bool isEmpty() const = 0;

    // print elements in the linear list
    virtual void printList() const = 0;

    // virtual destructor
    virtual ~LinearList() = default;
};
