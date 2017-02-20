import os

from flask import Flask
from flask_sqlalchemy import SQLAlchemy

BASE_DIR = os.path.abspath(os.path.dirname(__file__))


class Config:
    SECRET_KEY = 'test'

    SQLALCHEMY_COMMIT_ON_TEARDOWN = True
    SQLALCHEMY_TRACK_MODIFICATIONS = True
    SQLALCHEMY_RECORD_QUERIES = True

    TESTING = True
    DEBUG = True

    db_name = 'data-test.sqlite'

    SQLALCHEMY_DATABASE_URI = 'sqlite:///' + os.path.join(BASE_DIR, db_name)

    def __init__(self, app=None):
        self.app = None

        if app is not None:
            self.init_app(app)

        try:
            os.remove(self.SQLALCHEMY_DATABASE_URI)
        except FileNotFoundError:
            pass

    def init_app(self, app):
        self.app = app
        app.config.from_object(self)


app = Flask(__name__)
config = Config(app)
db = SQLAlchemy(app)
