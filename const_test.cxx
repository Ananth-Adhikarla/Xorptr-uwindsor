#define CXX_XOR_PROJECT_USE_REINTERPRET_CAST
//#define CXX_XOR_PROJECT_USE_Uconst intPTR_T

#include "dllist.hxx"
#include <iostream> 
#include <string> 
#include <initializer_list>

int main() {

    // default constructed
    dllist<const int> dl;

    // testing (size, val) constructor
    std::cout << "size-val constructor test: ";
    dllist<const int> dl_size_val(3U, int{5});
    for (auto i = dl_size_val.begin(); i != dl_size_val.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    // testing list initialized constructor
    std::cout << "list initialized constructor test: ";
    dllist<const int> dl_list_init{ {1, 2, 3, 4, 5, 6} };
    for (auto i = dl_list_init.begin(); i != dl_list_init.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    // testing copy constructor
    std::cout << "copy constructor test: ";
    dllist<const int> dl_copy{dl_list_init};
    for (auto i = dl_copy.begin(); i != dl_copy.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    // testing move constructor
    std::cout << "move constructor test: ";
    dllist<const int> dl_move{ dllist<const int>{ {1, 2, 3, 4, 5} } };
    for (auto i = dl_move.begin(); i != dl_move.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing copoy operator =
    std::cout << " = copy test: ";
    dllist<const int> dl_equal = dl_move;
    for (auto const& e : dl_equal) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing move operator =
    std::cout << " = move test: ";
    dllist<const int> dl_equal_move = dllist<const int>{ {1, 2, 3, 4, 5} };
    for (auto const& e : dl_equal_move) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing assign with initializer list
    std::cout << "assign with initializer list test: ";
    dllist<const int> dl_assign_init_list;
    dl_assign_init_list.assign( {1, 2, 3} );
    for (auto const& e : dl_assign_init_list) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing assign with size, val
    std::cout << "assign with size, val: ";
    dllist<const int> dl_assign_size_val;
    dl_assign_size_val.assign(3U, 3);
    for (auto const& e : dl_assign_size_val) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing assign with iterators
    std::cout << "assign with iter: ";
    dllist<const int> dl_assign_iter;
    dl_assign_iter.assign(dl_assign_size_val.begin(), dl_assign_size_val.end());
    for (auto const& e : dl_assign_iter) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

     //testing emplace front, back
    std::cout << "emplace: ";
    dl_assign_iter.emplace_front(234);
    dl_assign_iter.emplace_back(93786293);
    for (auto const& e : dl_assign_iter) {
        std::cout << e << " ";
    }
    std::cout << std::endl <<std::endl;

    //testing empty()
    dllist<const int> e;
    std::cout << "testing empty(): "
            << e.empty()
            << std::endl
            << std::endl;

    //testing size()
    dllist<const int> size_test{ {1, 2, 3, 4, 5} };
    std::cout << "testing size(): "
            << size_test.size()
            << std::endl
            << std::endl;

    //testing max_size()
    dllist<const int> max_size_test{ {1, 2, 3, 4, 5} };
    std::cout << "testing max_size(): "
            << max_size_test.max_size()
            << std::endl
            << std::endl;

    //testing front()
    dllist<const int> front_test{ {2, 1, 3, 4, 5} };
    std::cout << "testing front(): "
            << front_test.front()
            << std::endl
            << std::endl;

    //testing clear()
    dllist<const int> clear_test { {3, 2, 1, 4 } };
    std::cout << "before clear: " << clear_test.size() << std::endl;
    clear_test.clear();
    std::cout << "after clear: " << clear_test.size() << std::endl
            << std::endl;

    //testing insert()
    dllist<const int> insert_test { {3, 2, 1, 4 } };
    std::cout << "before insert 1: ";
    for (auto const& e : insert_test) {
        std::cout << e << " ";
    }
    std::cout <<std::endl;
    insert_test.insert(insert_test.begin(), 234234);
    std::cout << "after insert 1: ";
    for (auto const& e : insert_test) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    insert_test.insert(insert_test.begin(), front_test.begin(), front_test.end());
    std::cout << "after insert 2: ";
    for (auto const& e : insert_test) {
        std::cout << e << " ";
    }
    std::cout << std::endl << std:: endl;

    // testing erase()
    dllist<const int> erase_test { {3, 2, 1, 4 } };
    std::cout << "before erase: ";
    for (auto const& e : erase_test) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    auto it_2 = erase_test.begin();
    it_2++;
    erase_test.erase(it_2);
    std::cout << "after erase: ";
    for (auto const& e : erase_test) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    erase_test.erase(erase_test.begin(), erase_test.end());
    std::cout << "after erase 2: ";
    for (auto const& e : erase_test) {
        std::cout << e << " ";
    }
    std::cout << std::endl << std::endl;

    dllist<const int> b1 { {1, 2, 3, 4, 5} };
    dllist<const int> b2 { {1, 2, 3, 4, 5} };
    auto b1_iter = b1.begin();
    auto b2_iter = b1.begin();

    std::cout << "DLLIST COMPARE" << std::endl;
    std::cout << "equal: " << (b1 == b2) << std::endl;
    std::cout << "not equal: " << (b1 != b2) << std::endl;
    std::cout << "less than: "  << (b1 < b2) << std::endl;
    std::cout << "less or equal:  " << (b1 <= b2) << std::endl;
    std::cout << "greater than: " << (b1 > b2) << std::endl;
    std::cout << "greater or equal: "  << (b1 >= b2) << std::endl;
    std::cout << std::endl;

    std::cout << "DLLIST ITER COMPARE" << std::endl;
    std::cout << "equal: " << (b1_iter == b2_iter) << std::endl;
    std::cout << "not equal: " << (b1_iter != b2_iter) << std::endl;


    



    // testing iterator initialized constructor
    std::cout << "iterator initiailized constructor test: ";
    dllist<const int> dl_iter_init{dl_list_init.begin(), dl_list_init.end()};
    for (auto i = dl_iter_init.begin(); i != dl_iter_init.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    // push_back, push_front test
    int s;
    while(std::cin >> s) { 
        dl.push_back(s);
        dl.push_front(s); 
    }

    // push_front, push_back move tests
    std::cout << "push_front, push_back move tests: ";
    dl.push_front(20);
    dl.push_back(30);
    for (auto i = dl.begin(); i != dl.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;


    // forward prefix iteration test
    std::cout << "dllist forward prefix iteration (before popping): ";
    for (auto i = dl.begin(); i != dl.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    // backward prefix iteration test
    std::cout << "dllist backward prefix iteration (before popping): ";
    for (auto i = dl.rbegin(); i != dl.rend(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl <<std::endl;

    //pop_front, pop_back test
    dl.pop_front();
    dl.pop_back();

    //forward postfix iteration test
    std::cout << "dllist forward postfix iteration (after popping): ";
    for (auto i = dl.begin(); i != dl.end(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl << std::endl;

    // backward postfix iteration test
    std::cout << "dllist backward postfix iteration (after popping): ";
    for (auto i = dl.rbegin(); i != dl.rend(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl << std::endl;
}