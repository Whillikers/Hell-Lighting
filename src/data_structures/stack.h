#pragma once

template <typename T>
class Stack {
    public:
        /**
         * Construct a new, empty stack
         */
        Stack() {
            top = nullptr;
            size = 0;
        };
        ~Stack() {
            while (size > 0) {
                delete top->element;
                pop();
            }
        };

        /**
         * Push an item `item` onto the stack
         * @param item the item to add
         */
        void push(T* element) {
            ListNode* node = new ListNode;
            node->element = element;
            node->next = top;
            top = node;

            size++;
        };

        /**
         * Remove and return a pointer to the top item.
         * @return pointer to the item on top, or NULL if stack is empty
         */
        T* pop() {
            if (size == 0) {
                return nullptr;
            } else {
                T* ret = top->element;
                ListNode* toDelete = top;
                top = top->next;
                delete toDelete;
                size--;
                return ret;
            }
        };

        /**
         * Determine whether stack has any elements
         * @return true if stack has size >= 1, false if stack is empty
         */
        bool nonempty() {
            return size > 0;
        };

    private:
        typedef struct ListNode_ {
            T* element;
            struct ListNode_* next;
        } ListNode;

        ListNode* top;
        unsigned int size;
};
