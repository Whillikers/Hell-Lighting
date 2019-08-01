#pragma once

template <typename T>
class Queue {
    public:
        /**
         * Construct a new, empty queue
         */
        Queue() {
            front = nullptr;
            back = nullptr;
            size = 0;
        };
        ~Queue() {
            while (size > 0) {
                delete front->element;
                pop();
            }
        };

        /**
         * Push an item `item` into the queue (at the back)
         * @param item the item to add
         */
        void push(T* action) {
            ListNode* node = new ListNode;
            node->element = action;
            node->next = nullptr;
            if (size == 0) {
                front = node;
                back = node;
            } else {
                back->next = node;
                back = node;
            }

            size++;
        };

        /**
         * Remove and return a pointer to the first item in the queue.
         * @return pointer to the item on top, or NULL if stack is empty
         */
        T* pop() {
            if (size == 0) {
                return nullptr;
            } else {
                T* ret = front->element;
                ListNode* toDelete = front;
                front = front->next;
                delete toDelete;
                size--;
                return ret;
            }
        };

        /**
         * Determine whether queue has any elements
         * @return true if queue has size >= 1, false if queue is empty
         */
        bool nonempty() {
            return size > 0;
        };

    private:
        typedef struct ListNode_ {
            T* element;
            struct ListNode_* next;
        } ListNode;

        ListNode* front;
        ListNode* back;

        unsigned int size;
};
