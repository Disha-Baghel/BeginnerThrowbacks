#include <iostream>

template <typename t>
struct Node{
    t data;
    Node* next=nullptr,*prev=nullptr;
};

template <typename t>
class List{
    Node<t> *start,*end;
    unsigned int size = 0;
public:
    Node<t>* NewNode(t d){
        Node<t>* node = new Node<t>();
        node->data = d;
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    void push_front(t d){
        if(start == nullptr){
            start = end = NewNode(d);
        }
        else{
            Node<t>* temp = start;
            start = NewNode(d);
            start->next = temp;
            temp->prev = start;
        }
        size++;
    }

    void push_back(t d){
        Node<t>* np = NewNode(d);
        if(start == nullptr){
            start = end = np;
        }
        else{
            end->next = np;
            np->prev = end;
            end = np;
        }
        size++;
    }

    void pop_front(){
        if(start == nullptr){
            std::cout<<"Underflow";
        }
        else{
            Node<t>* node = start;
            start = start->next;
            delete node;
        }
        size--;
    }

    void pop_back(){
        if(start == nullptr){
            std::cout<<"Underflow";
        }
        else{
            Node<t>* node = end;
            end = end->prev;
            end->next = nullptr;
            delete node;
        }
    }

    template <typename s>
    friend std::ostream& operator<<(std::ostream& os,List<s>* l);
};

template <typename s>
std::ostream& operator<<(std::ostream& os,List<s>* l){
    Node<s>* temp = l->start;
    while(temp != nullptr){
        os<<temp->data<<' ';
        temp = temp->next;
    }
    return os;
}

int main(){

    List<std::string>* l = new List<std::string>();

    l->push_front("vikram");
    l->push_front("kangotra");
    l->push_back("my ");
    l->push_back("name");
    l->push_back("is");
    l->push_front("200");

    std::cout<<l;
	
    delete l;

    return 0;
}
