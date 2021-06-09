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
public:
    Liste(){    //Creates an empty list
        m_firstElement = nullptr;
        m_currentElement = nullptr;
    };

    Item<T> get() const
    {
        return *m_currentElement;
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
                cout << "Node " << i << ": " << printElement->m_information << '\n';
                printElement = printElement->m_nextElement;
                i++;
            }
        }
        else{
            cout << "List is empty!\n";
        }




    };

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
            m_firstElement = newItem;
            m_currentElement = newItem;
        }
        else
        {
            m_currentElement->m_nextElement = newItem;  //The item next to our position pointer is the item we want to add to the list
            m_currentElement = m_currentElement->m_nextElement; //The new item is our position pointer now
        }
    }


    void adv()
    {
        m_currentElement = m_currentElement->m_nextElement;     //Set position pointer to next element

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
            else if (m_firstElement == m_currentElement){   //If there is only one element
                m_firstElement = nullptr;       //To avoid dangling pointer first element is nullptr
                delete m_currentElement;
            }
            else{
                Item<T>* beforeElement = m_firstElement;     //New pointer to find out node before position pointer
                while (beforeElement->m_nextElement != m_currentElement) {     //Will head from node to node until the next element of the pointer is the position pointer
                    beforeElement = beforeElement->m_nextElement;
                }
                beforeElement->m_nextElement = m_currentElement->m_nextElement; //The next element for the node before the deleted element is now set
                delete m_currentElement;
                m_currentElement = beforeElement; //Our position pointer points to the node before the deleted node now
            }
        }  catch (runtime_error e) {
           cout << e.what() << '\n';
        }
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
