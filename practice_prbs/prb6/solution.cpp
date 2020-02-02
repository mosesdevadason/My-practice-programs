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
} list_node_t;

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
    size_t size;
    /**
     * @brief Increments the list's size.
     */
    void list_size_inc(void);
    /**
     * @brief Decrements the list's size.
     */
    void list_size_dec(void);
    /**
     * @brief Gets the node at the given index along with the previous and
     *        next nodes.
     *
     * @param[in] index Index of the node.
     * @param[out] p Previous node.
     * @param[out] q Next node.
     *
     * @return Node at index.
     */
    list_node_t* _list_get(size_t index, list_node_t **p, list_node_t **q);
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
    list_node_t* list_get(size_t index);
    /**
     * @brief Deletes the node at index.
     * @param[in] index Index to be deleted.
     */
    void list_delete(size_t index);
    /**
     * @brief Destroys the complete list.
     */
    void list_destroy(void);
    /**
     * @brief Returns the current size of the list.
     * @return Size of the list.
     */
    size_t list_size(void);
};

Xor_linked_list::Xor_linked_list(void)
{
    this->head = nullptr;
    this->size = 0;
}

Xor_linked_list::~Xor_linked_list(void)
{
    this->list_destroy();
}

void Xor_linked_list::list_size_inc(void)
{
    ++(this->size);
}

void Xor_linked_list::list_size_dec(void)
{
    --(this->size);
}

size_t Xor_linked_list::list_size(void)
{
    return this->size;
}

list_node_t* Xor_linked_list::_list_get(size_t index, list_node_t **p,
                                        list_node_t **n)
{
    if (nullptr == this->head) {
        std::printf("List is empty!\n");
        return nullptr;
    }

    list_node_t *node = this->head, *tmp = nullptr;
    *p = nullptr;
    *n = nullptr;
    do {
        if (0 == index) {
            // Get the next node to return.
            *n = (list_node_t*)((uintptr_t)node->xor_ptr ^ (uintptr_t)*p);
            return node;
        }
        /* Since each node's xor_ptr contains the XOR of the prevous and next
         * node's addresses, XOR of the prevous node's address and the current
         * xor_ptr would give the address of the next node. A ^ (A ^ B) = B. */
        tmp = node;
        node = (list_node_t*)((uintptr_t)*p ^ (uintptr_t)node->xor_ptr);
        //std::printf("Node traversed : %d. Address : %p\n", node->data, node);
        *p = tmp;
        --index;
    } while (node != nullptr);

    return nullptr;

}

list_node_t* Xor_linked_list::list_get(size_t index)
{
    list_node_t *p = nullptr, *n = nullptr;

    return this->_list_get(index, &p, &n);
}

void Xor_linked_list::list_delete(size_t index)
{
    list_node_t *p = nullptr, *n = nullptr, *node = nullptr;
    list_node_t *pp = nullptr, *nn = nullptr;

    node = this->_list_get(index, &p, &n);
    if (p != nullptr) {
        /* pp is the node previous to p. This can be obtained by XORing address
         * of current node with xor ptr of p. */
        pp = (list_node_t*)((uintptr_t)p->xor_ptr ^ (uintptr_t)node);
        // Re-calculate XOR_ptr of p.
        p->xor_ptr = (list_node_t*)((uintptr_t)pp ^ (uintptr_t)n);
    }
    if (n != nullptr) {
        /* nn is the node next to n. This can be obtaned by XORing the address
         * of current node and xor_ptr of n. */
        nn = (list_node_t*)((uintptr_t)node ^ (uintptr_t)n->xor_ptr);
        // Re-calculate XOR_ptr of n.
        n->xor_ptr = (list_node_t*)((uintptr_t)p ^ (uintptr_t)nn);
    }
    if (this->head == node)
        this->head = n;
    if (this->tail == node)
        this->tail = p;

    delete node;

    this->list_size_dec();
}

void Xor_linked_list::list_destroy(void)
{
    while (this->list_size() != 0) {
        this->list_delete(0);
    }
}

void Xor_linked_list::list_append(int data)
{
    list_node_t *node = new list_node_t;
    list_node_t *p = nullptr;

    node->data = data;

    // List is empty.
    if (nullptr == this->head) {
        this->head = node;
        this->tail = node;
        node->xor_ptr = nullptr;
        this->list_size_inc();
        return;
    }

    /* Since tail is the last node, we XOR nullptr with the xor_pointer to get
     * previous node. */
    p = (list_node_t*)((uintptr_t)(this->tail->xor_ptr) ^ (uintptr_t)nullptr);
    // Update XOR ptr of the current tail.
    this->tail->xor_ptr = (list_node_t*)((uintptr_t)p ^ (uintptr_t)node);
    // xor_ptr for the new node. Update tail pointer.
    node->xor_ptr = (list_node_t*)((uintptr_t)this->tail ^ (uintptr_t)nullptr);
    this->tail = node;

    this->list_size_inc();
}

int main(int argc, char *argv[])
{
    Xor_linked_list my_list;

    my_list.list_append(10);
    my_list.list_append(20);
    my_list.list_append(30);
    my_list.list_append(40);
    my_list.list_append(50);
    my_list.list_append(60);
    my_list.list_append(70);
    my_list.list_append(80);
    my_list.list_append(90);

    for (size_t ix = 0; ix < my_list.list_size(); ++ix) {
        std::printf("Node %lu : %d\n", ix, my_list.list_get(ix)->data);
    }

    std::printf("Deleted node at 2nd position!\n");
    my_list.list_delete(2);
    for (size_t ix = 0; ix < my_list.list_size(); ++ix) {
        std::printf("Node %lu : %d\n", ix, my_list.list_get(ix)->data);
    }

    std::printf("Deleted node at 0th position!\n");
    my_list.list_delete(0);

    for (size_t ix = 0; ix < my_list.list_size(); ++ix) {
        std::printf("Node %lu : %d\n", ix, my_list.list_get(ix)->data);
    }

    std::printf("Deleted node at last position!\n");
    my_list.list_delete(my_list.list_size() - 1);

    for (size_t ix = 0; ix < my_list.list_size(); ++ix) {
        std::printf("Node %lu : %d\n", ix, my_list.list_get(ix)->data);
    }

    std::printf("Inserted node with data 200\n");
    my_list.list_append(200);
    for (size_t ix = 0; ix < my_list.list_size(); ++ix) {
        std::printf("Node %lu : %d\n", ix, my_list.list_get(ix)->data);
    }

    return 0;
}
