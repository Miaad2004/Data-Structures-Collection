from queue import Queue

class Node:
   def __init__(self, data):
      self.left = None
      self.right = None
      self.data = data
      

class Tree:
    def __init__(self):
        self.Q = Queue()
        self.root = None
        
    def build(self, pre_order):
        for new_data in pre_order:
            new_node = Node(new_data)
            
            if self.root == None:
                self.root = new_node
                self.Q.put(new_node)
                continue
            
            # Get The first node in the queue
            curr_node = self.Q.queue[0]
            
            if curr_node.left == None:
                curr_node.left = new_node
            
            elif curr_node.right == None:
                curr_node.right = new_node
                self.Q.get()
            
            # Enqueue the new node
            self.Q.put(new_node)
    
    @staticmethod
    def print_tree(root, level=0, prefix=""):
        if root == None:
            return
        
        print('   ' * level, end="")
        print(prefix, end="")
        print(root.data)
        
        Tree.print_tree(root.left, level + 1, prefix="L:")
        Tree.print_tree(root.right, level + 1, prefix="R:")
    
    def zig_zag(self):
        if self.root is None:
            return
        
        curr_level_stack = []
        next_level_stack = []
        
        print_left_to_right = True
        
        curr_level_stack.append(self.root)
        
        while curr_level_stack:
            popped_node = curr_level_stack.pop()
            
            print(f"{popped_node.data} ", end="")
            
            if print_left_to_right:
                if popped_node.left:
                    next_level_stack.append(popped_node.left)
                
                if popped_node.right:
                    next_level_stack.append(popped_node.right)
            
            else:
                if popped_node.right:
                    next_level_stack.append(popped_node.right)
                
                if popped_node.left:
                    next_level_stack.append(popped_node.left)
            
            
            if len(curr_level_stack) == 0:
                # After printing each level, reverse the printing order
                print_left_to_right = not print_left_to_right
                curr_level_stack, next_level_stack = next_level_stack, curr_level_stack


def main():
    n = int(input())
    pre_order = list(map(int, input().split()))
    
    tree = Tree()
    tree.build(pre_order)
    tree.zig_zag()
    
main()
    

