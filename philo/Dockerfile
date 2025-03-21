FROM debian:latest
RUN apt update && apt install -y gcc make
COPY . /app
WORKDIR /app
RUN make
CMD ["./philo 100 800 200 200"]
