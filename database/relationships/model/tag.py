from datetime import datetime

from app import db


class Tag(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String, unique=True)
    posts = db.relationship('TagPost', backref=db.backref('tag'))

    def __repr__(self):
        return "%s object <%s>" % (self.__class__.__name__, self.id)


class TagPost(db.Model):
    tag_id = db.Column(db.Integer, db.ForeignKey('post.id'), primary_key=True)
    post_id = db.Column(db.Integer, db.ForeignKey('tag.id'), primary_key=True)

    tag_time = db.Column(db.DateTime, default=datetime.utcnow)

    def __repr__(self):
        return "%s object <tag_id: %s, post_id: %s>" % \
               (self.__class__.__name__, self.tag_id, self.post_id)
