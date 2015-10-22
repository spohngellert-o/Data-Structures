#ifndef VECTOR_H
#define VECTOR_H


#include <exception>
#include <iostream>

using namespace std;

template <typename T> class Vector{
    /* data: array that holds the data
    capacity: the current max capacity of the vector (length of array)
    size: size of the vector */
    T * data;
    int capacity;
    int size;
public:
    typedef T * iterator;
    typedef const T * const_iterator;
    //Standard constructor, initial capacity of 20
    Vector() {
       data = new T[20];
       capacity = 20;
       size = 0;
    }
    //constructor with initial capacity input
    Vector(int initial){
        data = new T[initial];
        capacity = initial;
        size = 0;
    }
    //Returns the end of the array
    iterator begin() {
        return &data[0];
    }
    //returns the beginning of the array
    iterator end() {
        iterator it = (&data[size]);
        return it;
    }
    //adds a value to the vector
    void add(T value) {
        //If the array needs to be resized
        if(capacity == size) {
            //makes a new array with the capacity doubled
            T * newData = new T[capacity*2];
            for(int i = 0; i < capacity; i++) {
                newData[i] = data[i];
            }
            newData[size] = value;
            data = newData;
            size++;
            capacity = capacity*2;
        }
        else {
            //else it adds the value to the array
            data[size] = value;
            size++;
        }
    }
    //Gets the data at index i
    T get(int i) {
        if(i >= size) {
            cout << "Index out of bounds";
            throw -1;
        }
        else {
            return data[i];
        }
    }
    //removes the data at index i and readjusts
    T remove(int i) {
        if(i >= size) {
            cout << "Index out of bounds";
            throw -1;
        }
        else {
            T ret = data[i];
            for(int dex = i; dex < size - 1; dex++) {
                data[dex] = data[dex + 1];
            }
            size--;
            return ret;
        }
    }
    //gets the length of the vector
    int length() {
        return size;
    }
    //adds a value at an index
    void add(T value, int index) {
        if(index > size) {
            cout << "Index out of bounds";
            throw -1;
        }
        else {
            T temp = value;
            while(index < size) {
                temp = data[index];
                data[index] = value;
                value = temp;
                index++;
            }
            data[index] = value;
            size++;
        }
    }
    //Checks if the value is contained within the vector
    //Needs reworking, == not strong
    bool contains(T value) {
        for(int i = 0; i < size; i++) {
            if(data[i] == value) {
                return true;
            }
        }
        return false;

    }
    //sort, currently does not work.
    void sort(bool (*f)(T, T))
    {
        if(!size <= 1)
        {
            T pivot = this->get(0);
            this->qsort(pivot, f);
        }

    }
    void qsort(T pivot, bool (*f)(T, T))
    {
        Vector <T> * left = new Vector<T>(size);
        Vector <T> * right = new Vector<T>(size);

        for(int i = 1; i < size; i++)
        {
            if(f(pivot, data[i]))
            {
                left->add(data[i]);
            }
            else
            {
                right->add(data[i]);
            }
        }
        left->add(pivot);
        left->sort(*f);
        right->sort(*f);
        combine(left, right);

    }
    //Combines the two vectors into this vector, does not work as is
    void combine(Vector<T> * left, Vector<T> * right)
    {
        int start = 0;
        for(int i = 0; i < left->length(); i++)
        {
            data[i] = left->get(i);
            start = i;
        }
        for(int i = 0; i < right->length(); i++)
        {
            data[i + start] = right->get(i);
        }
    }
};
class indexOut: public std::exception
{
    public:
  virtual const char* what() const throw()
  {
    return "Input index is out of bounds.";
  }
}outOfBounds;
template <typename T> class List {
    public:
    virtual T get(int i) = 0;
};
//Cons class (linked list)
//Needs added functionality for pop and push, plan on representing
//As a stack
template <typename T> class Cons: public List<T>
{
    T first;
    List<T> * rest;
    public:
    Cons(T f, List<T> * rest) {
        first = f;
        this->rest = rest;
    }
    //to get an element of the list
    T get(int i) {
        if(i == 0) {
            return this->first;
        }
        return this->rest->get(i - 1);

    }
};
//End of linked list
template <typename T> class Empty: public List<T>
{
    public:
    T get(int i) {
        cout << "Index out of bounds";
        throw -1;
    }
};
//Anode represents a node in a double linked list
template <typename T> class ANode
{
public:
    ANode<T> * next;
    ANode<T> * prev;
    //Abstract methods to be implemented
    virtual int size()=0;
    virtual T get(int index)=0;
    virtual void push(T d, int index)=0;
    void setNext(ANode<T> * n) {
        this->next = n;

    }
    void setPrev(ANode <T> * p) {
        this->prev = p;
    }
};
//Node is a subclass of Anode, contains data
template <typename T> class Node: public ANode<T>
{
    T data;
    public:
        Node(T d, ANode<T> * n, ANode<T> * p) {
            data = d;
            this->setNext(n);
            this->setPrev(p);
            p->setNext(this);
            n->setPrev(this);
        }
        /*void add(T d, int index) {
            std::cout << "here" << std::endl;
            if(index == 0)
            {
                 Node<T> * added = new Node<T>(d, this->next, this);

            }
            else
            {
               std::cout << "here" << std::endl;
               this->next->add(d, index - 1);
            }
        }*/
        int size(){
            return 1 + this->next->size();
        }
        T get(int index)
        {
            if(index == 0)
            {
                return this->data;
            }
            return this->next->get(index - 1);
        }
        //pushing an element onto the double linked list
        void push(T d, int index)
        {
            if(index == 0)
            {
                Node <T> * added = new Node<T>(d, this, this->prev);
            }
            else
            {
                this->next->push(d, index);
            }
        }
};
//sentinel represents end/beginning of list, contains no data
template <typename T> class Sentinel: public ANode<T>
{

    public:
    Sentinel(ANode<T> * n, ANode<T> * p) {
        this->setNext(n);
        this->setPrev(p);
        p->setNext(this);
        n->setPrev(this);

    }
    Sentinel() {
         this->next = this;
         this->prev = this;
    }
    int size(){
        return 0;
    }
    //Custom methods to push to the back or front of the deque
    void push_back(T d) {
        Node <T> * back = new Node<T>(d, this, this->prev);
    }
    void push_front(T d)
    {
        Node <T> * front = new Node<T>(d, this->next, this);
    }
    T get(int index) {
        cout << "Index out of bounds.";
        throw -1;
    }
    void push(T d, int index)
    {
        if(index == 0)
        {
            Node <T> * added = new Node<T>(d, this, this->prev);
        }
        else
        {
            cout << "Index out of bounds.";
            throw -1;
        }
    }
};

template <typename T> class Deque
{
    Sentinel<T> * header;
    public:

      Deque(Sentinel<T> * head) {
          header = head;
      }
      Deque()
      {
          header = new Sentinel<T>();
      }
      int size() {
          return this->header->next->size();
      }
      void add(T d, int index) {

          this->header->next->add(d, index);
      }
      void push_back(T d){
          this->header->push_back(d);

      }
      void push_front(T d)
      {
          this->header->push_front(d);
      }
      T get(int index) {
          return this->header->next->get(index);
      }
      T push(T d, int index)
      {
          this->header->next->push(d, index);
      }
};

#endif // VECTOR_H
