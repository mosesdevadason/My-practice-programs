#include <cstdio>
#include <cstdlib>

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
    if(nullptr == this->head) {
        std::printf("List is empty!\n");
        return nullptr;
    }
 
    list_node_t *node = this->head, *p = nullptr, *tmp = nullptr;
    do {
        if(0 == index) {
            return node;
        }
        /* Since each node's xor_ptr contains the XOR of the prevous and next
         * node's addresses, XOR of the prevous node's address and the current
         * xor_ptr would give the address of the next node. A ^ (A ^ B) = B. */
        tmp = node;
        node = p ^ node->xor_ptr;
        p = tmp;
        --index;
    }while(node != nullptr);

    return nullptr;
}
