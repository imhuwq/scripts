class Node:
    def __init__(self, val):
        self.val = val
        self.next = None

    def __repr__(self):
        return "%s" % self.val

    @classmethod
    def create_node_list(cls, len):
        if len == 0:
            return None
        root = Node(0)
        node = root
        for i in range(1, len):
            next_node = Node(i)
            node.next = next_node
            node = next_node
        return root


def get_node_list_len(node: Node) -> int:
    if node is None:
        return 0
    return get_node_list_len(node.next) + 1


def get_mid_node(node: Node) -> [Node, None]:
    len = get_node_list_len(node)
    if len < 3:
        return None

    mid_node = node
    for i in range(0, (len + 1) // 2):
        mid_node = mid_node.next
    return mid_node


def cut_mid_node(node: Node) -> [Node, None]:
    len = get_node_list_len(node)
    if len < 3:
        return None

    mid_node = node
    pre_node = mid_node
    for i in range(0, (len + 1) // 2):
        pre_node = mid_node
        mid_node = mid_node.next
    pre_node.next = None
    return mid_node


def reverse_linked_list(node: Node) -> [Node, None]:
    if node is None:
        return None

    cur = node
    pre = None
    nxt = None
    while cur is not None:
        nxt = cur.next
        cur.next = pre
        pre = cur
        cur = nxt

    return pre


def zig_zag(node: Node) -> [Node, None]:
    if node is None:
        return None

    mid = cut_mid_node(node)
    if mid is None:
        return node

    mid = reverse_linked_list(mid)

    root = node
    while mid is not None:
        node_next = node.next
        mid_next = mid.next
        node.next = mid
        mid.next = node_next
        mid = mid_next
        node = node_next
    return root


class Test:
    def test_create_node_list(self):
        n0 = Node.create_node_list(0)
        assert get_node_list_len(n0) == 0

        n1 = Node.create_node_list(1)
        assert get_node_list_len(n1) == 1

        n3 = Node.create_node_list(3)
        assert get_node_list_len(n3) == 3

    def test_get_mid_node(self):
        n0 = Node.create_node_list(0)
        m0 = get_mid_node(n0)
        assert m0 is None

        n1 = Node.create_node_list(1)
        m1 = get_mid_node(n1)
        assert m1 is None

        n2 = Node.create_node_list(2)
        m2 = get_mid_node(n2)
        assert m2 is None

        n3 = Node.create_node_list(3)
        m3 = get_mid_node(n3)
        assert m3 is not None
        assert m3.val == 2

        n4 = Node.create_node_list(4)
        m4 = get_mid_node(n4)
        assert m4 is not None
        assert m4.val == 2

        n5 = Node.create_node_list(5)
        m5 = get_mid_node(n5)
        assert m5 is not None
        assert m5.val == 3

    def test_cut_mid_node(self):
        n0 = Node.create_node_list(0)
        m0 = cut_mid_node(n0)
        assert m0 is None

        n1 = Node.create_node_list(1)
        m1 = cut_mid_node(n1)
        assert m1 is None

        n2 = Node.create_node_list(2)
        m2 = cut_mid_node(n2)
        assert m2 is None

        n3 = Node.create_node_list(3)
        m3 = cut_mid_node(n3)
        assert m3 is not None
        assert m3.val == 2
        assert get_node_list_len(n3) == 2

        n4 = Node.create_node_list(4)
        m4 = cut_mid_node(n4)
        assert m4 is not None
        assert m4.val == 2
        assert get_node_list_len(n4) == 2

        n5 = Node.create_node_list(5)
        m5 = cut_mid_node(n5)
        assert m5 is not None
        assert m5.val == 3
        assert get_node_list_len(n5) == 3

    def test_reverse_node_list(self):
        n0 = Node.create_node_list(0)
        r0 = reverse_linked_list(n0)
        assert r0 is None

        n1 = Node.create_node_list(1)
        r1 = reverse_linked_list(n1)
        assert r1.val == 0
        assert get_node_list_len(r1) == 1

        n2 = Node.create_node_list(2)
        r2 = reverse_linked_list(n2)
        assert r2.val == 1
        assert get_node_list_len(r2) == 2

        n3 = Node.create_node_list(3)
        r3 = reverse_linked_list(n3)
        assert r3.val == 2
        assert get_node_list_len(r3) == 3

        n4 = Node.create_node_list(4)
        r4 = reverse_linked_list(n4)
        assert r4.val == 3
        assert get_node_list_len(r4) == 4

        n5 = Node.create_node_list(5)
        r5 = reverse_linked_list(n5)
        assert r5.val == 4
        assert get_node_list_len(r5) == 5

    def test_zig_zag_reversed_last_half_list(self):
        n0 = Node.create_node_list(0)
        z0 = zig_zag(n0)
        assert z0 is None

        n1 = Node.create_node_list(1)
        z1 = zig_zag(n1)
        assert z1 is not None
        assert z1.val == 0

        n2 = Node.create_node_list(2)
        z2 = zig_zag(n2)
        assert z2 is not None
        assert z2.val == 0
        assert z2.next.val == 1

        n3 = Node.create_node_list(3)
        z3 = zig_zag(n3)
        assert z3 is not None
        assert z3.val == 0
        assert z3.next.val == 2
        assert z3.next.next.val == 1

        n4 = Node.create_node_list(4)
        z4 = zig_zag(n4)
        assert z4 is not None
        assert z4.val == 0
        assert z4.next.val == 3
        assert z4.next.next.val == 1
        assert z4.next.next.next.val == 2

        n5 = Node.create_node_list(5)
        z5 = zig_zag(n5)
        assert z5 is not None
        assert z5.val == 0
        assert z5.next.val == 4
        assert z5.next.next.val == 1
        assert z5.next.next.next.val == 3
        assert z5.next.next.next.next.val == 2

    def run_tests(self):
        self.test_create_node_list()
        self.test_get_mid_node()
        self.test_cut_mid_node()
        self.test_reverse_node_list()
        self.test_zig_zag_reversed_last_half_list()


if __name__ == '__main__':
    test = Test()
    test.run_tests()
