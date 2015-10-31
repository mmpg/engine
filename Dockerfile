# This Dockerfile is intended for development purposes only
FROM mmpg/base:latest
MAINTAINER Héctor Ramón Jiménez <hector0193@gmail.com>

RUN apt-get update && apt-get install -y cmake

ADD . /engine
WORKDIR /engine

RUN cmake . && make engine

# Keep the container running
CMD tail -f /var/log/bootstrap.log
