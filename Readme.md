## TODO 
### Iterator

- [ ] iterator
- [ ] iterator_traits
  - [ ] specialization for pointer and const pointer
- [ ] reverse_iterator
- [ ] __wrap_iter (for vector or random access iterator)
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
  - [ ] compound assignment operator(`+=`, `-=`)
  - [ ] addition operator(`+`)
  - [ ] substraction operator(`-`)


### Vector

- [ ] constructor
- [ ] methods
  - [ ] operator
    - [ ] assignment oeprator(**member function**)
    - [ ] index operator(**member function**)
    - [ ] relational operator(`==`, `!=`, `>`, `<`, `>=`, `<=`) (**non-member function**)
    - [ ] 
- [ ] iterator
<!-- - [ ]  -->

### 헷갈리는 것
1. __wrap_iter의 copy constructor로 들어오는 인자에 대해서 is_convertible와 enable_if를 통해 오버로딩을 제한하려는 코드가 있다.
   - 여기서 is_convertible을 어떻게 작성해야 할까?
   - integral_constant를 작성해야 함 -> 이건 또 어떻게?? 
