# Docker CNODP Images

## Table Of Contents
- [Docker CNODP Images](#docker-cnodp-images)
	- [Table Of Contents](#table-of-contents)
	- [Description](#description)
	- [Requirements](#requirements)
	- [Install](#install)
	- [Initial Setup & Configuration](#initial-setup--configuration)
		- [Python & Shell Script Runners](#python--shell-script-runners)
		- [Manual run via Docker Compose](#manual-run-via-docker-compose)
	- [Development Options](#development-options)
		- [VS Code Attach Container](#vs-code-attach-container)
		- [VS Code Server](#vs-code-server)
		- [Other Options](#other-options)
	- [Container Management](#container-management)
		- [Stop the Container](#stop-the-container)
		- [Destroy the Container](#destroy-the-container)
		- [Restart the Container](#restart-the-container)
		- [Start the Container](#start-the-container)

## Description
There are three pre-built docker containers available on DockerHub wich contain all the software required to develop and follow along with the pre-core lessons and examples. They are not required to be utilized throughout the course, however may prove useful.

## Requirements
- `Docker` or `DockerDesktop`
- An `x86_64` host machine.
- On windows `wsl` must be enabled which relies on `hyper-v` features being enabled. 
- At least 15 GBs of disk space.

## Install
```bash
chmod +x ./install.sh
./install.sh
```
```powershell
# Run from admin powershell context
./install.ps1
```

## Initial Setup & Configuration
### Python & Shell Script Runners 
```bash
# See all run options
python3 ./run.py -h
# Examples:
## Deploy the cnodp-full container with the vscode server running on port 9090
python3 ./run.py -t full -s -p 9090
## Deploy the cnodp-slim container without the vscode server running 
python3 ./run.py -t slim
```
```bash
## Nix
./run.sh
## Windows
./run.ps1
```

### Manual run via Docker Compose


## Development Options 
### VS Code Attach Container

### VS Code Server

### Other Options

## Container Management
### Stop the Container

### Destroy the Container

### Restart the Container

### Start the Container
