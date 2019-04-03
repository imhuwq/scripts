class Node:
    def __init__(self):
        self.next = None
        self.val = None

    @classmethod
    def from_list(cls, l):
        pre = Node()
        head = pre
        for i in l:
            n = Node()
            n.val = i
            pre.next = n
            pre = n
        return head.next

    @staticmethod
    def to_list(node):
        if node is None:
            return []

        ls = []
        cur = node
        while cur is not None:
            ls.append(cur.val)
            cur = cur.next
        return ls

    def __repr__(self):
        return "->".join(map(str, Node.to_list(self)))


def remove_duplicated_elements(node):
    if node is None:
        return None

    pre = Node()
    origin = pre

    cur = node
    nex = node.next
    last = pre
    delete_cur = False

    while nex is not None:
        if cur.val == nex.val:
            delete_cur = True
            nex = nex.next
        else:
            if not delete_cur:
                pre.next = cur
                pre = cur
                cur = nex
                nex = cur.next
            else:
                cur = nex
                nex = cur.next
                delete_cur = False
    if not delete_cur:
        pre.next = cur
    else:
        pre.next = None

    return origin.next


def generate_list(len):
    result = []
    for i in range(1, len + 1):
        result.append([i])

    pos = 1
    while pos < len:
        temp = []
        for s in result:
            for i in range(s[-1], len + 1):
                ds = s[:]
                ds.append(i)
                temp.append(ds)
        result = temp
        pos += 1
    return result


class Test:
    @staticmethod
    def remove_duplicate(ls):
        vals = []
        for i in ls:
            if ls.count(i) > 1:
                continue
            vals.append(i)
        return vals

    @staticmethod
    def test(ls):
        node = Node.from_list(ls)
        new_node = remove_duplicated_elements(node)
        deduplicated = Test.remove_duplicate(ls)
        try:
            assert deduplicated == Node.to_list(new_node)
        except AssertionError as e:
            print(deduplicated)
            print(Node.to_list(new_node))
            raise e

    @staticmethod
    def run():
        elements_len = 6
        for len in range(elements_len+1):
            lists = generate_list(len)
            for l in lists:
                Test.test(l)


if __name__ == "__main__":
    t = Test()
    t.run()
