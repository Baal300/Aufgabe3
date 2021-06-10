#ifndef LISTE_H
#define LISTE_H
#include "item.h"
#include "iostream"

using namespace std;

template <class T>
class Liste
{
private:
    Item<T>* m_firstElement;    //Head / Beginning of list
    Item<T>* m_currentElement;  //Position pointer
    Item<T>* m_lastElement;     //End pointer
public:
    Liste(){    //Creates an empty list
        m_firstElement = nullptr;
        m_currentElement = nullptr;
    };

    Item<T>* get() const
    {
        if(m_currentElement != nullptr){
            return m_currentElement;
        } else {
            cerr << "Element doesn't exist.\n";
            return nullptr;
        }
    };

    bool empty()
    {
        if (m_firstElement == nullptr){
            return true;
        }
        else{
            return false;
        }
    };

    void print()
    {
        //Only if the list is not empty print something
        if(m_firstElement != nullptr) {  //using empty() here doesn't work for sume reason
            cout << "******LIST******\n";

            Item<T>* printElement;
            printElement = m_firstElement; //Start at the beginning
            int i{1};

            while(printElement != nullptr){
                cout << "Node " << i << ": " << printElement->m_information;
                if (printElement->m_prevElement != nullptr)
                {
                    cout << " Previous element: " << printElement->m_prevElement->m_information;
                }
                if (printElement->m_nextElement != nullptr)
                {
                    cout << " Next element: " << printElement->m_nextElement->m_information;
                }
                cout << '\n';
                printElement = printElement->m_nextElement;     //Set next node to be printed
                i++;
            }
        }
        else{
            cout << "List is empty!\n";
        }

    };

    bool end()
    {
        if(!empty())
        {
            return m_currentElement == m_lastElement;
        } else {
            cerr << "Can't determine end if list is empty!\n";
        }
    }

    void display()
    {
        Item<T>* temp = new Item<T>;
        temp=m_firstElement;
        while(temp!=NULL)
        {
          cout<<temp->m_information<<"\t";
          temp=temp->m_nextElement;
        }
    }

    void ins(T value)
    {
        Item<T>* newItem = new Item<T>; //Creates new item object
        newItem->m_information = value;
        newItem->m_nextElement = nullptr;


        if(m_firstElement == nullptr) //If list is still empty
        {
            newItem->m_prevElement = nullptr;
            m_firstElement = newItem;
            m_currentElement = newItem;
            m_lastElement = newItem;
        }
        else
        {
            //Sort list
            m_currentElement = m_firstElement;
            while(true)
            {
                if(newItem->m_information < m_currentElement->m_information)
                {
                    newItem->m_prevElement = m_currentElement->m_prevElement;
                    newItem->m_nextElement = m_currentElement;
                    m_currentElement->m_prevElement = newItem;
                    m_currentElement = newItem;       //Insert our new element before the compared element if it's smaller

                    if(m_currentElement->m_prevElement != nullptr){    //If there was a previous element to our compared element it gets the new item as next element
                        m_currentElement->m_prevElement->m_nextElement = m_currentElement;
                    }
                    break;
                }
                if(end()){  //Element is inserted at the end if it's greater than all other elements
                    m_currentElement->m_nextElement = newItem;  //We want to add a node next to our position pointer
                    newItem->m_prevElement = m_currentElement; //Position pointer becomes previous node of new node
                    m_currentElement = newItem; //The new item/node is our position pointer now
                    break;
                }
                m_currentElement = m_currentElement->m_nextElement;  //Check next element
            }

            if(newItem->m_prevElement == nullptr){  //In case the new element got inserted at the beginning
                m_firstElement = newItem;
            }

            if(m_currentElement->m_nextElement == nullptr){ //If the next element of our new element is null, it is our last element
                m_lastElement = m_currentElement;
            }
        }
    }


    void adv()
    {
        if(!empty()){
            if(m_currentElement->m_nextElement != nullptr){
                cout << "***ADVANCE BY ONE POSTION***\n";
                m_currentElement = m_currentElement->m_nextElement;     //Set position pointer to next element
            }
            else{
                cerr << "Couldn't advance further. Position pointer is already at end of list.\n";
            }
        } else {
            cerr << "Can't advance on an empty list!\n";
        }
    };

    void reset()
    {
        m_currentElement = m_firstElement;
    }

    void del()
    {
        try {
            if(m_firstElement == nullptr){
                throw runtime_error("List is already empty!");      //Don't do anything if list is empty
            }
            else if (m_firstElement == m_currentElement && m_currentElement->m_nextElement == nullptr){   //If there is only one element
                m_firstElement = nullptr;       //To avoid dangling pointer first element is nullptr
                delete m_currentElement;        //previous and next should be in this case nullptr as well already
            }
            else if(m_currentElement == m_firstElement){       //If position pointer points to first element/beginning and there are elements after that
                m_firstElement = m_currentElement->m_nextElement;      //Set first element pointer to next element before it gets deleted
                delete m_currentElement;
                m_currentElement = m_firstElement;
                m_firstElement->m_prevElement = nullptr; // First element's prevPointer should be null
            }
            else{
                Item<T>* beforeElement = m_currentElement->m_prevElement;     //New pointer to find out node before position pointer
                beforeElement->m_nextElement = m_currentElement->m_nextElement; //The next element for the node before the deleted element is now set
                delete m_currentElement;
                m_currentElement = beforeElement; //Our position pointer points to the node before the deleted node now
            }
        }  catch (runtime_error e) {
           cerr << e.what() << '\n';
        }
    }

    void menu()
    {
        do{
            int menuSelection;

            //Try and Catch, in case user enters an invalid number
            do{
                try
                {
                    cout << "*************MENU*************\n"
                         << "Please select an option from the menu by entering one of the following numbers\n"
                         << "(1) Get current element\n"
                         << "(2) Empty?\n"
                         << "(3) End?\n"
                         << "(4) Advance one node\n"
                         << "(5) Put position pointer at start\n"
                         << "(6) Insert a node at position pointer\n"
                         << "(7) Delete a node at position pointer\n"
                         << "(8) Print list\n"
                         << "(9) Quit\n"
                         << "\nMenu selection: ";

                    cin >> menuSelection;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //In case we have extraneous inputs

                    if (cin.fail())
                    {
                        cin.clear(); //clears error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad input from stream
                        throw invalid_argument("Enter only valid numbers please!");
                    }
                    else if (menuSelection < 1 || menuSelection > 9)
                    {
                        throw invalid_argument("Please enter a valid number from 1-8!");
                    }

                }
                catch (invalid_argument &invalidNumber)
                {
                    cerr << invalidNumber.what() << '\n';
                    continue;
                }

                break;
            }while(true);

            switch (menuSelection) {
            case 1:
            {
                Item<T>* getElement {get()};
                if(getElement != nullptr){
                    cout << "The current element is: " << getElement->m_information  << '\n';
                }
                break;
            }
            case 2:
                if(empty() == true){
                    cout << "The list is currently empty.\n";
                }
                else{
                    cout << "The list is not empty.\n";
                }
                break;
            case 3:
                if(end()){
                    cout << "The position pointer points to the end of the list.\n";
                }
                else{
                    cout << "The position pointer doesn't point to the end of the list.\n";
                }
                break;
            case 4:
                adv();
                break;
            case 5:
                cout << "Position pointer is set to beginning of list.\n";
                reset();
                break;
            case 6:
                T value;
                cout << "Enter a value to insert: ";
                cin >> value;
                ins(value);
                break;
            case 7:
                del();
                cout << "***NODE DELETED***\n";
                break;
            case 8:
                print();
                break;
            case 9:
                break;
            default:
                cerr << "ERROR\n";
                break;
            }

            //If user enters 6 loop is broken and user quits menu, otherwise menu opens again
            if(menuSelection == 9)
            {
                break;
            }

        }while(true);
    }

    /*~Liste()
    {
        m_currentElement = m_firstElement;
        cout << "Starting to delete list.\n";

        while(m_currentElement != nullptr){ //As long list is not empty the elements get deleted
            delete m_currentElement;    //Debugger stops here
            m_currentElement = m_currentElement->m_nextElement;
        }

        cout << "List was destroyed.\n";
    }*/
};

#endif // LISTE_H
