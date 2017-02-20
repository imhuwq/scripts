from sqlalchemy.ext.associationproxy import association_proxy


def my_association_proxy(src, target):
    def create(value):
        target_cls = prox.target_class
        return target_cls(**{target: value})

    prox = association_proxy(src, target, creator=create)
    return prox


from .user import User, Follow
from .post import Post
from .tag import Tag, TagPost

