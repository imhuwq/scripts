class A:
    pass


class B:
    pass


class AB(A, B):
    pass


class BA(B, A):
    pass


class C(AB, BA):
    pass
