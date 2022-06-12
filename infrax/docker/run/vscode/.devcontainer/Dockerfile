# You can select which version of the container you would like here:
FROM cnodp/wolves-full
#FROM cnodp/wolves-partial
#FROM cnodp/wolves-slim
RUN useradd -ms /bin/zsh student
RUN usermod -a -G sudo student
RUN echo "student:student" | chpasswd
USER student
WORKDIR /home/student
