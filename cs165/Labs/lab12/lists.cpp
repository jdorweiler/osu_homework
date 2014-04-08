int main ()
{
      std::list<int> myList; //declare a list

      int myints[]={1771,7,3,6}; //declare an array of ints

      myList.assign (myints,myints+3);            // assign first 3 to my list

    std::cout << "list contains:";
    for (std::list<int>::iterator it=myList.begin(); it!=myList.end(); it++)
    std::cout << ' ' << *it;
    std::cout << '\n';

    // Swaping Lists

    std::list<int> myList2(5,3); //5 ints with value of 3

    myList.swap(myList2);

    std::cout << "list after swap:";
    for (std::list<int>::iterator it=myList.begin(); it!=myList.end(); it++)
    std::cout << ' ' << *it;
    std::cout << '\n';


      return 0;
}
