import unittest

class Node:
    def __init__(self, value, next_node=None):
        self.value = value
        self.next = next_node

class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0

    def append(self, value):
        self.append_first(value)

    def append_range(self, values):
        for value in values:   
            self.append_last(value)

    def append_first(self, value):
        if self.length == 0:
            new_node = Node(value)
            self.head = new_node
            self.tail = new_node
        else:
            new_node = Node(value, next_node=self.head)
            self.head = new_node

        self.length += 1

    def append_last(self, value):
        if self.length == 0:
            self.append_first(value)
        else:
            new_node = Node(value, next_node=None)
            self.tail.next = new_node
            self.tail = new_node

            self.length += 1

    def append_at(self, value, index):
        if index < 0 or index >= self.length:
            raise IndexError("Index out of range.")

        if self.length == 0:
            self.append_first(value)
            return

        previous = self.head
        current = self.head
        i = 0
        while current:
            if i == index:
                new_node = Node(value, next_node=current)
                previous.next = new_node
                break

            i += 1
            previous = current
            current = current.next

        self.length += 1
    
    def remove_first(self):
        self.remove_at(0)
    
    def remove_last(self):
        self.remove_at(self.length - 1)

    def remove_at(self, index):
        if index < 0 or index >= self.length:
            raise IndexError("Index out of range.")

        if self.length == 0:
            return

        elif self.length == 1:
            self.head = None
            self.tail = None

        elif index == 0:
            self.head = self.head.next

        else:
            previous = self.head
            current = self.head
            i = 0
            while current:
                if i == index:
                    previous.next = current.next
                    break

                i += 1
                previous = current
                current = current.next

        self.length -= 1

    def find(self, target):
        for i, value in enumerate(self):
            if target == value:
                return i

        return -1

    def __getitem__(self, index):
        if index < 0 or index >= self.length:
            raise IndexError("Index out of range.")

        for i, value in enumerate(self):
            if i == index:
                return value

    def __iter__(self):
        current = self.head
        while current:
            yield current.value
            current = current.next

    def __len__(self):
        return self.length
    
    def __str__(self):
        values = [str(value) for value in self]
        return " -> ".join(values)
    
    def reverse(self, node):        
        if node == None:
            node = self.head
        
        if node.next == None:
            self.head = node
            return

        self.reverse(node.next)
        
        node.next.next = node
        node.next = None


class TestLinkedLists(unittest.TestCase):

    def test_singly_linked_list(self):
        linked_list = SinglyLinkedList()

        initial_data = [56, 45, 12, 13, 52, 'test']
        linked_list.append_range(initial_data)
        self.assertEqual(str(linked_list), "56 -> 45 -> 12 -> 13 -> 52 -> test")

        linked_list.append_first("first")
        self.assertEqual(str(linked_list), "first -> 56 -> 45 -> 12 -> 13 -> 52 -> test")

        linked_list.remove_first()
        self.assertEqual(str(linked_list), "56 -> 45 -> 12 -> 13 -> 52 -> test")

        linked_list.append_last("last")
        self.assertEqual(str(linked_list), "56 -> 45 -> 12 -> 13 -> 52 -> test -> last")

        linked_list.remove_last()
        self.assertEqual(str(linked_list), "56 -> 45 -> 12 -> 13 -> 52 -> test")

        linked_list.append_at("at2", 2)
        self.assertEqual(str(linked_list), "56 -> 45 -> at2 -> 12 -> 13 -> 52 -> test")

        linked_list.remove_at(2)
        self.assertEqual(str(linked_list), "56 -> 45 -> 12 -> 13 -> 52 -> test")

        self.assertEqual(linked_list.find('test'), 5)
        self.assertEqual(len(linked_list), 6)
        self.assertEqual(linked_list[3], 13)
        

if __name__ == '__main__':
    unittest.main()