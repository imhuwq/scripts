from app import db


class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String, unique=True)

    author_id = db.Column(db.Integer, db.ForeignKey('user.id'))

    tags = db.relationship('TagPost', backref=db.backref('post'))

    def __repr__(self):
        return "%s object <%s>" % (self.__class__.__name__, self.id)
