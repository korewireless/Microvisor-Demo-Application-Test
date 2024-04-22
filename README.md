# Microvisor Application Test Stub

This repo provides a basic template for application test projects. Application test firmware is a mandatory part of the [Microvisor Factory Process](https://www.twilio.com/docs/iot/microvisor/manufacturing).

## Cloning the Repo

This repo makes uses of git submodules, some of which are nested within other submodules. To clone the repo, run:

```bash
git clone --recurse-submodules https://github.com/korewireless/Microvisor-Demo-Application-Test.git
```

and then:

```bash
cd Microvisor-Demo-Application-Test
```

## Platform Support

We currently support the following build platforms:

* Linux — native development under [Ubuntu 20.0.4](#build-in-ubuntu).
* Windows — development in [Ubuntu 20.0.4 via Windows Subsystem for Linux 2](#build-under-windows) or via [Docker container](#build-with-docker).
* Mac — development via [Docker container](#build-with-docker).

## Build under Windows

The recommended solution for working with Microvisor on Windows is via [Windows Subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install).

You will need Administrator privileges to install WSL.

### Install WSL

1. Open an Administrator-level Powershell instance.
1. Run `wsl --install -d ubuntu`.
1. **Important** Exit Powershell.
1. Open the Ubuntu instance shell from your Start menu and [follow the Ubuntu instructions below](#build-in-ubuntu).

## Build with Docker

### Build the Image

**macOS**

```shell
docker build --build-arg UID=$(id -u) --build-arg GID=$(id -g) -t microvisor-app-test-image .
```

**Windows**

```shell
docker build -t microvisor-app-test-image .
```

### Run the Build

```shell
docker run -it --rm -v $(pwd)/:/home/mvisor/project/ \
  --name microvisor-app-test microvisor-app-test-image
```

Under Docker, the code is compiled and bundled. The bundle is written to `build/app/mv-app-test.zip` in your local repo directory.

## Build in Ubuntu

### Install Libraries and Tools

Run:

```bash
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi git curl \
  build-essential cmake libsecret-1-dev jq openssl gdb-multiarch
```

### Install the Twilio CLI

Install the Twilio CLI. This is required to view streamed logs and for remote debugging. You need version 4.0.1 or above.

**Note** If you have already installed the Twilio CLI using *npm*, we recommend removing it and then reinstalling as outlined below. Remove the old version with `npm remove -g twilio-cli`.

```bash
wget -qO- https://twilio-cli-prod.s3.amazonaws.com/twilio_pub.asc | sudo apt-key add -
sudo touch /etc/apt/sources.list.d/twilio.list
echo 'deb https://twilio-cli-prod.s3.amazonaws.com/apt/ /' | sudo tee /etc/apt/sources.list.d/twilio.list
sudo apt update
sudo apt install -y twilio
```

Close your terminal window or tab, and open a new one. Now run:

```bash
twilio plugins:install @twilio/plugin-microvisor
```

The process outlined below requires Plugin 0.3.10 or above.

## Build and sign the application

The the repo's root directory run:

```bash
cmake -S . -B build
cmake --build build
twilio microvisor:apps:bundle build/app/mv-app-test.bin build/app/mv-app-test.zip
```

This will build and bundle the code. The bundle is written to `build/app/mv-app-test.zip`.

The bundle must now be signed. Run:

```bash
twilio microvisor:apps:create build/app/mv-app-test.zip --bundle-out build/app/mv-app-test-signed.zip
```

The signed bundle is written to `build/app/mv-app-test-signed.zip` and is intended to be consumed by the factory process' SPI flash image build stage.

## Copyright and Licensing

The sample code and Microvisor SDK are © 2024, KORE Wireless. It is licensed under the terms of the [MIT License](./LICENSE.md).

The SDK makes used of code © 2022, STMicroelectronics and affiliates. This code is licensed under terms described in [this file](https://github.com/twilio/twilio-microvisor-hal-stm32u5/blob/main/LICENSE-STM32CubeU5.md).
