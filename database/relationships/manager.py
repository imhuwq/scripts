from flask_migrate import Migrate, MigrateCommand
from flask_script import Manager, Shell

from app import app, db
from model import User, Follow, Post, Tag, TagPost


def make_shell_context():
    return dict(db=db, User=User, Post=Post, Tag=Tag, TagPost=TagPost)


manager = Manager(app)
migrate = Migrate(app, db)
manager.add_command('db', MigrateCommand)

manager.add_command('shell', Shell(make_context=make_shell_context))

if __name__ == '__main__':
    manager.run()
