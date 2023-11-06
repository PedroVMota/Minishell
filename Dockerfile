FROM --platform=arm64 debian:latest

# Install dependencies
RUN apt update && apt upgrade -y
RUN apt install git cmake make clang gdb gcc valgrind wget -y

# Install Readline 8
RUN wget https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
RUN tar -xvf readline-8.1.tar.gz
RUN cd readline-8.1 && ./configure && make && make install

