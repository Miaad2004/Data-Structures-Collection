from LinkedLists import SinglyLinkedList

class Stack:
    def __init__(self) -> None:
        self.linked_list = SinglyLinkedList()
    
    def push(self, value):
        self.linked_list.append_first(value)

    def pop(self):
        if len(self) == 0:
            raise IndexError("Stack is empty.")
        
        value = self.linked_list[0]
        self.linked_list.remove_first()
        return value

    def peek(self):
        return self.linked_list.head.value

    def is_empty(self):
        return len(self) == 0

    def __getitem__(self, index):
        if index < 0 or index >= len(self):
            raise IndexError("Index out of range.")

        for i, value in enumerate(self):
            if i == index:
                return value

    def __iter__(self):
        return iter(self.linked_list)

    def __len__(self):
        return self.linked_list.length
    
    def __str__(self):
        values = [str(value) for value in self]
        return ", ".join(values)