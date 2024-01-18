import unittest

class Q:
    def __init__(self, size=100) -> None:
        self.arr_size = size
        self.arr = [None] * self.arr_size
        self.current_size = 0
        self.first_idx = 0  
    
    def enqueue(self, data):
        if self.get_size() == self.arr_size:
            raise Exception("Queue is full.")
        
        insert_idx = (self.first_idx + self.get_size()) % self.arr_size
        self.arr[insert_idx] = data
        self.current_size += 1
    
    def dequeue(self):
        if self.is_empty():
            raise Exception("Queue is empty.")
        
        to_return = self.arr[self.first_idx]
        self.arr[self.first_idx] = None
        
        self.first_idx = (self.first_idx + 1) % self.arr_size
        self.current_size -= 1
        
        return to_return
    
    def get_size(self):
        return self.current_size
    
    def is_empty(self):
        return self.get_size() == 0
    
    def get_first(self):  
        if self.is_empty():
            raise Exception("Queue is empty.")
        
        return self.arr[self.first_idx]


class TestQueue(unittest.TestCase):
    def test_queue(self):
        q = Q(size=10)
        
        q.enqueue(1)
        self.assertEqual(q.get_size(), 1)
        self.assertEqual(q.get_first(), 1)

        dequeued_item = q.dequeue()
        self.assertEqual(dequeued_item, 1)
        self.assertEqual(q.get_size(), 0)
        
        q.enqueue(2)
        q.enqueue(3)
        self.assertEqual(q.get_size(), 2)
        self.assertEqual(q.get_first(), 2)

        dequeued_item = q.dequeue()
        self.assertEqual(dequeued_item, 2)
        self.assertEqual(q.get_size(), 1)

        self.assertFalse(q.is_empty())
        
        q.dequeue()
        self.assertTrue(q.is_empty())


if __name__ == '__main__':
    unittest.main()