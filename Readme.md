## TODO 
### Iterator

- [x] iterator
- [x] iterator_traits
  - [x] specialization for pointer and const pointer
- [x] reverse_iterator
  - [x] reverse_iterator::base
  - [x] reverse_iterator::operator*
  - [x] reverse_iterator::operator+
  - [x] reverse_iterator::operator++
  - [x] reverse_iterator::operator+=
  - [x] reverse_iterator::operator-
  - [x] reverse_iterator::operator--
  - [x] reverse_iterator::operator-=
  - [x] reverse_iterator::operator->
  <!-- - [ ] reverse_iterator::operator= c++11 -->
  - [x] reverse_iterator::operator[]
  - [x] relational operator(`==`, `!=`, `>`, `<`, `>=`, `<=`) (**non-member function**)
- [x] __wrap_iter (for vector or random access iterator)
  - [x] default constructor
  - [x] copy constructor
  - [x] conversion constructor
  - [x] destructor(virtual?)
  - [x] base (`return member data(iterator)`)
  - [x] postfix increment operator(`a++`)
  - [x] prefix increment operator(`++a`)
  - [x] postfix decrement operator(`a--`)
  - [x] prefix decrement operator(`--a`)
  - [x] dereference operator(`*`, `->`)
  - [x] index operator(**member function**)
  - [x] relational operator(`==`, `!=`, `>`, `<`, `>=`, `<=`) (**non-member function**)
  - [x] compound assignment operator(`+=`, `-=`)
    - [x] a += n;
    - [x] a -= n;
  - [x] addition operator(`+`)
    - [x] a + n
    - [x] n + a(non-member)
  - [x] substraction operator(`-`)
    - [x] a - n
    - [x] a1 - a2


### Vector

- [ ] constructor
  - [x] default
  - [x] size
  - [x] iterator
    - [ ] forward iterator optimization
  - [x] copy
- [ ] methods(**membef function**)
  - [x] assign
  - [x] at
  - [x] back
  - [x] begin
  - [x] capacity
  - [x] clear
  - [x] empty
  - [x] end
  - [x] erase
  - [x] front
  - [x] get_allocator
  - [ ] insert
    - [ ] push_back
  - [x] max_size
  - [x] operator=
  - [x] operator[]
  - [ ] pop_back
  - [ ] rbegin
  - [ ] rend
  - [x] reserve
  - [ ] resize
  - [x] size
  - [ ] swap
- [ ] methods(**non-member function**)
    - [ ] relational operator(`==`, `!=`, `>`, `<`, `>=`, `<=`) (**non-member function**)
    - [ ] 

### 헷갈리는 것
1. __wrap_iter의 copy constructor로 들어오는 인자에 대해서 is_convertible와 enable_if를 통해 오버로딩을 제한하려는 코드가 있다.
   - 여기서 is_convertible을 어떻게 작성해야 할까?
   - integral_constant를 작성해야 함 -> 이건 또 어떻게?? 

