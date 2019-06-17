#include <cstdio>
#include <cstdlib>
#include <cstdint>

/**
 * @brief Node structure to be inserted into the list.
 */
typedef struct _list_node_t
{
    /** Data to be stored. */
    int data;
    /** XOR of the addresses of the previous node and next node. */
    void *xor_ptr;
}list_node_t;

/**
 * @brief XOR linked list.
 */
class Xor_linked_list
{
    private:
        /** First node of the list. */
        list_node_t *head;
        /** Last node of the list. */
        list_node_t *tail;
        /** Size of the list. */
        std::size_t size;
        /**
         * @brief Increments the list's size.
         */
        void list_size_inc(void);
        /**
         * @brief Decrements the list's size.
         */
        void list_size_dec(void);
    public:
        /**
         * @brief Constructor.
         */
        Xor_linked_list(void);
        /**
         * @brief Destructor.
         */
        ~Xor_linked_list(void);
        /**
         * @brief Appends the given data to the end of the list.
         * @param[in] data Data to be inserted.
         */
        void list_append(int data);
        /**
         * @brief Gets the list node at the given index.
         * @param[in] index Index of the node to be retrieved.
         * @return Node at index.
         */
        list_node_t * list_get(std::size_t index);
        /**
         * @brief Returns the current size of the list.
         * @return Size of the list.
         */
        std::size_t list_size(void);
};

Xor_linked_list::Xor_linked_list(void)
{
    this->head = nullptr;
    this->size = 0;
}

Xor_linked_list::~Xor_linked_list(void)
{

}

void Xor_linked_list::list_size_inc(void)
{
    ++(this->size);
}

void Xor_linked_list::list_size_dec(void)
{
    --(this->size);
}

std::size_t Xor_linked_list::list_size(void)
{
    return this->size;
}

list_node_t * Xor_linked_list::list_get(std::size_t index)
{
    if (nullptr == this->head) {
        std::printf("List is empty!\n");
        return nullptr;
    }
 
    list_node_t *node = this->head, *p = nullptr, *tmp = nullptr;
    do {
        if (0 == index) return node;
        /* Since each node's xor_ptr contains the XOR of the prevous and next
         * node's addresses, XOR of the prevous node's address and the current
         * xor_ptr would give the address of the next node. A ^ (A ^ B) = B. */
        tmp = node;
        node = (list_node_t *) ((uintptr_t)p ^ (uintptr_t)node->xor_ptr);
        std::printf("Node traversed : %d. Address : %p\n", node->data, node);
        p = tmp;
        --index;
    }while(node != nullptr);

    return nullptr;
}

void Xor_linked_list::list_append(int data)
{
    list_node_t *node = new list_node_t;
    list_node_t *p = nullptr;

    node->data = data;
    std::printf("Inserted %d. Address : %p\n", data, node);

    // List is empty.
    if (nullptr == this->head) {
        this->head = node;
        this->tail = node;
        node->xor_ptr = nullptr;
        return;
    }
    
    /* Since tail is the last node, we XOR nullptr with the xor_pointer to get
     * previous node. */
    p = (list_node_t *) ((uintptr_t)(this->tail->xor_ptr) ^ (uintptr_t)nullptr);
    std::printf("Inserting %d. Previous node address : %p\n", node->data, p);
    // xor_ptr for the new node. Update tail pointer.
    node->xor_ptr = (list_node_t *) ((uintptr_t)p ^ (uintptr_t)nullptr);
    std::printf("Inserted %d. XOR ptr : %p\n", node->data, node->xor_ptr);
    tail = node;
}

int main(int argc, char *argv[])
{
    Xor_linked_list my_list;

    my_list.list_append(10);
    std::printf("Node 0 : %d\n", my_list.list_get(0)->data);
    my_list.list_append(20);
    std::printf("Node 1 : %d\n", my_list.list_get(1)->data);
    my_list.list_append(30);
    std::printf("Node 2 : %d\n", my_list.list_get(2)->data);

    return 0;
}
