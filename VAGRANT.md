# Vagrant CNODP VM

## Table Of Contents
- [Vagrant CNODP VM](#vagrant-cnodp-vm)
  - [Table Of Contents](#table-of-contents)
  - [Description](#description)
  - [Requirements](#requirements)
  - [Install](#install)
    - [Python & Shell Script Installer](#python--shell-script-installer)
    - [Manual Nix](#manual-nix)
    - [Manual Winderps](#manual-winderps)
  - [Initial Setup & Configuration](#initial-setup--configuration)
    - [Python & Shell Script Runners](#python--shell-script-runners)
    - [Manual Setup](#manual-setup)
  - [Login Credentials](#login-credentials)
  - [Shutdown and restart the machine](#shutdown-and-restart-the-machine)
  - [Destroy Instance](#destroy-instance)
  - [Update](#update)

## Description
This is a pre-configured VM specifically built for CNODP pre-core. It has all the tools and configurations pre-loaded to ensure that there are minimal issues related to environment or setup. It is not required to be utilized throughout the course, however may prove useful.

## Requirements
- `virtualbox` or `vmware-workstation`
- `vagrant` (see install instructions below)
- An `x86_64` host machine that can handle at least a 2 vCPU and 4 GB virtual machine. We do not currently support the M1 Mac Architecture.
- 10 GB to download the base image. 
- At least 40 GB for each instance of the box running
  - This is configurable either larger or smaller in either virtualbox/vmware or the vagrantfile
  - The base setup will expect at least 40 GB of disk space free.
## Install
### Python & Shell Script Installer
```bash
# See all options 
python3 ./install.py -h
# Examples:
## Install just vagrant
python3 ./install.py
## Install everything required to utilize vmware
python3 ./install.py -p vmware
## Install everything required to utilize both virtualbox and vmware
python3 ./install.py -p both
```
```bash
chmod +x ./install.sh
./install.sh
```
```powershell
# Run from admin powershell context
./install.ps1
```
### Manual Nix
If your host machine is a linux machine install the vagrant package. [Web Directions](https://www.vagrantup.com/downloads)
```bash
# For ubuntu/debian based distros
curl -fsSL https://apt.releases.hashicorp.com/gpg | sudo apt-key add -
sudo apt-add-repository "deb [arch=amd64] https://apt.releases.hashicorp.com $(lsb_release -cs) main"
sudo apt-get update && sudo apt-get install -y vagrant
# If you don't have VirtualBox or Vmware already installed
sudo apt-get install -y virtualbox
```
If you do have `vmwware-workstation` and would like to use it for this setup you must run the following as well:
```bash
# Instructions: https://www.vagrantup.com/docs/providers/vmware/vagrant-vmware-utility
wget -nv -O vagrant-vmware-utility.zip https://releases.hashicorp.com/vagrant-vmware-utility/1.0.21/vagrant-vmware-utility_1.0.21_linux_amd64.zip
sudo mkdir -p /opt/vagrant-vmware-desktop/bin
sudo unzip -d /opt/vagrant-vmware-desktop/bin vagrant-vmware-utility.zip
sudo /opt/vagrant-vmware-desktop/bin/vagrant-vmware-utility certificate generate
sudo /opt/vagrant-vmware-desktop/bin/vagrant-vmware-utility service install
# Instructions: https://www.vagrantup.com/docs/providers/vmware/installation
vagrant plugin install vagrant-vmware-desktop
```

### Manual Winderps
If you are on a windows machine the following commands must be run in an Administrative Powershell environment in order to ensure that you have the necessary tooling to run the box on a windows environment. 

```powershell
# Install the chocolatey package manager 
Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
cinst vagrant
# If you do not already have VirtualBox or VMWare installed
cinst virtualbox
```
If you do have `vmwware-workstation` and would like to use it for this setup you must run the following as well:
```powershell
# Instructions: https://www.vagrantup.com/docs/providers/vmware/vagrant-vmware-utility
# Download and install the following package: 
## https://releases.hashicorp.com/vagrant-vmware-utility/1.0.21/vagrant-vmware-utility_1.0.21_x86_64.msi
net.exe start vagrant-vmware-utility
# Instructions: https://www.vagrantup.com/docs/providers/vmware/installation
vagrant plugin install vagrant-vmware-desktop
```
## Initial Setup & Configuration
The box may be run with either Virtualbox or VMWare Workstation.

### Python & Shell Script Runners 
```bash
# See all run options
python3 ./run.py -h
# Examples:
## Deploy the box to virtualbox with 4 vCPUs and 8 GB of RAM with the vm being tracked in the /home/dev/vagrant-vms/cnodp folder.
python3 ./run.py -c 4 -r 8 -d /home/dev/vagrant-vms/cnodp
## Deploy the box to vmware with 2 vCPUs and 6 GB of RAM in the default folder (~/vagrant-vms/cnodp)
python3 ./run.py -p vmware -r 6
```
```bash
# Runs the box in the current directory. Asks about CPUs, RAM and provider.
## Nix
./run.sh
## Windows
./run.ps1
```

### Manual Setup
The following commands should be run in the directory where you want your vagrant box definitions to be downloaded and stored. These two commands will initiate the environment by downloading a Vagrantfile which can be used to define things like the amount of CPU and Memory to allocate to the box.
```powershell
vagrant init cnodp/wolves
```
The above command creates a basic `Vagrantfile` in the directory it was run in. You may run with the default Vagrantfile (although it may hide the Virtualbox or 
VMWare GUI to the VM by default.) If you would like to see the VM on screen by default as well as adjust things like vCPUs and RAM for the VM. You may replace th
e contents of the `Vagrantfile` with the following:
```powershell
Vagrant.configure("2") do |config|
  config.vm.box = "cnodp/wolves"

  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = 8192
    vb.cpus = 4
  end

  config.vm.provider "vmware_desktop" do |vb|
    vb.gui = true
    vb.vmx["memsize"] = "8192"
    vb.vmx["numvcpu"] = "4"
  end
end
```
Finally in order to download and bring up the VM you may run the following command. This command can take anywhere from 15-20 min depending on your internet connection as it needs to download the initial 10 Gig image onto your box. Subsequent runs will simply copy the base box to the proper directory from your local filesystem and should be much faster (30 sec to 1 min). In order to pull updates to the box you will need to run a different command detailed later in this guide. 
```powershell
vagrant up --provider virtualbox
```
## Login Credentials
```
Username: vagrant
Password: vagrant
```

## Shutdown and restart the machine
In order to shutdown the machine you may run the following:
```powershell
vagrant down 
```
If you would like to bring the machine back up you may run the following:
```powershell
vagrant up
```
You may of course use either virtualbox/vmwares gui to shutdown and restart the box as well. 
## Destroy Instance
In order to completely remove the instance and all associated data on the machine you have been utilizing you may run the following command:
```powershell
vagrant destroy -f
``` 

Subsequent runs of the following two commands will check for updates to our customized image (but not download/install them by default) and will boot a fresh copy of the local image currently installed. If there has been an update it will signal that you can download the new image via another command (see below). 

```powershell
vagrant init -f cnodp/wolves
vagrant up --provider virtualbox
# Or vmware provider
vagrant up --provider vmware_desktop
```
## Update
This will pull in any updates for the specified box in your Vagrantfile.
```powershell
vagrant box update
```
