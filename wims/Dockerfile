FROM debian

EXPOSE 80 443

WORKDIR /home/wims

ENTRYPOINT ["./docker-entrypoint.sh"]

VOLUME ["/home/wims/sessions", "/home/wims/s2", "/home/wims/log"]

RUN    apt-get update \
    && apt-get install -y \
        --no-install-recommends \
        ant \
        apache2 \
        autoconf \
        bison \
        flex \
        gcc \
        g++ \
        imagemagick \
        libgd-dev \
        lsb-release \
        make \
        openjdk-7-jdk \
        sudo \
        texlive \
        unzip \
    && rm -rf /var/lib/apt/lists/* \
    && adduser \
        --disabled-password \
        --gecos '' \
        --no-create-home \
        wims

COPY . .

RUN chown -R \
        wims: \
        /home/wims
