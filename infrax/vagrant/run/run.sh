#!/bin/bash
CLEAR='\e[m'
GREEN='\e[1;32m'
PURPLE='\e[1;35m'
CYAN='\e[1;36m'
BLUE='\e[1;34m'
DIR_PATH=$(dirname $(realpath $0))

function set_cpus() {
	read -e -p "$(echo -e "${PURPLE}[?] Enter the number of CPUs to assign to the VM [2]: ${CLEAR}")" -i "2" NUM_OF_CPUS
	NUM_OF_CPUS=${NUM_OF_CPUS:-2}
	sed -i "s/vb.cpus = 2/vb.cpus = ${NUM_OF_CPUS}/g" Vagrantfile.working
	sed -i "s/vb.vmx[\"numvcpu\"] = \"2\"/vb.vmx[\"numvcpu\"] = \"${NUM_OF_CPUS}\"/g" Vagrantfile.working
}

function set_ram() {
	read -e -p "$(echo -e "${PURPLE}[?] Enter the amout of RAM to assign to the VM [4]: ${CLEAR}")" -i "4" RAM
	RAM=$(expr ${RAM:-4} \* 1024)
	sed -i "s/vb.memory = 4096/vb.memory = ${RAM}/g" Vagrantfile.working
	sed -i "s/vb.vmx[\"memsize\"] = \"4096\"/vb.vmx[\"memsize\"] = \"${RAM}\"/g" Vagrantfile.working
}

function start_with_provider() {
	PS3="$(echo -e "${PURPLE}[?] Enter a number to select which provider you would like to utilize: ${CLEAR}")"
	select provider in virtualbox vmware
	do
		PROVIDER=${provider}
		break
	done
	mv Vagrantfile.working Vagrantfile
	vagrant up --provider $PROVIDER
}

function initialize_vagrant() {
	cd $DIR_PATH
	vagrant init cnodp/wolves
	cp Vagrantfile.template Vagrantfile.working
}

initialize_vagrant
set_cpus
set_ram
start_with_provider