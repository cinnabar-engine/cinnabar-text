FROM archlinux
RUN echo "[cinnabar]">/etc/pacman.conf
RUN echo "Server = https://cinnabar-engine.github.io/arch">/etc/pacman.conf
RUN pacman -Syu --noconfirm && pacman -S base-devel cmake sdl2 cinnabar-render cinnabar-core freetype2 --noconfirm --needed
COPY . /app
RUN chown nobody:nobody /app -R
RUN chmod 7777 /app -R
USER nobody
#RUN cd app
#RUN /packaging/create-arch.sh docker
#CMD bash -c "/app/create-arch.sh $@" docker  >> /proc/1/fd/1