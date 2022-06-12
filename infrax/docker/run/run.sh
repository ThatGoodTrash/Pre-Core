#!/bin/bash
CLEAR='\e[m'
GREEN='\e[1;32m'
PURPLE='\e[1;35m'
CYAN='\e[1;36m'
BLUE='\e[1;34m'
SCRIPT_DIR=$(realpath $(dirname "$0"))

function get_size() {
	PS3="$(echo -e "${PURPLE}[?] Enter a number to select which size cnodp/wolves image you would like to utilize: ${CLEAR}")"
	select size in slim partial full
	do
		export WOLF_SIZE=${size}
		break
	done
}

function get_port() { 
	read -e -p "$(echo -e "${PURPLE}[?] Enter the port number to expose for the code-server [8080]: ${CLEAR}")" -i "8080" EXPOSE_PORT
	export EXPOSE_PORT=${EXPOSE_PORT:-8080}
}

function write_docker_compose() {
	cat ${SCRIPT_DIR}/docker-compose-template.yml > ${SCRIPT_DIR}/docker-compose.yml
	sed -i "s/\${WOLF_SIZE}/${WOLF_SIZE}/g" ${SCRIPT_DIR}/docker-compose.yml
	sed -i "s/\${EXPOSE_PORT}/${EXPOSE_PORT}/g" ${SCRIPT_DIR}/docker-compose.yml
}

function start_container() {
	cd "${SCRIPT_DIR}"
	docker-compose up -d
}

function start_server_on_request() {
	read -e -p "$(echo -e "${PURPLE}[?] Would you like to start the code-server now? [N/y]: ${CLEAR}")" START_SERVER
	START_SERVER=${START_SERVER:-N}
	START_SERVER=${START_SERVER:0:1}

	if [[ ${START_SERVER} == 'Y' || ${START_SERVER} == 'y' ]]
	then 
		exec 3< <(docker exec -t cnodp-${WOLF_SIZE} /app/code-server/bin/code-server --auth none --bind-addr 0.0.0.0:${EXPOSE_PORT} --user-data-dir /root/.vscode /home/precore)
		sed -e '/HTTPS/q' <&3 ; cat <&3 &
		disown
		DEF_DEV=$(ip -j -p r | grep -A 5 default | grep dev | cut -d '"' -f4)
		DEF_IP=$(ip -j -p a | grep -m1 -A 20 ${DEF_DEV} | grep local | cut -d '"' -f4)
		echo -e "${GREEN}[+] Connect to the code-server by navigating to http://localhost:8080 or http://${DEF_IP}:8080${CLEAR}"
	else
		echo -e "${BLUE}[*] If you would like to start the server at another point in time run the following commands:${CLEAR}"
		echo -e "${CYAN}docker exec -t cnodp-${WOLF_SIZE} /app/code-server/bin/code-server --auth none --bind-addr 0.0.0.0:8080 --user-data-dir /root/.vscode /home/precore &${CLEAR}"
		echo -e "${CYAN}disown${CLEAR}"
	fi
}

function print_info() {
	echo -e "${GREEN}[+] To get an interactive shell in the container run the following:${CLEAR}"
	echo -e "${CYAN}docker exec -it cnodp-${WOLF_SIZE} /usr/bin/zsh${CLEAR}"
	
	echo -e "${GREEN}[+] To shut down the container without destroying the data:${CLEAR}"
	echo -e "${CYAN}pushd ${SCRIPT_DIR}${CLEAR}"
	echo -e "${CYAN}docker-compose down${CLEAR}"
	echo -e "${CYAN}popd${CLEAR}"
	
	echo -e "${GREEN}[+] To bring the container backup:${CLEAR}"
	echo -e "${CYAN}pushd ${SCRIPT_DIR}${CLEAR}"
	echo -e "${CYAN}docker-compose up -d${CLEAR}"
	echo -e "${CYAN}popd${CLEAR}"
	
	echo -e "${GREEN}[+] To destory the container as well as the volume:${CLEAR}"
	echo -e "${CYAN}pushd ${SCRIPT_DIR}${CLEAR}"
	echo -e "${CYAN}docker-compose down -v${CLEAR}"
	echo -e "${CYAN}popd${CLEAR}"
}

get_size
get_port
write_docker_compose
start_container
start_server_on_request
print_info