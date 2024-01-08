class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularLinkedList:
    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            self.head.next = self.head
        else:
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = new_node
            new_node.next = self.head

    def AreEqual(self, cursor1, cursor2):
        StartPos1 = cursor1
        StartPos2 = cursor2

        while True:
            if cursor1.data != cursor2.data:
                return False

            cursor1 = cursor1.next
            cursor2 = cursor2.next

            if cursor1 == StartPos1 and cursor2 == StartPos2:
                return True

            if (cursor1 == StartPos1 and cursor2 != StartPos2) or (cursor1 != StartPos1 and cursor2 == StartPos1):
                return False

    def Main(self, list2):
        i = self.head
        j = list2.head
        StartPos = list2.head

        while True:
            if i.data == j.data and self.AreEqual(i, j):
                return True

            j = j.next

            if j == StartPos:
                return False

def main():
    d1 = [1,2,3,4,5]
    d2 = [5,1,2,32,4]
    l1 = CircularLinkedList()
    l2 = CircularLinkedList()
    for i in d1:
        l1.append(i)
    
    for i in d2:
        l2.append(i)
    
    print(l1.Main(l2))

if __name__ == '__main__':
    main()
