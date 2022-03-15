#ifndef MAP_HPP
# define MAP_HPP


#include <iostream>
#include <memory>
#include <exception>
#include <iterator>
#include "../utils/make_pair.hpp"

namespace ft
{

    template < class Key, class T, class Compare = std::less<Key>,  
    class Alloc = std::allocator<std::pair<const Key,T> > >    
    class map{

        private:
            typedef struct _map_node{
                ft::pair<Key, T>    *_myPair;
                _map_node           *next;
                _map_node           *begin;
            }               _map_node;
            _map_node   *_myMap;
            size_t   _size;
            _map_node   *_end;
            Compare     _comp;
            _map_node   *_begin;
            
            _map_node  *map_new_end( void )
            {
                _map_node *lst = new _map_node;
                lst->next = NULL;
                lst->_myPair = NULL;
                return lst;
            }

            _map_node  *map_new_begin( void)
            {
                _map_node *lst = new _map_node;
                lst->_myPair =  NULL;
                lst->next = this->_end;
                return lst;
            }

            _map_node  *map_new(Key key, T value)
            {
                _map_node *lst = new _map_node;
                lst->_myPair = new ft::pair<Key, T>();

                *lst->_myPair =  ft::make_pair(key, value);
                lst->begin = this->_end->begin;
                lst->next = this->_end;
                return lst;
            }

            void map_back(_map_node **alst, _map_node *other)
            {
                _map_node *lst;
                _map_node *tmp;

                lst = *alst;
                if (alst == NULL)
                    *alst = other;
                else
                {
                    while (lst->next != this->_end )
                    {   
                        if ((lst->next->_myPair && other->_myPair) && other->_myPair->first < lst->next->_myPair->first)   
                            break ;
                        lst = lst->next;
                    }
                    if (lst->next == this->_end)
                        lst->next = other;
                    else
                    {
                        tmp = lst->next;
                        lst->next = other;
                        other->next = tmp;
                    }
                }
            }
            
        public:

            typedef Alloc												allocator_type;
            typedef size_t												size_type;
            typedef pair< Key, T>					                    value_type;
            typedef Compare					                            key_compare;

            map( void ) 
            {
                this->_end = map_new_end();
                this->_myMap = map_new_begin();
                this->_end->begin = this->_myMap;
                this->_size = 0;
                return ;
            }

            ~map( void ) 
            {
                _map_node *temp = this->_myMap;
                while (temp->next)
                {
                    this->_myMap = this->_myMap->next;
                    if (temp->_myPair)
                        delete temp->_myPair;
                    delete temp;
                    temp = this->_myMap;
                }
                delete temp;
                return ;
            }

            class value_compare{   
                friend class map;
                protected:
                    Compare comp;
                    value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
                public:
                    typedef bool result_type;
                    typedef value_type first_argument_type;
                    typedef value_type second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };

            class iterator : public std::iterator<std::input_iterator_tag, int>{
                public:
                    iterator(void) 
                    {
                        return ;
                    }
                    iterator(_map_node * x) :p(x) 
                    {
                        return ;
                    }

                    iterator & operator=( iterator const & src) 
                    {
                        this->p = src.p;
                        return *this ;
                    }

                    iterator(iterator const & test) :p(test.p) 
                    {
                        return ;
                    }

                    ft::pair<Key, T> & operator*( void ) 
                    {
                        return *this->p->_myPair;
                    }

                    ft::pair<Key, T> * operator->( void )
                    {
                        return this->p->_myPair;
                    }
                    
                    bool operator==( iterator const & it ) const
                    {
                        if ( it.p->_myPair == this->p->_myPair)
                            return true;
                        return false;
                    }

                    bool operator!=( iterator const & ite) const
                    {
                        if (this->p->_myPair == ite.p->_myPair)
                            return false;
                        return true;
                    }

                    iterator operator++(int) 
                    {
                        iterator  temp = *this;
                        ++*this;
                        return temp;
                    }

                    iterator& operator++(void) 
                    {
                        this->p = this->p->next;
                        return *this;
                    }


                    iterator operator--(int) 
                    {
                        iterator  temp = *this;
                        --*this;
                        return temp;
                    }

                    iterator& operator--(void) 
                    {
                        _map_node *temp = this->p->begin ;
                        while (temp->next && temp->next->_myPair != this->p->_myPair)
                        {    
                            temp = temp->next;
                        }
                        this->p = temp;
                        this->p->_myPair = temp->_myPair;
                        return *this;
                    }


                private :
                    _map_node * p;
                    
            };

            class const_iterator : public std::iterator<std::input_iterator_tag, int>{
                public:
                    const_iterator(void) 
                    {
                        return ;
                    }
                    const_iterator(_map_node * x) :p(x)
                    {
                        return ;
                    }

                    const_iterator & operator=( const_iterator const & src) 
                    {
                        this->p = src.p;
                        return *this ;
                    }

                    const_iterator(const_iterator const & test) :p(test.p) 
                    {
                        return ;
                    }

                    T & operator*( void ) const 
                    {
                        return this->p->_myPair->second;
                    }

                    ft::pair<Key, T> * operator->( void )
                    {
                        return this->p->_myPair;
                    }
                    bool operator==( const_iterator const & it ) const
                    {
                        if ( it.p->_myPair == this->p->_myPair)
                            return true;
                        return false;
                    }

                    bool operator!=( const_iterator const & ite) const
                    {
                        if (this->p->_myPair == ite.p->_myPair)
                            return false;
                        return true;
                    }

                    const_iterator operator++(int) 
                    {
                        const_iterator  temp = *this;
                        ++*this;
                        return temp;
                    }

                    const_iterator& operator++(void) 
                    {
                        this->p = this->p->next;
                        return *this;
                    }


                    const_iterator operator--(int) 
                    {
                        const_iterator  temp = *this;
                        
                        --*this;
                        return temp;
                    }

                    const_iterator& operator--(void) 
                    {
                        _map_node *temp = this->p->begin ;
                        while (temp->next && temp->next->_myPair != this->p->_myPair)
                        {    
                            temp = temp->next;
                        }
                        this->p = temp;
                        this->p->_myPair = temp->_myPair;
                        return *this;
                    }


                private :
                    _map_node * p;
                    
            };

            class reverse_iterator : public std::iterator<std::input_iterator_tag, int>{
                public:
                    reverse_iterator(void) 
                    {
                        return ;
                    }
                    reverse_iterator(_map_node * x) :p(x) 
                    {
                        return ;
                    }

                    reverse_iterator & operator=( reverse_iterator const & src) 
                    {
                        this->p = src.p;
                        return *this ;
                    }

                    reverse_iterator(reverse_iterator const & test) :p(test.p) 
                    {
                        return ;
                    }

                    T & operator*( void ) 
                    {
                        return this->p->_myPair->second;
                    }

                    ft::pair<Key, T> * operator->( void )
                    {
                        return this->p->_myPair;
                    }

                    bool operator==( reverse_iterator const & it ) const
                    {
                        if ( it.p->_myPair == this->p->_myPair)
                            return true;
                        return false;
                    }

                    bool operator!=( reverse_iterator const & ite) const
                    {
                        if (this->p->_myPair == ite.p->_myPair)
                            return false;
                        return true;
                    }

                    reverse_iterator operator++(int) 
                    {
                        reverse_iterator  temp = *this;
                        ++*this;
                        return temp;
                    }

                    reverse_iterator& operator++(void) 
                    {
                        _map_node *temp = this->p->begin ;
                        while (temp->next && temp->next->_myPair != this->p->_myPair)
                        {    
                            temp = temp->next;
                        }
                        this->p = temp;
                        this->p->_myPair = temp->_myPair;
                        return *this;
                    }

                    reverse_iterator operator--(int) 
                    {
                        reverse_iterator  temp = *this;
                        --*this;
                        return temp;
                    }

                    reverse_iterator& operator--(void) 
                    {
                        this->p = this->p->next;
                        return *this;
                    }
                   
                private :
                    _map_node * p;
            };

            class const_reverse_iterator : public std::iterator<std::input_iterator_tag, int>{
                public:
                    const_reverse_iterator(void) 
                    {
                        return ;
                    }
                    const_reverse_iterator(_map_node * x) :p(x) 
                    {
                        return ;
                    }

                    const_reverse_iterator & operator=( const_reverse_iterator const & src) 
                    {
                        this->p = src.p;
                        return *this ;
                    }

                    const_reverse_iterator(const_reverse_iterator const & test) :p(test.p) 
                    {
                        return ;
                    }

                    T & operator*( void ) 
                    {
                        return this->p->_myPair->second;
                    }

                    ft::pair<Key, T> * operator->( void )
                    {
                        return this->p->_myPair;
                    }

                    bool operator==( const_reverse_iterator const & it ) const
                    {
                        if ( it.p->_myPair == this->p->_myPair)
                            return true;
                        return false;
                    }

                    bool operator!=( const_reverse_iterator const & ite) const
                    {
                        if (this->p->_myPair == ite.p->_myPair)
                            return false;
                        return true;
                    }

                    const_reverse_iterator operator++(int) 
                    {
                        const_reverse_iterator  temp = *this;
                        ++*this;
                        return temp;
                    }

                    const_reverse_iterator& operator++(void) 
                    {
                        _map_node *temp = this->p->begin ;
                        while (temp->next && temp->next->_myPair != this->p->_myPair)
                        {    
                            temp = temp->next;
                        }
                        this->p = temp;
                        this->p->_myPair = temp->_myPair;
                        return *this;
                    }

                    const_reverse_iterator operator--(int) 
                    {
                        const_reverse_iterator  temp = *this;
                        --*this;
                        return temp;
                    }

                    const_reverse_iterator& operator--(void) 
                    {
                        this->p = this->p->next;
                        return *this;
                    }
                   
                private :
                    _map_node * p;
            };

            iterator    begin( void ) 
            {
                iterator   it(this->_myMap->next);
                return (it);
            }

            iterator     end( void ) 
            {
                _map_node *temp = this->_myMap;
                iterator   it(this->_end);
                return (it);
            }

            const_iterator    begin( void ) const
            {
                const_iterator   it(this->_myMap);
                return (it);
            }

            const_iterator     end( void ) const
            {
                _map_node *temp = this->_myMap;
                const_iterator   it(this->_end);
                return (it);
            }

            const_iterator    cbegin( void ) const
            {
                const_iterator   it(this->_myMap->next);
                return (it);
            }

            const_iterator     cend( void ) const
            {
                _map_node *temp = this->_myMap;
                const_iterator   it(this->_end);
                return (it);
            }

            reverse_iterator    rbegin( void ) 
            {
                _map_node *temp = this->_myMap;

                while( temp->next != this->_end)
                    temp = temp->next; 
                reverse_iterator   it(temp);
                return (it);
            }

            reverse_iterator     rend( void ) 
            {
                reverse_iterator   it(this->_myMap);
                return (it);
            }

            const_reverse_iterator    rbegin( void ) const
            {
                _map_node *temp = this->_myMap;

                while( temp->next != this->_end)
                    temp = temp->next; 
                const_reverse_iterator   it(temp);
                return (it);
            }

            const_reverse_iterator     rend( void ) const
            {
                const_reverse_iterator   it(this->_myMap);
                return (it);
            }

            const_reverse_iterator    crbegin( void ) const
            {
                _map_node *temp = this->_myMap;

                while( temp->next != this->_end)
                    temp = temp->next; 
                const_reverse_iterator   it(temp);
                return (it);
            }

            const_reverse_iterator     crend( void ) const
            {
                const_reverse_iterator   it(this->_myMap);
                return (it);
            }

            map & operator=( const map & src ) 
            {
                this->_myMap = src._myMap;
                this->_size = src._size;
                return *this;
            } 

            T & operator[]( const Key key ) 
            {
                _map_node *temp = this->_myMap->next;
                if (this->_size != 0)
                {
                    
                    for (int i = 0; temp->next != this->_end ; i++)
                    {
                        if (key == temp->_myPair->first)
                            return (temp->_myPair->second);  
                        temp = temp->next;       
                    }
                }
				T a = T();
                _map_node *test = this->map_new(key, a);
                this->map_back(&this->_myMap, test);
                this->_end->begin = this->_myMap;    
                this->_size++;
				return test->_myPair->second;
            }
            
            bool empty( void ) const
            {
                if (this->_size == 0)   
                    return true;
                return false;
            }

            size_type size( void ) const
            {
                return this->_size;
            }

			void display_map(){
				_map_node *temp = this->_myMap;
				while(temp)
				{
					std::cout << "display_map: " << temp << std::endl;
					temp = temp->next;
				}
                std::cout << "display_map end: " <<this->_end << std::endl;
                std::cout << "display_map begin in end: " <<this->_end->begin << std::endl;
				return;
			}

			size_type max_size() const{
				std::allocator<struct _map_node> _alloc;
				return _alloc.max_size() ;
			}

			allocator_type get_allocator() const{
				std::allocator<struct _map_node> _new_alloc;
				return _new_alloc;
			}

            void swap (map& x){
				map temp;

				temp = *this;
				*this = x;
				x = temp;
				//alternative(idk which one is better, need to find out):
				//_map_node *temp;
				//size_type temps;
				//
				//temp = this->_myMap;
				//temps = this->_size;
				//this->_myMap = x._myMap;
				//this->_size = x._size;
				//x._myMap = temp;
				//x._size = temps;
			}

            void clear( void )
            {
                _map_node *temp = this->_myMap;
                while (temp->next)
                {
                    this->_myMap = this->_myMap->next;
                    if (temp->_myPair)
                        delete temp->_myPair;
                    delete temp;
                    temp = this->_myMap;
                }
                delete temp;
                this->_end = map_new_end();
                this->_myMap = map_new_begin();
                this->_end->begin = this->_myMap;
                this->_size = 0; 
                return ;
            }

            size_type count (const Key& k) const
            {
                _map_node *temp = this->_myMap->next;

                while (temp->next != this->_end)
                {    
                    if (temp->_myPair->first == k)
                        return 1;
                    temp = temp->next;
                }
                
                return 0;
            }

            iterator find (const Key& k)
            {
                iterator it = this->begin();
                iterator ite = this->end();
                
                while (it != ite)
                {    
                    
                    if (it->first == k)
                        return it;
                    it++;
                }
                return ite;
            }

            const_iterator find (const Key& k) const
            {
                const_iterator it = this->begin();
                const_iterator ite = this->end();

                while (it != ite)
                {    
                    if (it->first == k)
                        return it;
                    it++;
                }
                return ite;
            }

            ft::pair<iterator, bool> insert(ft::pair<Key, T> add)
            {
                size_type there_is_or_not = this->count(add.first);
                if ( there_is_or_not == 0)
                {
                    this->map_back(&this->_myMap, map_new(add.first, add.second));
                    this->_size++;
                }
                iterator it = this->find(add.first);
                ft::pair<iterator, bool> ret ;
                if (there_is_or_not == 0)
                    ret =  ft::make_pair(it, true);
                else
                    ret =  ft::make_pair(it, false);
                return ret;
            }

            iterator insert( iterator it, ft::pair<Key, T> add)
            {
                _map_node *new_node = NULL;
                _map_node *new_node_seg = NULL;
                iterator its = this->begin();

                if ( it != this->end())
                {
                    it++;
                    if (it == its )
                    {
                        it--;
                        new_node_seg = map_new(it->first, it->second);
                        delete new_node_seg;
                    }
                    else    
                        it--;
                    new_node_seg = map_new(it->first, it->second);
                    delete new_node_seg;
                }
                if ( it != this->end() && ++it == this->begin())
                {
                    iterator last = this->end();
                    new_node_seg = map_new(last->first, last->second);
                } 
                new_node = map_new(add.first, add.second);
                size_type there_is_or_not = this->count(add.first);
                if ( there_is_or_not == 0)
                {
                    this->map_back(&this->_myMap, new_node);
                    this->_size++;
                }
                else
                    delete new_node;
                iterator it_to_send = this->find(add.first);
                return it_to_send;
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                while (first != last)
                {
                    size_type there_is_or_not = this->count(first->first);
                    if ( there_is_or_not == 0)
                    {
                        this->map_back(&this->_myMap, map_new(first->first, first->second));
                        this->_size++;
                    }
                    first++;
                }
                return ;
            }

            void erase(iterator position)
            {
				_map_node *temp;
				temp = this->_myMap;
				while (temp->next->_myPair->first != position->first)
				{
					temp = temp->next;
				}
				_map_node *to_del;
				to_del = temp->next;
				temp->next = temp->next->next;
				delete to_del->_myPair;
				delete to_del;
				this->_size--;
				return;
			}

			size_type erase(const Key &k)
            {
				_map_node *temp;
				_map_node *before;
				temp = this->_myMap->next;
				before = this->_myMap->next;
				temp = temp->next;
				while (temp->next != NULL)
				{
					if(temp->_myPair->first == k)
						break;
					temp = temp->next;
					before = before->next;
				}
				if(!temp->next)
					return 0;
				_map_node *to_del;
				to_del = temp;
				before->next = temp->next;
				delete to_del->_myPair;
				delete to_del;
				this->_size--;
				return 1;
			}

			void erase(iterator first, iterator last)
            {
				_map_node *temp = this->_myMap->next;
				while(temp->next->_myPair->first != first->first)
					temp = temp->next;
				_map_node *to_del = temp->next;
				_map_node *end = this->_myMap->next;
				while (end->_myPair->first != last->first)
					end = end->next;
				temp->next = end;
				_map_node *erased;
				while(to_del->_myPair->first != last->first)
				{
					erased = to_del;
					to_del = to_del->next;
					delete erased->_myPair;
					delete erased;
				}
			}

            key_compare key_comp() const
            {
                return this->_comp;
            }

            value_compare value_comp( void )
            {
                return (key_comp());
            }

            iterator lower_bound (const Key & k)
            {
                iterator it;
                iterator ite = this->end();

                it = this->find(k);
                if (it != ite)
                    return it;
                it = this->begin();
                while (it != ite)
                {
                    if (k < it->first)
                        return it;
                    it++;
                }
                return it;
            }

            const_iterator lower_bound (const Key & k) const
            {
                const_iterator it;
                const_iterator ite = this->cend();

                it = this->find(k);
                if (it != ite)
                    return it;
                it = this->cbegin();
                while (it != ite)
                {
                    if (k < it->first)
                        return it;
                    it++;
                }
                return it;
            }

            iterator upper_bound (const Key & k)
            {
                iterator it;
                iterator ite = this->end();

                it = this->find(k);
                if (it != ite)
                    return ++it;
                it = this->begin();
                while (it != ite)
                {
                    if (k < it->first)
                        return it;
                    it++;
                }
                return it;
            }

            const_iterator upper_bound (const Key & k) const
            {
                const_iterator it;
                const_iterator ite = this->cend();

                it = this->find(k);
                if (it != ite)
                    return ++it;
                it = this->cbegin();
                while (it != ite)
                {
                    if (k < it->first)
                        return it;
                    it++;
                }
                return it;
            }
    };
}

#endif //MAP_HPP