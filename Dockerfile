FROM krallin/ubuntu-tini:xenial

RUN apt-get update -y \
	&& apt-get upgrade -y \
	&& apt-get install -y --no-install-recommends \
		build-essential \
		git \
		wget \
		bzip2 \
		ca-certificates \
		sudo \
        locales \
        cmake \
        gcc \
        g++ \
        less \
        openssh-client \
        dos2unix \
	&& apt-get clean \
	&& rm -fr /var/lib/apt/lists

# Generate locales
RUN    echo "en_US.UTF-8 UTF-8" >  /etc/locale.gen \
	&& echo "en_AU.UTF-8 UTF-8" >> /etc/locale.gen \
    && locale-gen

# Configure environment
ENV SHELL /bin/bash
ENV HOME /root
ENV LC_ALL en_AU.UTF-8
ENV LANG en_AU.UTF-8
ENV LANGUAGE en_AU:en

RUN echo "cacert=/etc/ssl/certs/ca-certificates.crt" > /root/.curlrc
RUN ssh-keygen -t rsa -b 4096 -N "" -f /root/.ssh/id_rsa

RUN apt-get update -y \
	&& apt-get upgrade -y \
	&& apt-get install -y --no-install-recommends \
        openssh-server \
	&& apt-get clean \
	&& rm -fr /var/lib/apt/lists

RUN mkdir /var/run/sshd
RUN echo 'root:root' |chpasswd

RUN sed -ri 's/^PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -ri 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config

EXPOSE 22

# Install conda as root
ENV CONDA_DIR /opt/conda3/4.2.12
RUN cd /tmp && \
    mkdir -p $CONDA_DIR && \
    wget https://repo.continuum.io/miniconda/Miniconda3-4.2.12-Linux-x86_64.sh && \
    echo "c59b3dd3cad550ac7596e0d599b91e75d88826db132e4146030ef471bb434e9a *Miniconda3-4.2.12-Linux-x86_64.sh" | sha256sum -c - && \
    /bin/bash Miniconda3-4.2.12-Linux-x86_64.sh -f -b -p $CONDA_DIR && \
    rm Miniconda3-4.2.12-Linux-x86_64.sh && \
    $CONDA_DIR/bin/conda config --system --add channels conda-forge && \
    $CONDA_DIR/bin/conda config --system --set auto_update_conda false && \
    $CONDA_DIR/bin/conda clean -tipsy

RUN echo "export PATH=$CONDA_DIR/bin:$PATH" >> /root/.bashrc

RUN $CONDA_DIR/bin/conda create --name openmm --yes python=2.7 doxygen swig fftw numpy \ 
	&& $CONDA_DIR/bin/conda clean -tipsy

# Configure container startup
ENTRYPOINT ["tini", "--"]

WORKDIR /root

CMD    ["/usr/sbin/sshd", "-D"]

### Note to build openmm ###
# source activate openmm
# mkdir build
# cd build
# cmake ../openmm -DCMAKE_INSTALL_PREFIX=/opt/openmm/7.1
# make
# make test (optional)
# make install
# make PythonInstall
# python -m simtk.testInstallation
