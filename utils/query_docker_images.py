import os
import requests


def parse_authenticate(authenticate):
    rv = dict()
    pairs = authenticate.split(" ", 1)[-1]
    pairs = pairs.split(",")
    for pair in pairs:
        name, value = pair.split("=")
        value = value.strip("\"")
        rv[name] = value
    return rv


def request_docker_api(url, user, password):
    session = requests.Session()

    rsp = session.get(url, verify=False)
    authenticate = rsp.headers["Www-Authenticate"]

    authenticate = parse_authenticate(authenticate)

    realm = authenticate.pop("realm")
    rsp = session.get(realm, params=authenticate, auth=(user, password))
    token = rsp.json()["token"]

    rsp = session.get(url, headers={"Authorization": "Bearer {0}".format(token)}, verify=False)
    return rsp


user = os.environ.get("docker_user", None) or input("docker user: ")
password = os.environ.get("docker_password", None) or input("docker password: ")
target_api = "https://docker.imhuwq.com/v2/_catalog"
rsp = request_docker_api(target_api, user, password)
print(rsp.json())
