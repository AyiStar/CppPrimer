# Notes in Chapter 11

## Chapter 11. Associative Containers

**Associative** and **sequential** containers differ from one another in a fundamental way:  
* Elements in an associative container are stored and retrieved by a **key**.
* Elements in a sequential container are stored and accessed sequentially by their **position** in the container.

Associative containers support efficient **lookup** and **retrieval** by a key.

The two primary associative-container types are **map** and **set**:  
* The elements in a *map* are key-value pairs.
  The key serves as an index into the map, and the value represents the data associated with that index.
* The *set* element contains **only a key**. A set supports efficient **queries** as to whether a given key is present.

We might use a set to hold words that we want to ignore during some kind of text processing.  
A dictionary would be a good use for a map. The word would be the key, and its definition would be the value.

The library provides 8 associative containers, which differ along **3 dimensions**:  
* Each container is a *set* or a *map*.
* Each container requires *unique* key or allows *multiple* keys.
* Each container stores the elements *in order* or *not*.

Here are associative container types:  
* Elements ordered by key:  
    * map: associative array; hold key-value pairs. \<map\>
    * set: container in which the key is the value. \<set\>
    * multimap: map in which a key can appear multiple times. \<map\>
    * multiset: set in which a key can appear multiple times. \<set\>
* Unordered collections:
    * unordered_map: map organized by a hash function. \<unordered_map\>
    * unordered_set: set organized by a hash function. \<unordered_set\>
    * unordered_multimap: hashed map; keys can appear multiple times. \<unordered_map\>
    * unordered_multiset: hashed set; keys can appear multiple times. \<unordered_set\>



### 11.1 Using an Associative Container

A **map** is a collection of key-value pairs, and is often referred to as an *associated array*.  
An associative array is like a "normal" array except that its subscripts don't have to be integers.
Values in a map are found by a key rather than by their position.

A **set** is simply a collection of keys, and is most useful when we simply want to know whether a value is present.

##### Using a *map*

To define a map, we must specify both the *key* and *value* types.  
When we subscript a map, we use a key as the subscript, and we get back the value associated with that key.  
If the key is not already in the map, the subscript operator creates a new element whose key is the subscript and whose value is default.

When we fetch an element from a map, we get an object of **type pair**.  
Briefly, a pair is a template type that holds two (public) data elements named *first* and *second*.  
The pairs used by map have a *first* member that is the key and a *second* member that is the corresponding value.

##### Using a *set*

To define a set, we specify the type of its elements.  

We can list initialize the elements of an associative container.

The *find* member returns an iterator. If the given key is in the set, the iterator refers to that key.
If the element is not found, it returns the off-the-end iterator.



### 11.2 Overview of the Associative Containers

Associative containers support the general container operations,
but do not support the sequential-container position-specific operations.
Moreover, the associative containers do not support the constructors or insert operations that take an element value and a count.

The associative container iterators are **bidirectional**.

#### 11.2.1 Defining an Associative Container

Each of the associative containers defines a default constructor,
which creates an **empty** container of the specified type.  
We can also initialize an associative container as a copy of another container of the same type,
or from a range of values so long as those values can be converted to the type of the container.  
We can also list initialize the elements.

When we list initialize an associative container, the initializers must be convertible to the type in the container.  
When we initialize a *map*, we have to supply both the key and the value, wrapping each key-value pair inside by *curly braces* {*key*, *value*}.


#### 11.2.2 Requirements on Key Type

For the ordered containers, the key type must define a way to **compare** the keys.  
By default, the library uses the \< operator for the key type to compare the keys.

##### Key Types for Ordered Containers

We can also supply our own comparison operation to use in place of \< operator on keys.  
The specified operation must define a *strict weak ordering* over the key type, which we can think of as "less than".  
The comparison function must have the following properties:  
* Two keys cannot both be "less than" each other.
* If k1 is "less than" k2 and k2 is "less than" k3, then k1 must be "less than" k3.
* If there are two keys, and neither key is "less than" the other, then we'll say that those keys are *equivalent*.
  If k1 is equivalent to k2 and k2 is equivalent, then k1 must be equivalent to k3.  
  If two keys are equivalent, the container treats them as equal.
  When used as a key to a map, there will be only on element associated with those keys, and either key can be used to access the corresponding value.
  
##### Using a Comparison Function for the Key Type

The operation type is specified following the element type inside the angle brackets that we use to say which type of container we are defining.  
We supply a particular comparison operation (that must have the same type as we specified inside the angle brackets) as a **constructor argument** when we create a container.

``` C++
bool compareIsbn (const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
```


#### 11.2.3 The *pair* Type

The library type **pair** is defined in the *utility* header.

A *pair* holds two data members. It is a *template* from which we generate specific types.  
We must supply **two** type names when we create a *pair*.

The default pair constructor **value initializes** the data members.  
We can also provide initializers for each member with a list.

The data members of *pair* are **public**, which are named *first* and *second*, respectively.

The library defines only a limited number of operations on *pair*s:  
* pair<T1, T2> p;
  p is a pair with value initialized members of types T1 and T2, respectively.
* pair<T1, T2> p(v1, v2);
  p is a pair with types T1 and T2; the first and second members are initialized from v1 and v2, respectively.
* pair<T1, T2> p = {v1, v2};
  Equivalent to p(v1, v2).
* make_pair(v1, v2):
  Return a *pair* initialized from v1 and v2. The type of the pair is inferred from the types of v1 and v2.
* p.first:
  Return the (public) data member of p named first.
* p.second:
  Return the (public) data member of p named second.
* p1 relop p2:
  Relational operators (\<, \<=, \>, \>=). Relational operators are defined as dictionary ordering.
  p1 \< p2 is true if p1.first < p2.first or !(p2.first \< p1.first) && p1.second \< p2.second.
* p1 == p2 / p1 != p2:
  Two pairs are equal if their first and second members are respectively equal.
  
##### A Function to Create *pair* Objects

``` C++
pair<string, int>
process(vector<string> &v)
{
    // process v
    if (!v.empty())
        return { v.back(), v.back().size() }; // list initialize
    else
        return pair<string, int>(); // explicitly constructed return value
}
```



### 11.3 Operations on Associative Containers

The associative containers define some types:  
* key_type:
  Type of the key for this container type.
* mapped_type:
  Type associated with each key; **map types only**.
* value_type:
  For sets, same as the key_type; for maps, pair\<const key_type, mapped_type\>.  
  The key part is const because we cannot change an element's key.

#### 11.3.1 Associative Container Iterators

When we dereference an iterator, we get a **reference** to a value of the container's **value_type**.

``` C++
// get an iterator to an element in word_count
auto map_it = eord_count.begin();
// *map_it is a reference to a pair<const string, size_t> object
cout << map_it->first; // print the key for this element
cout << " " << map_it->second; // print the value of the element
map_it->first = "new key"; // error: key is const
++map_it->second; // ok: we can change the value through an iterator
```

##### Iterators for *set*s Are *const*

Although the *set* types define both the *iterator* and *const_iterator* types,
both types of iterators give us **read-only** access to the elements in the *set*.

##### Iterating across an Associative Container

The *map* and *set* types provide all the *begin* and *end* operations.
We can use these functions to obtain iterators that we can use to traverse the container.

##### Associative Containers and Algorithms

In general, we **do not** use the generic algorithms with the associative containers.   
* Because the  keys are *const*, we cannot pass associative container iterators to algorithms that write to or reorder container elements.
* Although associative containers can be used with the algorithms that read elements, many of these algorithms *search* the sequence.
  However, it is almost a **bad** idea to use a generic search algorithm because elements in an associative container can be found quickly by their key.
  
In practice, if we do so at all, we use an associative container with the algorithms either as the source sequence or as a destination.


#### 11.3.2 Adding Elements

The *insert* members add one element or a range of elements.  
Because *map* and *set* types contain **unique** keys, inserting an element that is already present has **no effect**.

##### Adding Elements to a *map*

When we *insert* in to a map, we must remember that the element type is a **pair**.

``` C++
// 4 ways to add word to word_count
word_count.insert({word, 1});
word_count.insert(make_pair(word, 1));
word_count.insert(pair<string, size_t>(word, 1));
word_count.insert(map<string, size_t>::value_type(word, 1));
```

##### Testing the Return from *insert*

The value returned by *insert* (or *emplace*) depends on the container type and the parameters.  
For the containers that have *unique* keys, the versions of *insert* and *emplace* that add a single element return a *pair* that lets us know whether the insertion happened.
* The *first* member of the *pair* is an iterator to the element with the given key.
* The *second* is a *bool* indicating whether that element was inserted (true), or was already there (false).

##### Adding Elements to *multiset* or *multimap*

Because keys in a *multi* container need not be unique, *insert* on these types **always** inserts an element.


#### 11.3.3 Erasing Elements

The associative containers define 3 versions of *erase*:  
* c.erase(k):
  Remove every element with key k from c. Return size_type indicating the number of elements removed.
* c.erase(k):
  Remove the element denoted by the iterator p from c.
  p must refer to an actual element in c; it must not be equal to c.end().
  Return an iterator to the element after p or c.end() if p denotes the last element in c.
* c.erase(b, e):
  Remove the elements in the range denoted by the iterator pair b, e. Return e.
  

#### 11.3.4 Subscripting a *map*

The *map* and *unordered_map* containers provide the **subscript operator** and a corresponding **at** function:  
* c\[k\]:
  Return the element with key k; if k is not in c, **add** a new, value-initialized element with key k.
* c.at(k):
  **Checked** access to the element with key k; **throw** an out_of_range exception if k is not in c.

Because the subscript operator might insert an element, we may use subscript only on a *map* that is **not const**.

##### Using the Value Returned from a Subscript Operation

When we subscript a *map*, we get a **mapped_type** object instead of an element type (i.e. *pair*).

Sometimes we only want to know whether an element is present and *do not* want to add the element if it is not.
In such cases, we must not use the subscript operator.


#### 11.3.5 Accessing Elements

The associative containers provide various ways to find a given element:  
* c.find(k):
  Return an iterator to the (first) element with key k, or the off-the-end iterator if k is not in the container.
* c.count(k):
  Return the number of elements with key k.
  For the containers with unique keys, the result is always zero or one.
* c.lower_bound(k):
  Return an iterator to the first element with key not less than k.
  Not valid for the unordered containers.
* c.upper_bound(k):
  Return an iterator to the first element with key greater than k.
  Not valid for the unordered containers.
* c.equal_range(k):
  Return a *pair* of iterators denoting the elements with key k.
  If k is not present, both members are c.end().

##### Using *find* Instead of Subscript for *map*s.

Using a subscript has an important side effect:
If that key is not already in the *map*, then subscript inserts an element with that key.  
Sometimes, we cannot use the subscript only to determine whether an element is present. In such cases, we should use *find*.

##### Finding Elements in a *multimap* or *multiset*

When a *multimap* or *multiset* has multiple elements of a given key, those elements will be **adjacent** within the container.  
We are **guaranteed** that iterating across a *multimap* or *multiset* returns all the elements with a given key in sequence.

``` C++
string search_item ("Alain de Botton"); // author we'll look for
auto entries = authors.count(search_item); // number of elements
auto iter = authors.find(search_item); // first entry for this author
// loop through the number of entries there are for this author
while(entries) {
    cout << iter->second << endl; // print each title
    ++iter; // advance to the next title
    --entries; // keep track of how many we've printed
}
```

##### A Different, Iterator-Oriented Solution

* The iterator returned by *lower_bound* will refer to the **first** instance of that key.
* The iterator returned by *upper_bound* will refer just **after the last** instance of the key.
* If the element is not in the *multimap*, then *lower_bound* and *upper_bound* will return equal iterators;
  both will refer to the point at which the key can be inserted without disrupting the order.

``` C++
for (auto beg = authors.lower_bound(serach_item),
          end = authors.upper_bound(search_item);
     beg != end; ++beg)
    cout << beg->second << endl; // print each title
```

##### The *equal_range* Function

*equal_range* takes a key and returns a *pair* of iterators.  
* If the key is present, then the first iterator refers to the first instance of the key and the second iterator refers one past the last instance of the key.
* If no matching element is found, then both the first and second iterators refer to the position where this key can be inserted.

``` C++
for (auto pos = authors.equal_range(search_item);
     pos.first != pos.second; ++pos.first)
    cout << pos.first->second << endl; // print each line
```


#### 11.3.6 A Word Transformation Map

See EXM11_3.



### 11.4 The Unordered Containers

Rather than using a comparison operation to organize the elements,
*unordered container*s use a **hash** function and the key type's == operator.

Although hashing gives better average case performance in principle,
achieving good result in practice often requires a fair bit of performance testing and tweaking.  
So, it is usually easier to use an ordered container.

##### Using an Unordered Container

Aside from operations that *manage the hashing*, the unordered containers provide the **same** operations as the ordered containers.

##### Managing the Buckets

The unordered containers are organized as a collection of **buckets**, each of which holds zero or more elements.
These containers use a *hash* function to map elements to buckets.

The performance of an unordered container depends on the quality of its hash function and the number and size of its buckets.

A hash function is allowed to map elements with different keys to the same buckets.
When a bucket holds several elements, those elements are searched sequentially to find the one we want.

Here are a set of functions that let us manage the buckets:  
* Bucket Interface:  
    * c.bucket_count():
      Number of buckets in use.
    * c.max_bucket_count():
      Largest number of buckets this container can hold.
    * c.bucket_size(n):
      Number of elements in the nth bucket.
    * c.bucket(k):
      Bucket in which elements with key k would be found.
* Bucket Iteration:
    * local_iterator:
      Iterator type that can access elements in a bucket.
    * const_local_iterator:
      *const* version of the bucket iterator.
    * c.begin(n), c.end(n):
      Iterator to the first, one past the last element in bucket n.
    * c.cbegin(n), c.cend(n):
      Return const_local_iterator.
* Hash Policy:  
    * c.load_factor():
      Average number of elements per bucket. Return *float*.
    * c.max_load_factor():
      Average bucket size that c tries to maintain. c adds buckets to keep *load_factor* <= *max_load_factor*. Return float.
    * c.rehash(n):
      Reorganize storage so that *bucket_count* \>= n and *bucket_count* \> *size* / *max_load_factor*.
    * c.reserve(n):
      Reorganize so that c can hold n elements without a rehash.
  
##### Requirement on Key Type for Unordered Containers

By default, the unordered containers use the **==** operator on the key type to compare elements.  
They also use an object of type *hash<key_type> to generate the hash code for each element.

The library supplies versions of the **hash** template for the built-in types, including pointers.  
It also defines *hash* for some of the library types, including *string*s and the smart pointer types.  
Thus, we can **directly** define unordered containers whose key is one of the types above.

However, we **cannot** directly define an unordered container that uses a oue own class types for it key type.  
Instead, we must supply our own version of the *hash* template.
We can supply functions to replace both the == operator and to calculate a hash code.

``` C++
size_t hasher (const Sales_data &sd)
{
    return hash<string>() (sd.isbn());
}

bool eqOp (const Sales_data &lhs, ocnst Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

using SD_multiset = unordered_multiset<Sales_data, decltype(hasher)*, decltype(eqOp)*>;
// arguments are the bucket size and pointers to the hash function and equality operator
SD_multiset bookstore(42, hasher, eqOp);
```

We can override just the hash function if our class has its own == operator.