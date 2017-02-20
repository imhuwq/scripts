from datetime import datetime

from model import my_association_proxy

from app import db


class Follow(db.Model):
    follower_id = db.Column(db.Integer, db.ForeignKey('user.id'), primary_key=True)
    followed_id = db.Column(db.Integer, db.ForeignKey('user.id'), primary_key=True)

    follow_time = db.Column(db.DateTime, default=datetime.utcnow)

    def __repr__(self):
        return "%s object <follower_id: %s, followed_id: %s>" % \
               (self.__class__.__name__, self.follower_id, self.followed_id)


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String, unique=True)

    # user has one-to-many relationship with post
    posts = db.relationship('Post', backref=db.backref('author'))

    # user has self-reference many-to-many relationship: following <-> followers

    # people who are following you, in the Follow table, you are in the followed side
    follow_followers = db.relationship('Follow', foreign_keys=[Follow.followed_id],
                                       backref=db.backref('followed', lazy='joined'),
                                       cascade='all, delete-orphan')

    # people who you are following, in the Follow table, your are in the follower side
    follow_followeds = db.relationship('Follow', foreign_keys=[Follow.follower_id],
                                       backref=db.backref('follower', lazy='joined'),
                                       cascade='all, delete-orphan')

    # lazy mode in backref is 'join', which means 'join query' which will load all object immediately;
    # if it is set to default 'select', then each access to the related object in the first time
    # will request a individual query;
    # lazy mode in relationship is 'dynamic', which means the query returns a query object which
    # we can carry out further query actions on it, but in this example, we don't need it;
    # casecade 'all' means add all related object to db session automatically when one object is added to db session
    # casecade 'delete-orphan' means delete rows in association table when one of the two side breaks the link

    # use proxy to access followers and followeds directly, skip the association Follow object
    followers = my_association_proxy('follow_followers', 'follower')  # proxy to follow_followers, proxy for follower
    followeds = my_association_proxy('follow_followeds', 'followed')

    def __repr__(self):
        return "%s object <%s>" % (self.__class__.__name__, self.id)

    @classmethod
    def new(cls, name):
        user = User(name=name)
        db.session.add(user)
        db.session.commit()
        return user
